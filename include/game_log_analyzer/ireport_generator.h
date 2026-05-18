#pragma once

#include <string>
#include "game_log_analyzer/analyzer.h"

namespace game_log_analyzer {

class IReportGenerator {
public:
    virtual ~IReportGenerator() = default;
    virtual std::string name() const = 0;
    virtual void generate(const AnalysisReport& report) const = 0;
};

}