#include <gtest/gtest.h>
#include "game_log_analyzer/performance_detector.h"

namespace game_log_analyzer {

TEST(PerformanceDetectorTest, DetectsSevereFrameSpike) {
    PerformanceDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Info, "Physics", "Frame time: 48ms (target: 16ms)"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::High);
}

TEST(PerformanceDetectorTest, DetectsMildFrameSpike) {
    PerformanceDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Info, "Physics", "Frame time: 20ms (target: 16ms)"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Medium);
}

TEST(PerformanceDetectorTest, IgnoresGoodFrameTime) {
    PerformanceDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Info, "Physics", "Frame time: 12ms (target: 16ms)"});

    auto matches = detector.detect(entries);

    EXPECT_EQ(matches.size(), 0);
}

TEST(PerformanceDetectorTest, DetectsOutOfMemory) {
    PerformanceDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Memory", "Out of memory: requested 512MB"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Critical);
}

TEST(PerformanceDetectorTest, DetectsAllocationSpike) {
    PerformanceDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Warning, "Memory", "Allocation spike: 256MB in 0.3s"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Medium);
}

TEST(PerformanceDetectorTest, ReturnsCorrectName) {
    PerformanceDetector detector;
    EXPECT_EQ(detector.name(), "PerformanceDetector");
}

}