#include "game_log_analyzer/log_parser.h"
#include <fstream>
#include <stdexcept>

namespace game_log_analyzer {

LogEntry LogParser::parse_line(const std::string& line) const {
    
    LogEntry entry;
    std::size_t pos = 0;

    std::size_t start = line.find('[', pos);
    std::size_t end = line.find(']', start);

    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("Invalid log line: missing timestamp");
    }

    entry.timestamp = line.substr(start + 1, end - start - 1);
    pos = end + 1;

    start = line.find('[', pos);
    end = line.find(']', start);
    
    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("Invalid log line: missing severity");
    }

    std::string severity_str = line.substr(start + 1, end - start - 1);
    entry.severity = string_to_severity(severity_str);
    pos = end + 1;

    start = line.find('[', pos);
    end = line.find(']', start);

    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("Invalid log line: missing category");
    }

    entry.category = line.substr(start + 1, end - start - 1);
    pos = end + 1;

    if (pos < line.size() && line[pos] == ' ') {
        pos++;
    }
    entry.message = line.substr(pos);

    return entry;
}

std::vector<LogEntry> LogParser::parse_file(const std::string& file_path) const {

    std::ifstream file(file_path);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + file_path);
    }

    std::vector<LogEntry> entries;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        entries.push_back(parse_line(line));
    }

    return entries;
}

}