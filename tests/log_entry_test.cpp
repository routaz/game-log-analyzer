#include <gtest/gtest.h>
#include "game_log_analyzer/log_entry.h"

namespace game_log_analyzer {

TEST(SeverityTest, ConvertsToString) {
    EXPECT_EQ(severity_to_string(Severity::Info), "INFO");
    EXPECT_EQ(severity_to_string(Severity::Warning), "WARN");
    EXPECT_EQ(severity_to_string(Severity::Error), "ERROR");
    EXPECT_EQ(severity_to_string(Severity::Fatal), "FATAL");
    EXPECT_EQ(severity_to_string(Severity::Unknown), "UNKNOWN");
}

TEST(SeverityTest, ConvertsFromString) {
    EXPECT_EQ(string_to_severity("INFO"), Severity::Info);
    EXPECT_EQ(string_to_severity("WARN"), Severity::Warning);
    EXPECT_EQ(string_to_severity("ERROR"), Severity::Error);
    EXPECT_EQ(string_to_severity("FATAL"), Severity::Fatal);
}

TEST(SeverityTest, UnknownForInvalidInput) {
    EXPECT_EQ(string_to_severity("GARBAGE"), Severity::Unknown);
    EXPECT_EQ(string_to_severity(""), Severity::Unknown);
    EXPECT_EQ(string_to_severity("info"), Severity::Unknown);
}

}