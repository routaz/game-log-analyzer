#pragma once

#include <string>
#include <vector>
#include "game_log_analyzer/ilog_parser.h"

namespace game_log_analyzer {

class UnityLogParser : public ILogParser {
public:
    std::vector<LogEntry> parse_file(const std::string& file_path) const override;

private:
    LogEntry parse_line(const std::string& line) const;
    Severity parse_unity_severity(const std::string& severity_str) const;
    std::string guess_category(const std::string& message) const;
    bool is_stack_trace_line(const std::string& line) const;
};

}