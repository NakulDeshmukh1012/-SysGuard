# SysGuard

## Linux System & Hardware Monitoring Framework

SysGuard is a Linux-based system monitoring and diagnostic application developed using C++ and a custom Linux character device driver.

The application provides a command-line interface for monitoring system resources, inspecting running processes, controlling processes using Linux signals, maintaining event logs, and communicating with a kernel-space character device.

## Features

- System information monitoring
- CPU load monitoring
- Memory monitoring
- Disk usage monitoring
- Running process monitoring
- Process search by name
- Process control using Linux signals
- Event logging
- Custom Linux character device driver
- User-space to kernel-space communication through `/dev/sysguard`

## Technology Stack

- C++
- C
- Linux
- Linux `/proc` filesystem
- Linux system calls
- Linux signals
- Linux Character Device Driver
- GNU Make
- GCC/G++
- Git

## Architecture

```text
                    SysGuard
                       |
              C++ Command Line App
                       |
       +---------------+---------------+
       |               |               |
 System Monitor   Resource Monitor   Process Monitor
       |               |               |
      /proc           /proc           /proc
                                       |
                                  Linux Signals
                       
                       |
                Driver Interface
                       |
                  /dev/sysguard
                       |
              Character Device Driver
                       |
                  Linux Kernel
## Project Structure
SysGuard/
├── app/
│   ├── main.cpp
│   ├── system_monitor.cpp
│   ├── resource_monitor.cpp
│   ├── process_monitor.cpp
│   ├── logger.cpp
│   └── driver_interface.cpp
│
├── driver/
│   ├── sysguard_driver.c
│   └── Makefile
│
├── include/
│   ├── system_monitor.h
│   ├── resource_monitor.h
│   ├── process_monitor.h
│   ├── logger.h
│   └── driver_interface.h
│
├── logs/
├── Makefile
├── README.md
└── .gitignore
