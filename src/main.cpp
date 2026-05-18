#include <iostream>
#include <memory>
#include <string>
#include "game_log_analyzer/log_parser.h"
#include "game_log_analyzer/analyzer.h"
#include "game_log_analyzer/crash_detector.h"
#include "game_log_analyzer/performance_detector.h"
#include "game_log_analyzer/error_detector.h"
#include "game_log_analyzer/console_reporter.h"
#include "game_log_analyzer/json_reporter.h"

void print_usage() {
    std::cout << "Usage: analyzer --file <log_file> [--format <console|json>] [--output <file>]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --file     Path to the log file (required)" << std::endl;
    std::cout << "  --format   Output format: console or json (default: console)" << std::endl;
    std::cout << "  --output   Output file path for json format (default: report.json)" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string file_path;
    std::string format = "console";
    std::string output_path = "report.json";

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--file" && i + 1 < argc) {
            file_path = argv[i + 1];
            i++;
        } else if (arg == "--format" && i + 1 < argc) {
            format = argv[i + 1];
            i++;
        } else if (arg == "--output" && i + 1 < argc) {
            output_path = argv[i + 1];
            i++;
        } else if (arg == "--help") {
            print_usage();
            return 0;
        }
    }

    if (file_path.empty()) {
        std::cout << "Error: --file is required.\n" << std::endl;
        print_usage();
        return 1;
    }

    std::cout << "GameLogAnalyzer v0.1.0\n" << std::endl;

    // Parse the log file
    game_log_analyzer::LogParser parser;
    std::vector<game_log_analyzer::LogEntry> entries;

    try {
        entries = parser.parse_file(file_path);
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Parsed " << entries.size() << " log entries.\n" << std::endl;

    // Set up the analyzer
    game_log_analyzer::Analyzer analyzer;
    analyzer.add_detector(std::make_unique<game_log_analyzer::CrashDetector>());
    analyzer.add_detector(std::make_unique<game_log_analyzer::PerformanceDetector>());
    analyzer.add_detector(std::make_unique<game_log_analyzer::ErrorDetector>());

    auto report = analyzer.analyze(entries, file_path);

    // Generate report
    if (format == "json") {
        game_log_analyzer::JsonReporter reporter(output_path);
        reporter.generate(report);
        std::cout << "JSON report saved to " << output_path << std::endl;
    } else {
        game_log_analyzer::ConsoleReporter reporter;
        reporter.generate(report);
    }

    return 0;
}