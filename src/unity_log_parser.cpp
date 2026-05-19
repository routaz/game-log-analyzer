#include "game_log_analyzer/unity_log_parser.h"
#include <fstream>
#include <stdexcept>

namespace game_log_analyzer {

Severity UnityLogParser::parse_unity_severity(const std::string& severity_str) const {
    if (severity_str == "INFO") return Severity::Info;
    if (severity_str == "WARNING") return Severity::Warning;
    if (severity_str == "ERROR") return Severity::Error;
    if (severity_str == "FATAL") return Severity::Fatal;
    return Severity::Unknown;
}

std::string UnityLogParser::guess_category(const std::string& message) const {
    if (message.find("Shader") != std::string::npos) return "Rendering";
    if (message.find("draw calls") != std::string::npos) return "Rendering";
    if (message.find("Memory") != std::string::npos) return "Memory";
    if (message.find("Asset") != std::string::npos) return "Assets";
    if (message.find("Exception") != std::string::npos) return "Core";
    if (message.find("Frame time") != std::string::npos) return "Performance";
    return "General";
}

bool UnityLogParser::is_stack_trace_line(const std::string& line) const {
    // Stack traces start with whitespace
    return !line.empty() && (line[0] == ' ' || line[0] == '\t');
}

LogEntry UnityLogParser::parse_line(const std::string& line) const {
    LogEntry entry;

    entry.timestamp = line.substr(0, 19);

    std::size_t start = line.find('[');
    std::size_t end = line.find(']', start);

    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("Invalid Unity log line: missing severity");
    }

    std::string severity_str = line.substr(start + 1, end - start - 1);
    entry.severity = parse_unity_severity(severity_str);

    std::size_t pos = end + 1;
    if (pos < line.size() && line[pos] == ' ') {
        pos++;
    }
    entry.message = line.substr(pos);

    entry.category = guess_category(entry.message);

    return entry;
}

std::vector<LogEntry> UnityLogParser::parse_file(const std::string& file_path) const {
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

        if (is_stack_trace_line(line) && !entries.empty()) {
            entries.back().message += "\n" + line;
        } else {
            entries.push_back(parse_line(line));
        }
    }

    return entries;
}

}