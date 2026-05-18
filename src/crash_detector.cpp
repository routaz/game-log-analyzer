#include "game_log_analyzer/crash_detector.h"

namespace game_log_analyzer {

std::string CrashDetector::name() const {
    return "CrashDetector";
}

bool CrashDetector::is_crash_entry(const LogEntry& entry) const {
    if (entry.severity == Severity::Fatal) {
        return true;
    }

    const std::string& msg = entry.message;

    if (msg.find("exception") != std::string::npos) return true;
    if (msg.find("Exception") != std::string::npos) return true;
    if (msg.find("crash") != std::string::npos) return true;
    if (msg.find("Crash") != std::string::npos) return true;
    if (msg.find("Access violation") != std::string::npos) return true;
    if (msg.find("segfault") != std::string::npos) return true;

    return false;
}

std::vector<PatternMatch> CrashDetector::detect(const std::vector<LogEntry>& entries) const {
    std::vector<PatternMatch> matches;

    for (const auto& entry : entries) {
        if (is_crash_entry(entry)) {
            PatternMatch match;
            match.detector_name = name();
            match.description = "Crash detected: " + entry.message;
            match.match_severity = MatchSeverity::Critical;
            match.related_entries.push_back(entry);

            matches.push_back(match);
        }
    }

    return matches;
}

}