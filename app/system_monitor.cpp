#include <iostream>
#include <fstream>
#include <string>
#include "system_monitor.h"

void showSystemInfo() {
    std::ifstream file("/proc/uptime");

    if (!file) {
        std::cerr << "Error: Unable to read /proc/uptime\n";
        return;
    }

    double uptime;
    file >> uptime;

    std::cout << "\n========== SYSTEM INFORMATION ==========\n";
    std::cout << "System uptime: " << uptime << " seconds\n";
    std::cout << "Kernel information is available through /proc and /sys.\n";
    std::cout << "========================================\n";
}
