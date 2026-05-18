#include "game_log_analyzer/pattern_match.h"

namespace game_log_analyzer {

std::string match_severity_to_string(MatchSeverity severity) {
    switch (severity) {
        case MatchSeverity::Low:      return "LOW";
        case MatchSeverity::Medium:   return "MEDIUM";
        case MatchSeverity::High:     return "HIGH";
        case MatchSeverity::Critical: return "CRITICAL";
        default:                      return "UNKNOWN";
    }
}

}