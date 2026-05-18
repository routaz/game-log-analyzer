#include <gtest/gtest.h>
#include "game_log_analyzer/crash_detector.h"

namespace game_log_analyzer {

TEST(CrashDetectorTest, DetectsFatalEntries) {
    CrashDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Fatal, "Core", "Unhandled exception"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Critical);
    EXPECT_EQ(matches[0].detector_name, "CrashDetector");
}

TEST(CrashDetectorTest, DetectsCrashKeywords) {
    CrashDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Core", "Access violation at 0x00FF"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 1);
}

TEST(CrashDetectorTest, IgnoresNormalEntries) {
    CrashDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Info, "Core", "Save checkpoint reached"});
    entries.push_back({"2024-01-01 00:00:00", Severity::Warning, "Memory", "Pool nearly full"});

    auto matches = detector.detect(entries);

    EXPECT_EQ(matches.size(), 0);
}

TEST(CrashDetectorTest, ReturnsCorrectName) {
    CrashDetector detector;
    EXPECT_EQ(detector.name(), "CrashDetector");
}

}