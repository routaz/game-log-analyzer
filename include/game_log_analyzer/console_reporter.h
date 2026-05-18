#pragma once

#include "game_log_analyzer/ireport_generator.h"

namespace game_log_analyzer {

class ConsoleReporter : public IReportGenerator {
public:
    std::string name() const override;
    void generate(const AnalysisReport& report) const override;
};

}