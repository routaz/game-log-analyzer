#include "game_log_analyzer/html_reporter.h"
#include <fstream>

namespace game_log_analyzer {

HtmlReporter::HtmlReporter(const std::string& output_path)
    : output_path_(output_path) {
}

std::string HtmlReporter::name() const {
    return "HtmlReporter";
}

std::string HtmlReporter::severity_to_color(MatchSeverity severity) const {
    switch (severity) {
        case MatchSeverity::Critical: return "#dc3545";
        case MatchSeverity::High:     return "#fd7e14";
        case MatchSeverity::Medium:   return "#ffc107";
        case MatchSeverity::Low:      return "#28a745";
        default:                      return "#6c757d";
    }
}

void HtmlReporter::generate(const AnalysisReport& report) const {
    std::ofstream file(output_path_);

    // Head section — page title and styling
    file << "<!DOCTYPE html>" << std::endl;
    file << "<html>" << std::endl;
    file << "<head>" << std::endl;
    file << "<title>GameLogAnalyzer Report</title>" << std::endl;
    file << "<style>" << std::endl;
    file << "  body { font-family: Arial, sans-serif; margin: 40px; background: #1a1a2e; color: #e0e0e0; }" << std::endl;
    file << "  h1 { color: #00d4ff; }" << std::endl;
    file << "  .summary { margin: 20px 0; font-size: 16px; }" << std::endl;
    file << "  table { border-collapse: collapse; width: 100%; margin-top: 20px; }" << std::endl;
    file << "  th { background: #16213e; padding: 12px; text-align: left; border-bottom: 2px solid #00d4ff; }" << std::endl;
    file << "  td { padding: 10px 12px; border-bottom: 1px solid #2a2a4a; }" << std::endl;
    file << "  tr:hover { background: #16213e; }" << std::endl;
    file << "  .badge { padding: 4px 10px; border-radius: 4px; color: white; font-weight: bold; font-size: 13px; }" << std::endl;
    file << "</style>" << std::endl;
    file << "</head>" << std::endl;

    // Body section — the actual content
    file << "<body>" << std::endl;
    file << "<h1>GameLogAnalyzer Report</h1>" << std::endl;

    // Summary info
    file << "<div class=\"summary\">" << std::endl;
    file << "  <p>File: " << report.file_path << "</p>" << std::endl;
    file << "  <p>Total entries: " << report.total_entries << "</p>" << std::endl;
    file << "  <p>Issues found: " << report.all_matches.size() << "</p>" << std::endl;
    file << "</div>" << std::endl;

    // Issues table
    file << "<table>" << std::endl;
    file << "<tr><th>Severity</th><th>Detector</th><th>Description</th></tr>" << std::endl;

    for (const auto& match : report.all_matches) {
        std::string color = severity_to_color(match.match_severity);
        std::string severity = match_severity_to_string(match.match_severity);

        file << "<tr>" << std::endl;
        file << "  <td><span class=\"badge\" style=\"background:" << color << "\">"
             << severity << "</span></td>" << std::endl;
        file << "  <td>" << match.detector_name << "</td>" << std::endl;
        file << "  <td>" << match.description << "</td>" << std::endl;
        file << "</tr>" << std::endl;
    }

    file << "</table>" << std::endl;
    file << "</body>" << std::endl;
    file << "</html>" << std::endl;
}

}