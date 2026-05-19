#pragma once

#include <string>
#include "game_log_analyzer/ireport_generator.h"

namespace game_log_analyzer {

class HtmlReporter : public IReportGenerator {
public:
    explicit HtmlReporter(const std::string& output_path);
    std::string name() const override;
    void generate(const AnalysisReport& report) const override;

private:
    std::string output_path_;
    std::string severity_to_color(MatchSeverity severity) const;
};

}