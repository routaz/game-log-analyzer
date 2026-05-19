cmake_minimum_required(VERSION 3.14)
project(GameLogAnalyzer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

# --- Main executable ---
add_executable(analyzer
    src/main.cpp
    src/log_entry.cpp
    src/log_parser.cpp
    src/pattern_match.cpp
    src/crash_detector.cpp
    src/performance_detector.cpp
    src/error_detector.cpp
    src/analyzer.cpp
    src/console_reporter.cpp
    src/json_reporter.cpp
    src/html_reporter.cpp
    src/unity_log_parser.cpp
)

# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# --- Tests ---
enable_testing()

add_executable(tests
    tests/log_entry_test.cpp
    tests/log_parser_test.cpp
    tests/crash_detector_test.cpp
    tests/performance_detector_test.cpp
    tests/error_detector_test.cpp
    src/log_entry.cpp
    src/log_parser.cpp
    src/pattern_match.cpp
    src/crash_detector.cpp
    src/performance_detector.cpp
    src/error_detector.cpp
    src/analyzer.cpp
    src/console_reporter.cpp
    src/json_reporter.cpp
    src/html_reporter.cpp
    src/unity_log_parser.cpp
)

target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)