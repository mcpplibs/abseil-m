// Abseil through its C++ modules. The macros (LOG, CHECK …) are not something a module can export: they come
// from <mwrap/abseil/macros.hpp>, included before the imports.
#include <mwrap/abseil/macros.hpp>

import std;
import mcpplibs.mwrap.abseil;

namespace {

// Every log line also lands here.
struct Collect final : absl::LogSink {
    std::vector<std::string> lines;
    void Send(const absl::LogEntry& entry) override { lines.emplace_back(entry.text_message()); }
};

struct Reading {
    std::string sensor;
    int value;
};

// "name=value", or why not.
absl::StatusOr<Reading> Parse(absl::string_view text) {
    std::pair<absl::string_view, absl::string_view> kv = absl::StrSplit(text, absl::MaxSplits('=', 1));
    int value = 0;
    if (kv.first.empty() || !absl::SimpleAtoi(kv.second, &value))
        return absl::InvalidArgumentError(absl::StrCat("not a reading: \"", text, "\""));
    return Reading{std::string(kv.first), value};
}

}  // namespace

int main() {
    Collect sink;
    absl::AddLogSink(&sink);

    absl::flat_hash_map<std::string, int> counts;
    for (absl::string_view word : absl::StrSplit("the quick fox and the lazy dog and the cat", ' ', absl::SkipEmpty()))
        ++counts[word];
    std::vector<std::pair<std::string, int>> sorted(counts.begin(), counts.end());
    absl::c_sort(sorted, [](const auto& a, const auto& b) { return a.second != b.second ? a.second > b.second : a.first < b.first; });
    std::cout << "top words: " << absl::StrJoin(sorted.begin(), sorted.begin() + 2, ", ", absl::PairFormatter("=")) << "\n";

    for (absl::string_view text : {"temp=21", "humidity=x"}) {
        absl::StatusOr<Reading> reading = Parse(text);
        if (reading.ok())
            std::cout << absl::StrFormat("%s reads %d\n", reading->sensor, reading->value);
        else
            LOG(WARNING) << reading.status();
    }

    const absl::Time at = absl::FromCivil(absl::CivilSecond(2025, 5, 12, 8, 30, 0), absl::UTCTimeZone());
    std::cout << "release day: " << absl::FormatTime(absl::RFC3339_sec, at, absl::UTCTimeZone()) << "\n";

    absl::RemoveLogSink(&sink);
    CHECK_EQ(sink.lines.size(), 1u);
    std::cout << "logged: " << sink.lines.front() << "\n";
    return counts["the"] == 3 && sorted.front().first == "the" ? 0 : 1;
}
