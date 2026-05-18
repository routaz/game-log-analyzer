#pragma once

#include <vector>
#include "game_log_analyzer/log_entry.h"
#include "game_log_analyzer/pattern_match.h"

namespace game_log_analyzer {

class IPatternDetector {
public:
    virtual ~IPatternDetector() = default;
    virtual std::string name() const = 0;
    virtual std::vector<PatternMatch> detect(const std::vector<LogEntry>& entries) const = 0;
};

}