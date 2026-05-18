#pragma once

#include <string>
#include <vector>
#include "game_log_analyzer/log_entry.h"

namespace game_log_analyzer {

class LogParser {
    
public:
    std::vector<LogEntry> parse_file(const std::string& file_path) const;
    LogEntry parse_line(const std::string& line) const;
};

}