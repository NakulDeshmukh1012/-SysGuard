#include <iostream>
#include "system_monitor.h"
#include "process_monitor.h"
#include "resource_monitor.h"
#include "driver_interface.h"
#include "logger.h"
int main() {
logEvent("SysGuard started");
    int choice;

    while (true) {
        
std::cout << "\n========== SYSGUARD ==========\n";
std::cout << "1. System Information\n";
std::cout << "2. CPU Monitor\n";
std::cout << "3. Memory Monitor\n";
std::cout << "4. Process Monitor\n";
std::cout << "5. Search Process\n";
std::cout << "6. Process Control\n";
std::cout << "7. Disk Monitor\n";
std::cout << "8. Event Logs\n";
std::cout << "9. Driver Status\n";
std::cout << "0. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showSystemInfo();
                break;
case 2:
    showCPUUsage();
    break;

case 3:
    showMemoryUsage();
    break;
case 4:
    showProcesses();
break;
case 5:
    searchProcess();
    break;

case 6:
    controlProcess();
    break;
   case 7:
    showDiskUsage();
    break;
case 8:
    showLogs();
    break;
case 9:
    showDriverStatus();
    break;
            case 0:
                std::cout << "Exiting SysGuard...\n";
                return 0;

            default:
                std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
