// Abseil through import mcpplibs.mwrap.abseil alone: the library's strings, containers, hashing, status,
// time, numbers, random, synchronization and functional names, used as upstream documents them. No
// Abseil header is included here.
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.abseil;

namespace {

TEST(Strings, CatFormatSplitJoin) {
    EXPECT_EQ(absl::StrCat("a", 1, "-", 2.5, absl::Hex(255, absl::kZeroPad4)), "a1-2.500ff");
    EXPECT_EQ(absl::StrFormat("%s=%05d|%.3f|%x", "n", 42, 3.14159, 255u), "n=00042|3.142|ff");
    std::vector<std::string> parts = absl::StrSplit("a,b,,c", ',', absl::SkipEmpty());
    EXPECT_EQ(parts, (std::vector<std::string>{"a", "b", "c"}));
    std::vector<absl::string_view> pieces = absl::StrSplit("k1=v1;k2=v2", absl::ByAnyChar(";="));
    ASSERT_EQ(pieces.size(), 4u);
    EXPECT_EQ(pieces[3], "v2");
    EXPECT_EQ(absl::StrJoin(parts, "+"), "a+b+c");
    EXPECT_EQ(absl::StrJoin(std::map<int, int>{{1, 2}, {3, 4}}, ",", absl::PairFormatter("=")), "1=2,3=4");
    EXPECT_EQ(absl::StrReplaceAll("one two one", {{"one", "1"}, {"two", "2"}}), "1 2 1");
    EXPECT_EQ(absl::Substitute("$0 + $0 = $1", 2, 4), "2 + 2 = 4");
    EXPECT_TRUE(absl::StartsWith("prefix-body", "prefix") && absl::EndsWithIgnoreCase("body.TXT", ".txt"));
    EXPECT_EQ(absl::StripAsciiWhitespace("  x y \t"), "x y");
    EXPECT_EQ(absl::AsciiStrToUpper("abc"), "ABC");
    int number = 0;
    EXPECT_TRUE(absl::SimpleAtoi("-1234", &number));
    EXPECT_EQ(number, -1234);
    EXPECT_FALSE(absl::SimpleAtoi("12x", &number));
    EXPECT_EQ(absl::Base64Escape("Abseil"), "QWJzZWls");
    std::string unescaped;
    EXPECT_TRUE(absl::Base64Unescape("QWJzZWls", &unescaped));
    EXPECT_EQ(unescaped, "Abseil");
    EXPECT_EQ(absl::CEscape("a\nb\"c"), "a\\nb\\\"c");
}

TEST(Strings, Cord) {
    absl::Cord cord("hello");
    cord.Append(", ");
    cord.Append(std::string(1000, 'x'));
    EXPECT_EQ(cord.size(), 1007u);
    EXPECT_TRUE(cord.StartsWith("hello, x"));
    EXPECT_EQ(std::string(cord).substr(0, 7), "hello, ");
    EXPECT_EQ(absl::Cord("abc"), absl::Cord("abc"));
}

TEST(Containers, HashMapsBtreeInlinedFixed) {
    absl::flat_hash_map<std::string, int> counts;
    for (absl::string_view word : absl::StrSplit("a b a c b a", ' ')) ++counts[word];
    EXPECT_EQ(counts.size(), 3u);
    EXPECT_EQ(counts["a"], 3);
    EXPECT_TRUE(counts.contains("c"));
    absl::flat_hash_set<int> set = {1, 2, 3};
    set.erase(2);
    EXPECT_FALSE(set.contains(2));
    absl::node_hash_map<int, std::string> nodes = {{1, "one"}};
    const std::string* stable = &nodes[1];
    for (int i = 2; i < 100; ++i) nodes[i] = "n";
    EXPECT_EQ(stable, &nodes[1]);
    absl::btree_map<int, char> ordered = {{3, 'c'}, {1, 'a'}, {2, 'b'}};
    std::string walk;
    for (const auto& [key, value] : ordered) walk += value;
    EXPECT_EQ(walk, "abc");
    absl::btree_set<std::string> names = {"b", "a"};
    EXPECT_EQ(*names.begin(), "a");
    absl::InlinedVector<int, 4> small = {1, 2, 3};
    small.push_back(4);
    small.push_back(5);
    EXPECT_EQ(small.size(), 5u);
    absl::FixedArray<int> fixed(3, 7);
    EXPECT_EQ(std::accumulate(fixed.begin(), fixed.end(), 0), 21);
    // An adapted constant of internal linkage in the header, the same value.
    EXPECT_EQ(mcpplibs::mwrap::abseil::kFixedArrayUseDefault, static_cast<std::size_t>(-1));
}

struct Point {
    int x, y;
    template <typename H>
    friend H AbslHashValue(H h, const Point& p) { return H::combine(std::move(h), p.x, p.y); }
    bool operator==(const Point&) const = default;
};

TEST(Hash, ConsistentAndCombinable) {
    EXPECT_EQ(absl::HashOf(Point{1, 2}), absl::HashOf(Point{1, 2}));
    EXPECT_EQ(absl::Hash<std::string>{}("abc"), absl::Hash<absl::string_view>{}("abc"));
    absl::flat_hash_set<Point> points = {{1, 2}, {3, 4}};
    EXPECT_TRUE(points.contains(Point{3, 4}));
}

TEST(Status, CodesMessagesAndStatusOr) {
    absl::Status ok = absl::OkStatus();
    EXPECT_TRUE(ok.ok());
    absl::Status missing = absl::NotFoundError("no such key");
    EXPECT_EQ(missing.code(), absl::StatusCode::kNotFound);
    EXPECT_TRUE(absl::IsNotFound(missing));
    EXPECT_EQ(missing.message(), "no such key");
    EXPECT_EQ(missing.ToString(), "NOT_FOUND: no such key");
    std::ostringstream out;
    out << missing;  // a namespace-scope operator, exported with the type
    EXPECT_EQ(out.str(), "NOT_FOUND: no such key");
    auto parse = [](absl::string_view text) -> absl::StatusOr<int> {
        int value;
        if (!absl::SimpleAtoi(text, &value)) return absl::InvalidArgumentError(absl::StrCat("not a number: ", text));
        return value;
    };
    EXPECT_EQ(*parse("41") + 1, 42);
    absl::StatusOr<int> bad = parse("x");
    ASSERT_FALSE(bad.ok());
    EXPECT_EQ(bad.status().code(), absl::StatusCode::kInvalidArgument);
    EXPECT_EQ(bad.value_or(-1), -1);
}

TEST(Time, DurationsCivilTimeAndFormatting) {
    const absl::Duration d = absl::Hours(1) + absl::Minutes(30);  // the arithmetic operators
    EXPECT_EQ(absl::ToInt64Minutes(d), 90);
    EXPECT_EQ(absl::FormatDuration(d), "1h30m");
    EXPECT_TRUE(d > absl::ZeroDuration() && d * 2 == absl::Hours(3));
    const absl::TimeZone utc = absl::UTCTimeZone();
    const absl::Time t = absl::FromCivil(absl::CivilSecond(2025, 5, 12, 8, 30, 0), utc);
    EXPECT_EQ(absl::FormatTime(absl::RFC3339_full, t, utc), "2025-05-12T08:30:00+00:00");
    EXPECT_EQ(absl::ToUnixSeconds(t), 1747038600);
    absl::Time parsed;
    std::string error;
    ASSERT_TRUE(absl::ParseTime(absl::RFC3339_full, "2025-05-12T10:30:00+02:00", &parsed, &error)) << error;
    EXPECT_EQ(parsed, t);
    const absl::CivilDay day(2024, 2, 28);
    EXPECT_EQ(day + 1, absl::CivilDay(2024, 2, 29));
    EXPECT_EQ(absl::GetWeekday(absl::CivilDay(2025, 5, 12)), absl::Weekday::monday);
    const absl::TimeZone plus_eight = absl::FixedTimeZone(8 * 60 * 60);
    EXPECT_EQ(absl::FormatTime("%H:%M", t, plus_eight), "16:30");
    EXPECT_GT(absl::Now(), t);
}

TEST(Numeric, Int128AndBits) {
    const absl::uint128 big = absl::MakeUint128(1, 0);
    EXPECT_EQ(absl::Uint128High64(big * 3), 3u);
    EXPECT_EQ(absl::int128(-5) * 4, absl::int128(-20));
    std::ostringstream out;
    out << absl::Uint128Max();
    EXPECT_EQ(out.str(), "340282366920938463463374607431768211455");
    EXPECT_EQ(absl::popcount(0xF0u), 4);
    EXPECT_EQ(absl::countr_zero(8u), 3);
    EXPECT_EQ(absl::bit_ceil(5u), 8u);
}

TEST(Crc, Crc32cCheckValue) {
    // The CRC-32C check value of "123456789" (RFC 3720, appendix B.4).
    EXPECT_EQ(static_cast<std::uint32_t>(absl::ComputeCrc32c("123456789")), 0xE3069283u);
    const absl::crc32c_t left = absl::ComputeCrc32c("1234"), right = absl::ComputeCrc32c("56789");
    EXPECT_EQ(absl::ConcatCrc32c(left, right, 5), absl::ComputeCrc32c("123456789"));
}

TEST(Functional, CleanupFunctionRefAnyInvocableBindFrontOverload) {
    int cleaned = 0;
    {
        absl::Cleanup bump = [&] { ++cleaned; };
    }
    EXPECT_EQ(cleaned, 1);
    auto apply = [](absl::FunctionRef<int(int)> f) { return f(20); };
    EXPECT_EQ(apply([](int x) { return x + 1; }), 21);
    absl::AnyInvocable<std::unique_ptr<int>()> make = [p = std::make_unique<int>(7)]() mutable { return std::move(p); };
    EXPECT_EQ(*make(), 7);
    auto add = absl::bind_front([](int a, int b) { return a + b; }, 40);
    EXPECT_EQ(add(2), 42);
    auto kind = absl::Overload([](int) { return 'i'; }, [](absl::string_view) { return 's'; });
    EXPECT_EQ(kind(1), 'i');
    EXPECT_EQ(kind(absl::string_view("x")), 's');
    std::vector<int> values = {3, 1, 2};
    absl::c_sort(values);
    EXPECT_TRUE(absl::c_is_sorted(values) && absl::c_linear_search(values, 2));
    absl::Span<const int> span(values);
    EXPECT_EQ(span.subspan(1).front(), 2);
}

TEST(Random, DistributionsStayInBounds) {
    absl::BitGen gen;
    for (int i = 0; i < 1000; ++i) {
        const int u = absl::Uniform(absl::IntervalClosedClosed, gen, 1, 6);
        ASSERT_TRUE(u >= 1 && u <= 6);
        const double r = absl::Uniform(gen, 0.0, 1.0);
        ASSERT_TRUE(r >= 0.0 && r < 1.0);
    }
    absl::InsecureBitGen fast;
    EXPECT_LE(absl::Bernoulli(fast, 0.0), false);
    std::vector<int> deck = {1, 2, 3, 4, 5};
    std::shuffle(deck.begin(), deck.end(), gen);
    EXPECT_EQ(std::accumulate(deck.begin(), deck.end(), 0), 15);
}

TEST(Synchronization, MutexNotificationBlockingCounter) {
    absl::Mutex mu;
    int total = 0;
    {
        absl::MutexLock lock(&mu);
        total = 1;
    }
    absl::Notification done;
    EXPECT_FALSE(done.HasBeenNotified());
    done.Notify();
    EXPECT_TRUE(done.WaitForNotificationWithTimeout(absl::Seconds(1)));
#ifndef __EMSCRIPTEN__  // the Web row is built without threads
    absl::BlockingCounter counter(4);
    std::vector<std::thread> workers;
    for (int i = 0; i < 4; ++i)
        workers.emplace_back([&] {
            for (int j = 0; j < 1000; ++j) {
                absl::MutexLock lock(&mu);
                ++total;
            }
            counter.DecrementCount();
        });
    counter.Wait();
    for (auto& worker : workers) worker.join();
    EXPECT_EQ(total, 4001);
#endif
}

TEST(Base, LogSeverityAndCasts) {
    EXPECT_EQ(absl::LogSeverityName(absl::LogSeverity::kWarning), std::string_view("WARNING"));
    EXPECT_EQ(absl::NormalizeLogSeverity(absl::LogSeverity::kFatal), absl::LogSeverity::kFatal);
    EXPECT_EQ(absl::bit_cast<std::uint32_t>(1.0f), 0x3F800000u);
    EXPECT_EQ(absl::implicit_cast<long>(3), 3L);
    static absl::once_flag once;
    int calls = 0;
    for (int i = 0; i < 3; ++i) absl::call_once(once, [&] { ++calls; });
    EXPECT_EQ(calls, 1);
}

}  // namespace
