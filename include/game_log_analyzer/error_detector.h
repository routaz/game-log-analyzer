#pragma once

#include <vector>
#include <string>
#include "game_log_analyzer/ipattern_detector.h"

namespace game_log_analyzer {

class ErrorDetector : public IPatternDetector {

public:
    std::string name() const override;
    std::vector<PatternMatch> detect(const std::vector<LogEntry>& entries) const override;

private:
    PatternMatch check_error_category(const LogEntry& entry) const;
    MatchSeverity get_severity_for_category(const std::string& category) const;
    std::string build_description(const LogEntry& entry) const;
};   
}