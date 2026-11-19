// Clang reads a translation unit that imports the module first and includes Abseil's headers after it;
// GCC 16 does not (an import followed by an include of the same headers redefines the standard library's
// internals), so there this test is empty and the README states the order: includes first.
#if defined(__clang__)
import mcpplibs.mwrap.abseil;
#include <absl/strings/str_cat.h>
#include <absl/status/status.h>
#endif
#include <gtest/gtest.h>

#if defined(__clang__)
TEST(ImportFirst, ModuleThenHeaders) {
    const absl::Status status = absl::UnavailableError(absl::StrCat("try ", 2));
    EXPECT_EQ(status.ToString(), "UNAVAILABLE: try 2");
}
#else
TEST(ImportFirst, NotForGcc) { SUCCEED(); }
#endif
