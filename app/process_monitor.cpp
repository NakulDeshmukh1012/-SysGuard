#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "process_monitor.h"
#include <csignal>
namespace fs = std::filesystem;

void showProcesses() {
    std::cout << "\n========== PROCESS MONITOR ==========\n";
    std::cout << "PID\tProcess\n";
    std::cout << "-------------------------------------\n";

    int count = 0;

    for (const auto& entry : fs::directory_iterator("/proc")) {

        if (!entry.is_directory())
            continue;

        std::string pid = entry.path().filename().string();

        if (pid.empty() || !isdigit(pid[0]))
            continue;

        std::ifstream file(entry.path() / "comm");

        if (file) {
            std::string name;
            std::getline(file, name);

            std::cout << pid << "\t" << name << '\n';

            count++;

            if (count >= 20)
                break;
        }
    }

    std::cout << "-------------------------------------\n";
    std::cout << "Showing first 20 processes.\n";
}
void searchProcess() {
    std::string target;
    std::cout << "\nEnter process name to search: ";
    std::cin >> target;

    bool found = false;

    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (!entry.is_directory())
            continue;

        std::string pid = entry.path().filename().string();

        if (pid.empty() || !isdigit(pid[0]))
            continue;

        std::ifstream file(entry.path() / "comm");

        if (file) {
            std::string name;
            std::getline(file, name);

            if (name.find(target) != std::string::npos) {
                std::cout << "PID: " << pid
                          << "  Process: " << name << '\n';
                found = true;
            }
        }
    }

    if (!found)
        std::cout << "Process not found.\n";
}
void controlProcess() {
    int pid;
    int signalChoice;

    std::cout << "\nEnter PID: ";
    std::cin >> pid;

    std::cout << "1. Terminate Process\n";
    std::cout << "2. Stop Process\n";
    std::cout << "3. Continue Process\n";
    std::cout << "Select: ";
    std::cin >> signalChoice;

    int signalValue;

    switch (signalChoice) {
        case 1:
            signalValue = SIGTERM;
            break;

        case 2:
            signalValue = SIGSTOP;
            break;

        case 3:
            signalValue = SIGCONT;
            break;

        default:
            std::cout << "Invalid choice.\n";
            return;
    }

    if (kill(pid, signalValue) == 0)
        std::cout << "Signal sent successfully.\n";
    else
        std::cout << "Failed to send signal. Check PID and permissions.\n";
}
