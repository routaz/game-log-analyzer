#include "game_log_analyzer/log_entry.h"

namespace game_log_analyzer {

std::string severity_to_string(Severity severity) {
    switch (severity) {
        case Severity::Info:    return "INFO";
        case Severity::Warning: return "WARN";
        case Severity::Error:   return "ERROR";
        case Severity::Fatal:   return "FATAL";
        default:                return "UNKNOWN";
    }
}

Severity string_to_severity(const std::string& str) {
    if (str == "INFO")  return Severity::Info;
    if (str == "WARN")  return Severity::Warning;
    if (str == "ERROR") return Severity::Error;
    if (str == "FATAL") return Severity::Fatal;
    return Severity::Unknown;
}

}