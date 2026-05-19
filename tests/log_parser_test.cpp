#include <gtest/gtest.h>
#include "game_log_analyzer/log_parser.h"

namespace game_log_analyzer {

TEST(LogParserTest, ParsesValidFile) {
    LogParser parser;
    auto entries = parser.parse_file("../sample_logs/game_session.log");

    ASSERT_EQ(entries.size(), 10);
    EXPECT_EQ(entries[0].severity, Severity::Info);
    EXPECT_EQ(entries[0].category, "Physics");
    EXPECT_EQ(entries[2].severity, Severity::Error);
    EXPECT_EQ(entries[2].category, "Rendering");
}

TEST(LogParserTest, ParsesAllSeverityLevels) {
    LogParser parser;
    auto entries = parser.parse_file("../sample_logs/game_session.log");

    ASSERT_EQ(entries.size(), 10);
    EXPECT_EQ(entries[0].severity, Severity::Info);
    EXPECT_EQ(entries[1].severity, Severity::Warning);
    EXPECT_EQ(entries[2].severity, Severity::Error);
    EXPECT_EQ(entries[6].severity, Severity::Fatal);
}

TEST(LogParserTest, ThrowsOnMissingFile) {
    LogParser parser;
    EXPECT_THROW(parser.parse_file("nonexistent.log"), std::runtime_error);
}

} // namespace game_log_analyzer