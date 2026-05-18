#include "game_log_analyzer/console_reporter.h"
#include <iostream>

namespace game_log_analyzer {

std::string ConsoleReporter::name() const {
    return "ConsoleReporter";
}

void ConsoleReporter::generate(const AnalysisReport& report) const {
    std::cout << "=== Analysis Report ===" << std::endl;

    std::cout << "File: " << report.file_path << std::endl;
    std::cout << "Total entries: " << report.total_entries << std::endl;
    std::cout << "Issues found: " << report.all_matches.size() << std::endl;

    for (const auto& match : report.all_matches) {
        std::cout << "[" << match_severity_to_string(match.match_severity) << "] "
                  << match.detector_name << ": " << match.description << std::endl;
    }

    std::cout << "=== End of Report ===" << std::endl;
}

}