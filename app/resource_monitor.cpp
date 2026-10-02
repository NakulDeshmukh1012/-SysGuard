#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "resource_monitor.h"
#include <sys/statvfs.h>
void showCPUUsage() {
    std::ifstream file("/proc/loadavg");

    if (!file) {
        std::cerr << "Error: Unable to read CPU information.\n";
        return;
    }

    double load1, load5, load15;
    file >> load1 >> load5 >> load15;

    std::cout << "\n========== CPU MONITOR ==========\n";
    std::cout << "Load average (1 min):  " << load1 << '\n';
    std::cout << "Load average (5 min):  " << load5 << '\n';
    std::cout << "Load average (15 min): " << load15 << '\n';
    std::cout << "=================================\n";
}

void showMemoryUsage() {
    std::ifstream file("/proc/meminfo");

    if (!file) {
        std::cerr << "Error: Unable to read memory information.\n";
        return;
    }

    std::string line;
    long total = 0;
    long available = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        long value;

        iss >> key >> value;

        if (key == "MemTotal:")
            total = value;

        if (key == "MemAvailable:")
            available = value;
    }

    std::cout << "\n========== MEMORY MONITOR ==========\n";
    std::cout << "Total Memory:     " << total / 1024 << " MB\n";
    std::cout << "Available Memory: " << available / 1024 << " MB\n";
    std::cout << "Used Memory:      "
              << (total - available) / 1024 << " MB\n";
    std::cout << "====================================\n";
}


void showDiskUsage() {
    struct statvfs disk;

    if (statvfs("/", &disk) != 0) {
        std::cerr << "Error: Unable to read disk information.\n";
        return;
    }

    unsigned long long total =
        static_cast<unsigned long long>(disk.f_blocks) * disk.f_frsize;

    unsigned long long available =
        static_cast<unsigned long long>(disk.f_bavail) * disk.f_frsize;

    unsigned long long used = total - available;

    std::cout << "\n========== DISK MONITOR ==========\n";
    std::cout << "Total Disk:     " << total / (1024 * 1024 * 1024) << " GB\n";
    std::cout << "Used Disk:      " << used / (1024 * 1024 * 1024) << " GB\n";
    std::cout << "Available Disk: " << available / (1024 * 1024 * 1024) << " GB\n";
    std::cout << "==================================\n";
}
