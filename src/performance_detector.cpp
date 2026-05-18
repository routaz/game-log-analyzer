#include "game_log_analyzer/performance_detector.h"
#include <stdexcept>

namespace game_log_analyzer {

std::string PerformanceDetector::name() const {
    return "PerformanceDetector";
}

int PerformanceDetector::extract_number_after(const std::string& text, const std::string& prefix) const {
    std::size_t pos = text.find(prefix);
    if (pos == std::string::npos) {
        return -1;
    }

    pos += prefix.size();
    std::string number_str;

    while (pos < text.size() && std::isdigit(text[pos])) {
        number_str += text[pos];
        pos++;
    }

    if (number_str.empty()) {
        return -1;
    }

    return std::stoi(number_str);
}

bool PerformanceDetector::is_frame_time_entry(const LogEntry& entry) const {
    return entry.message.find("Frame time:") != std::string::npos;
}

bool PerformanceDetector::is_memory_entry(const LogEntry& entry) const {
    return entry.message.find("Allocation spike") != std::string::npos
        || entry.message.find("Out of memory") != std::string::npos;
}

PatternMatch PerformanceDetector::check_frame_time(const LogEntry& entry) const {
    PatternMatch match;
    match.detector_name = name();
    match.related_entries.push_back(entry);

    int frame_time = extract_number_after(entry.message, "Frame time: ");
    int target = extract_number_after(entry.message, "target: ");

    if (frame_time > 0 && target > 0 && frame_time > target * 2) {
        match.description = "Severe frame spike: " + std::to_string(frame_time)
            + "ms (target: " + std::to_string(target) + "ms)";
        match.match_severity = MatchSeverity::High;
    } else if (frame_time > 0 && target > 0 && frame_time > target) {
        match.description = "Frame time above target: " + std::to_string(frame_time)
            + "ms (target: " + std::to_string(target) + "ms)";
        match.match_severity = MatchSeverity::Medium;
    }

    return match;
}

PatternMatch PerformanceDetector::check_memory(const LogEntry& entry) const {
    PatternMatch match;
    match.detector_name = name();
    match.description = "Memory issue: " + entry.message;
    match.related_entries.push_back(entry);

    if (entry.message.find("Out of memory") != std::string::npos) {
        match.match_severity = MatchSeverity::Critical;
    } else {
        match.match_severity = MatchSeverity::Medium;
    }

    return match;
}

std::vector<PatternMatch> PerformanceDetector::detect(const std::vector<LogEntry>& entries) const {
    std::vector<PatternMatch> matches;

    for (const auto& entry : entries) {
        if (is_frame_time_entry(entry)) {
            auto match = check_frame_time(entry);
            if (!match.description.empty()) {
                matches.push_back(match);
            }
        }

        if (is_memory_entry(entry)) {
            matches.push_back(check_memory(entry));
        }
    }

    return matches;
}

}