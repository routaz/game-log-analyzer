#include "game_log_analyzer/error_detector.h"
#include <stdexcept>

namespace game_log_analyzer {

std::string ErrorDetector::name() const {
    return "ErrorDetector";
}

PatternMatch ErrorDetector::check_error_category(const LogEntry& entry) const{
    PatternMatch match;
    match.detector_name = name();
    match.description = build_description(entry);
    match.match_severity = get_severity_for_category(entry.category);
    match.related_entries.push_back(entry);
    return match;


}

MatchSeverity ErrorDetector::get_severity_for_category(const std::string& category) const {
    
    if(category== "Memory") return MatchSeverity::High;
    if(category == "Rendering" || category == "Audio") return MatchSeverity::Medium;
    return MatchSeverity::Low;
}

std::vector<PatternMatch> ErrorDetector::detect(const std::vector<LogEntry>& entries) const {
    std::vector<PatternMatch> matches;

    for (const auto& entry : entries) {
    if (entry.severity != Severity::Error) {
        continue;
    }

    const std::string& msg = entry.message;
    if (msg.find("exception") != std::string::npos
        || msg.find("Exception") != std::string::npos
        || msg.find("crash") != std::string::npos
        || msg.find("Access violation") != std::string::npos) {
        continue;
    }

    matches.push_back(check_error_category(entry));
    }
    return matches;
}

std::string ErrorDetector::build_description(const LogEntry& entry) const{
    
    return "Error in " + entry.category + ": " + entry.message;
}

}