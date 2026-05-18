#pragma once

#include <string>
#include "game_log_analyzer/ireport_generator.h"

namespace game_log_analyzer {

class JsonReporter : public IReportGenerator {
public:
    explicit JsonReporter(const std::string& output_path);
    std::string name() const override;
    void generate(const AnalysisReport& report) const override;

private:
    std::string output_path_;
    void create_issue_string(const AnalysisReport& report,std::ofstream& file) const;
};

}