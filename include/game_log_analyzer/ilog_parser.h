#pragma once

#include <string>
#include <vector>
#include "game_log_analyzer/log_entry.h"

namespace game_log_analyzer {

class ILogParser {
public:
    virtual ~ILogParser() = default;
    virtual std::vector<LogEntry> parse_file(const std::string& file_path) const = 0;
};

}