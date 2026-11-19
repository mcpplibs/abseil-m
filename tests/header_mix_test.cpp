// The macros, which a module cannot export, with the module: <mwrap/abseil/macros.hpp> (every public header)
// is included first, then the module imported — the order GCC requires (its includes before its imports).
// Flags declared with ABSL_FLAG, read and set; LOG to a sink; CHECK; the attribute and branch macros; and the
// entities seen through the header and through the module are the same.
#include <mwrap/abseil/macros.hpp>
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.abseil;

ABSL_FLAG(int, rounds, 3, "how many rounds");
ABSL_FLAG(std::string, greeting, "hello", "what to say");

namespace {

struct Capture final : absl::LogSink {
    std::vector<std::string> lines;
    void Send(const absl::LogEntry& entry) override { lines.emplace_back(entry.text_message()); }
};

TEST(HeaderMix, FlagsDeclaredReadSetAndFound) {
    EXPECT_EQ(absl::GetFlag(FLAGS_rounds), 3);
    absl::SetFlag(&FLAGS_rounds, 5);
    EXPECT_EQ(absl::GetFlag(FLAGS_rounds), 5);
    absl::CommandLineFlag* flag = absl::FindCommandLineFlag("greeting");
    ASSERT_NE(flag, nullptr);
    EXPECT_EQ(flag->CurrentValue(), "hello");
    std::string error;
    EXPECT_TRUE(flag->ParseFrom("hi", &error)) << error;
    EXPECT_EQ(absl::GetFlag(FLAGS_greeting), "hi");
    EXPECT_FALSE(absl::FindCommandLineFlag("rounds")->ParseFrom("not a number", &error));
}

TEST(HeaderMix, LogToASinkAndCheck) {
    Capture sink;
    absl::AddLogSink(&sink);
    LOG(INFO) << "value " << 42;
    LOG_IF(WARNING, false) << "not logged";
    ABSL_LOG(ERROR) << absl::StrCat("status: ", absl::NotFoundError("x").ToString());
    absl::RemoveLogSink(&sink);
    ASSERT_EQ(sink.lines.size(), 2u);
    EXPECT_EQ(sink.lines[0], "value 42");
    EXPECT_EQ(sink.lines[1], "status: NOT_FOUND: x");
    CHECK_EQ(2 + 2, 4) << "arithmetic";
    ABSL_CHECK(!sink.lines.empty());
    int value = 7;
    EXPECT_EQ(*ABSL_DIE_IF_NULL(&value), 7);
}

ABSL_ATTRIBUTE_UNUSED ABSL_CONST_INIT int g_counter = 0;

TEST(HeaderMix, BranchAndAttributeMacrosAndOneSetOfEntities) {
    int taken = 0;
    if (ABSL_PREDICT_TRUE(g_counter == 0)) ++taken;
    if (ABSL_PREDICT_FALSE(g_counter != 0)) ++taken;
    EXPECT_EQ(taken, 1);
    static_assert(ABSL_LTS_RELEASE_VERSION == 20250512);
    // Made through the header's spelling, used through the module's, and the other way.
    const ::absl::lts_20250512::Status made = ::absl::lts_20250512::InvalidArgumentError("e");
    const absl::Status& seen = made;
    EXPECT_TRUE(absl::IsInvalidArgument(seen));
    static_assert(std::is_same_v<absl::flat_hash_map<int, int>, ::absl::lts_20250512::flat_hash_map<int, int>>);
}

}  // namespace
