#include <gtest/gtest.h>
#include "game_log_analyzer/error_detector.h"

namespace game_log_analyzer {

TEST(ErrorDetectorTest, DetectsMemoryErrorAsHigh) {
    ErrorDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Memory", "Out of memory: requested 512MB, available 128MB"});
   
    auto matches = detector.detect(entries);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::High);
}

TEST(ErrorDetectorTest, DetectsRenderingErrorAsMedium) {
    ErrorDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Rendering", "Texture pool nearly full: 95% utilized"});
   
    auto matches = detector.detect(entries);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Medium);
}

TEST(ErrorDetectorTest, DetectsAudioErrorAsMedium) {
    ErrorDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Audio", "Sound bank failed to load: explosions.bnk"});
   
    auto matches = detector.detect(entries);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Medium);
}

TEST(ErrorDetectorTest, DetectsUnkownErrorAsLow) {
    ErrorDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Physics", "Frame time: 48ms (target: 16ms)"});
   
    auto matches = detector.detect(entries);
    EXPECT_EQ(matches[0].match_severity, MatchSeverity::Low);
}


TEST(ErrorDetectorTest, DetectsErrorKeywords) {
    ErrorDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Rendering", "Texture pool nearly full: 95% utilized"});
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Memory", "Out of memory: requested 512MB, available 128MB"});
    entries.push_back({"2024-01-01 00:00:00", Severity::Error, "Audio", "Sound bank failed to load: explosions.bnk"});

    auto matches = detector.detect(entries);

    ASSERT_EQ(matches.size(), 3);
}

TEST(ErrorDetectorTest, IgnoresNormalEntries) {
    ErrorDetector detector;

    std::vector<LogEntry> entries;
    entries.push_back({"2024-01-01 00:00:00", Severity::Info, "Core", "Save checkpoint reached"});
    entries.push_back({"2024-01-01 00:00:00", Severity::Warning, "Memory", "Pool nearly full"});

    auto matches = detector.detect(entries);

    EXPECT_EQ(matches.size(), 0);
}

TEST(ErrorDetectorTest, ReturnsCorrectName) {
    ErrorDetector detector;
    EXPECT_EQ(detector.name(), "ErrorDetector");
}

}