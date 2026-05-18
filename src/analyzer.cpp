#include "game_log_analyzer/analyzer.h"

namespace game_log_analyzer {

void Analyzer::add_detector(std::unique_ptr<IPatternDetector> detector) {
    detectors_.push_back(std::move(detector));
}

AnalysisReport Analyzer::analyze(const std::vector<LogEntry>& entries, const std::string& file_path) const {
    AnalysisReport report;
    report.file_path = file_path;
    report.total_entries = static_cast<int>(entries.size());

    for (const auto& detector : detectors_) {
        auto matches = detector->detect(entries);

        for (auto& match : matches) {
            report.all_matches.push_back(std::move(match));
        }
    }

    return report;
}

}