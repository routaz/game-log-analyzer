#pragma once

#include <vector>
#include <memory>
#include "game_log_analyzer/log_entry.h"
#include "game_log_analyzer/pattern_match.h"
#include "game_log_analyzer/ipattern_detector.h"

namespace game_log_analyzer {

struct AnalysisReport {
    std::string file_path;
    int total_entries;
    std::vector<PatternMatch> all_matches;
};

class Analyzer {
public:
    void add_detector(std::unique_ptr<IPatternDetector> detector);
    AnalysisReport analyze(const std::vector<LogEntry>& entries, const std::string& file_path) const;

private:
    std::vector<std::unique_ptr<IPatternDetector>> detectors_;
};

}