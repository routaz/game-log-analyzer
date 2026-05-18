#pragma once

#include <string>
#include <vector>
#include "game_log_analyzer/log_entry.h"

namespace game_log_analyzer {

enum class MatchSeverity {
    Low,
    Medium,
    High,
    Critical
};

struct PatternMatch {
    std::string detector_name;
    std::string description;
    MatchSeverity match_severity;
    std::vector<LogEntry> related_entries;
};

std::string match_severity_to_string(MatchSeverity severity);

}