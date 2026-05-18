#include "game_log_analyzer/json_reporter.h"
#include <iostream>
#include <fstream>

namespace game_log_analyzer
{

    JsonReporter::JsonReporter(const std::string& output_path)
    : output_path_(output_path) {
    }

    std::string JsonReporter::name() const{
        return "JsonReporter";
    }

void JsonReporter::generate(const AnalysisReport& report) const{
    
    std::string file_path = report.file_path;
    int total_issues = report.total_entries;

    std::ofstream file(output_path_);
    file << "{" << std::endl;
    file << "\t\"file\": \"" << report.file_path << "\"," << std::endl;
    file << "\t\"total_entries\": " << total_issues << "," << std::endl;
    file << "\t\"issues\": [" << std::endl;
    create_issue_string(report, file);
    file << "\t]" << std::endl;
    file << "}" << std::endl;

}

void JsonReporter::create_issue_string(const AnalysisReport& report, std::ofstream& file) const {

    for (std::size_t i = 0; i < report.all_matches.size(); i++) {
    const auto& match = report.all_matches[i];
    file << "\t\t{" << std::endl;
    file << "\t\t\t\"severity\": \"" << match_severity_to_string(match.match_severity) << "\"," << std::endl;
    file << "\t\t\t\"detector\": \"" << match.detector_name << "\"," << std::endl;
    file << "\t\t\t\"description\": \"" << match.description << "\"" << std::endl;
    file << "\t\t}";
    if (i < report.all_matches.size() - 1) {
        file << ",";
    }
    file << std::endl;
    }

}
    
}