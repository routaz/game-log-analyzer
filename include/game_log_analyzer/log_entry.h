#pragma once

#include <string>

namespace game_log_analyzer{

enum class Severity {
    Info,
    Warning,
    Error,
    Fatal,
    Unknown
};

struct LogEntry{
    std::string timestamp;
    Severity severity;
    std::string category;
    std::string message;
};

std::string severity_to_string(Severity severity);
Severity string_to_severity(const std::string& str);

}