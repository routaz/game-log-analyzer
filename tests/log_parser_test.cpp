#include <gtest/gtest.h>
#include "game_log_analyzer/log_parser.h"

namespace game_log_analyzer {

TEST(LogParserTest, ParsesValidLine) {
    LogParser parser;
    auto entry = parser.parse_line(
        "[2024-03-15 14:23:01.456] [ERROR] [Rendering] Shader compilation failed"
    );

    EXPECT_EQ(entry.timestamp, "2024-03-15 14:23:01.456");
    EXPECT_EQ(entry.severity, Severity::Error);
    EXPECT_EQ(entry.category, "Rendering");
    EXPECT_EQ(entry.message, "Shader compilation failed");
}

TEST(LogParserTest, ParsesAllSeverityLevels) {
    LogParser parser;

    auto info = parser.parse_line("[2024-01-01 00:00:00.000] [INFO] [Core] Test");
    EXPECT_EQ(info.severity, Severity::Info);

    auto warn = parser.parse_line("[2024-01-01 00:00:00.000] [WARN] [Core] Test");
    EXPECT_EQ(warn.severity, Severity::Warning);

    auto fatal = parser.parse_line("[2024-01-01 00:00:00.000] [FATAL] [Core] Test");
    EXPECT_EQ(fatal.severity, Severity::Fatal);
}

TEST(LogParserTest, ThrowsOnInvalidLine) {
    LogParser parser;
    EXPECT_THROW(parser.parse_line("not a valid log line"), std::runtime_error);
    EXPECT_THROW(parser.parse_line(""), std::runtime_error);
}

TEST(LogParserTest, ThrowsOnMissingFile) {
    LogParser parser;
    EXPECT_THROW(parser.parse_file("nonexistent.log"), std::runtime_error);
}

}