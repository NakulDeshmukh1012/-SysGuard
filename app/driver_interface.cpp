#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include "driver_interface.h"

void showDriverStatus() {
    const char* device = "/dev/sysguard";

    int fd = open(device, O_RDONLY);

    if (fd < 0) {
        std::cerr << "Driver unavailable: "
                  << std::strerror(errno) << '\n';
        return;
    }

    char buffer[128] = {0};

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);

    if (bytesRead < 0) {
        std::cerr << "Failed to read from driver.\n";
        close(fd);
        return;
    }

    buffer[bytesRead] = '\0';

    std::cout << "\n========== DRIVER STATUS ==========\n";
    std::cout << "Device: " << device << '\n';
    std::cout << "Response: " << buffer;
    std::cout << "===================================\n";

    close(fd);
}
