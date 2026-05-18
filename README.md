# GameLogAnalyzer

A C++17 CLI tool that parses game engine log files, detects patterns (crashes, performance issues, errors), and generates reports.

Built with a clean, SOLID architecture: abstract interfaces for detectors and reporters, smart pointer-based polymorphism, and comprehensive unit tests using GoogleTest.

## Features

- **Log Parsing** — Reads timestamped game engine logs with severity levels (INFO, WARN, ERROR, FATAL) and categories
- **Pattern Detection** — Pluggable detector system with three built-in detectors:
  - `CrashDetector` — Identifies fatal errors, access violations, and unhandled exceptions
  - `PerformanceDetector` — Flags frame time spikes and memory pressure (allocation spikes, out-of-memory)
  - `ErrorDetector` — Categorizes non-crash errors by subsystem with severity classification
- **Report Generation** — Pluggable reporter system:
  - `ConsoleReporter` — Formatted terminal output
  - `JsonReporter` — Machine-readable JSON reports

## Architecture

```
┌─────────┐     ┌───────────┐     ┌──────────────────┐     ┌──────────────────┐
│ Log File │────>│ LogParser │────>│    Analyzer       │────>│ IReportGenerator │
└─────────┘     └───────────┘     │                   │     ├──────────────────┤
                                  │ IPatternDetector[] │     │ ConsoleReporter  │
                                  ├───────────────────┤     │ JsonReporter     │
                                  │ CrashDetector     │     └──────────────────┘
                                  │ PerformanceDetector│
                                  │ ErrorDetector      │
                                  └───────────────────┘
```

### SOLID Principles

- **Single Responsibility** — Each detector handles one concern; parser only parses; reporters only report
- **Open/Closed** — New detectors or reporters can be added without modifying existing code
- **Liskov Substitution** — All detectors are interchangeable through the `IPatternDetector` interface
- **Interface Segregation** — Small, focused interfaces (`IPatternDetector`, `IReportGenerator`)
- **Dependency Inversion** — `Analyzer` depends on abstractions, not concrete detector/reporter types

## Building

### Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.14+

### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Run Tests

```bash
cd build
./tests
```

## Usage

```bash
# Console output (default)
./analyzer --file path/to/game.log

# JSON report
./analyzer --file path/to/game.log --format json --output report.json

# Help
./analyzer --help
```

### Expected Log Format

```
[2024-03-15 14:23:01.456] [ERROR] [Rendering] Shader compilation failed: vertex_shadow.glsl
[2024-03-15 14:23:02.001] [FATAL] [Core] Unhandled exception: Access violation at 0x00FF2340
[2024-03-15 14:23:02.100] [INFO] [Physics] Frame time: 48ms (target: 16ms)
```

Each line follows the format: `[timestamp] [SEVERITY] [Category] Message`

## Project Structure

```
game-log-analyzer/
├── CMakeLists.txt
├── README.md
├── include/game_log_analyzer/
│   ├── log_entry.h
│   ├── log_parser.h
│   ├── pattern_match.h
│   ├── ipattern_detector.h
│   ├── crash_detector.h
│   ├── performance_detector.h
│   ├── error_detector.h
│   ├── analyzer.h
│   ├── ireport_generator.h
│   ├── console_reporter.h
│   └── json_reporter.h
├── src/
│   ├── main.cpp
│   ├── log_entry.cpp
│   ├── log_parser.cpp
│   ├── pattern_match.cpp
│   ├── crash_detector.cpp
│   ├── performance_detector.cpp
│   ├── error_detector.cpp
│   ├── analyzer.cpp
│   ├── console_reporter.cpp
│   └── json_reporter.cpp
├── tests/
│   ├── log_entry_test.cpp
│   ├── log_parser_test.cpp
│   ├── crash_detector_test.cpp
│   ├── performance_detector_test.cpp
│   └── error_detector_test.cpp
└── sample_logs/
    └── game_session.log
```

## License

MIT
