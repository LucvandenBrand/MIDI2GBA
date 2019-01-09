#include <iostream>
#include <fstream>
#include "main.hpp"
#include "lib/cxxopts/cxxopts.hpp"
#include "log/logger.hpp"

void printHeader() {
    cout << PROGRAM_NAME << " v" << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH
         << " by " << AUTHOR << endl;
}

string pathToName(string path) {
    const size_t last_slash_idx = path.find_last_of("\\/");
    if (string::npos != last_slash_idx)
        path.erase(0, last_slash_idx + 1);

    const size_t period_idx = path.rfind('.');
    if (string::npos != period_idx)
        path.erase(period_idx);

    return path;
}

int main(int argc, char **argv)
{
    auto logger = Logger::getInstance();
    auto &log = *logger;

    vector<string> filePaths;
    bool toBinary = false;

    try {
        cxxopts::Options options(argv[0], "Allows you to convert MIDI music to GBA compatible data.");

        options.allow_unrecognised_options().add_options()
                        ("h, help", "Print this help screen.")
                        ("v, verbose", "Print all log messages.")
                        ("w, warn", "Only print warnings and error messages.")
                        ("n, files", "File paths.", cxxopts::value<vector<string>>());

        options.parse_positional({"files"});

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            printHeader();
            cout << options.help() << endl;
            return EXIT_SUCCESS;
        }

        if (result.count("verbose")) {
            printHeader();
            logger->setLogLevel(INFO);
        } else if (result.count("warn")) {
            logger->setLogLevel(WARN);
        } else {
            logger->setLogLevel(ERROR);
        }

        if (result.count("files"))
            filePaths = result["files"].as<vector<string>>();

    } catch (const cxxopts::OptionException& e) {
        log(ERROR, e.what());
        exit(EXIT_FAILURE);
    }

    if (filePaths.size() < 3 && !(toBinary && filePaths.size() > 1)) {
        log(ERROR, "Please provide input and output files as positional arguments.");
        return EXIT_FAILURE;
    }

    string midiPath = filePaths[0];

    return EXIT_SUCCESS;
}