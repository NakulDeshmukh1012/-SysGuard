#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"

const std::string LOG_FILE = "logs/sysguard.log";

void logEvent(const std::string& message) {
    std::ofstream file(LOG_FILE, std::ios::app);

    if (!file) {
        std::cerr << "Error: Unable to open log file.\n";
        return;
    }

    file << message << '\n';
}

void showLogs() {
    std::ifstream file(LOG_FILE);

    if (!file) {
        std::cout << "\nNo logs available.\n";
        return;
    }

    std::string line;

    std::cout << "\n========== EVENT LOGS ==========\n";

    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    std::cout << "================================\n";
}
