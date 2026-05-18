#pragma once

#include <vector>
#include <string>
#include "game_log_analyzer/ipattern_detector.h"

namespace game_log_analyzer {

class CrashDetector : public IPatternDetector {
public:
    std::string name() const override;
    std::vector<PatternMatch> detect(const std::vector<LogEntry>& entries) const override;

private:
    bool is_crash_entry(const LogEntry& entry) const;
};

}