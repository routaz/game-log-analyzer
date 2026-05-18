#pragma once

#include <vector>
#include <string>
#include "game_log_analyzer/ipattern_detector.h"

namespace game_log_analyzer {

class PerformanceDetector : public IPatternDetector {
public:
    std::string name() const override;
    std::vector<PatternMatch> detect(const std::vector<LogEntry>& entries) const override;

private:
    PatternMatch check_frame_time(const LogEntry& entry) const;
    PatternMatch check_memory(const LogEntry& entry) const;
    bool is_frame_time_entry(const LogEntry& entry) const;
    bool is_memory_entry(const LogEntry& entry) const;
    int extract_number_after(const std::string& text, const std::string& prefix) const;
};

}