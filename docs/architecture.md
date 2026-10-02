# SysGuard Architecture

## 1. System Overview

SysGuard follows a modular layered architecture consisting of a user-space C++ application and a Linux kernel-space character device driver.

The application provides monitoring and process-management functionality, while the driver demonstrates controlled communication between user space and kernel space.

## 2. High-Level Architecture

```text
                    USER
                     |
                     v
          +----------------------+
          |   SysGuard CLI       |
          |      C++ App         |
          +----------+-----------+
                     |
       +-------------+-------------+
       |             |             |
       v             v             v
+-------------+ +-------------+ +-------------+
| System      | | Resource    | | Process     |
| Monitor     | | Monitor     | | Monitor     |
+-------------+ +-------------+ +-------------+
       |             |             |
       +-------------+-------------+
                     |
                     v
              Linux Interfaces
              /proc and system calls

                     |
                     v
          +----------------------+
          | Driver Interface     |
          |    C++ Module        |
          +----------+-----------+
                     |
                     v
              /dev/sysguard
                     |
                     v
          +----------------------+
          | SysGuard Character   |
          | Device Driver        |
          +----------+-----------+
                     |
                     v
              Linux Kernel


##3. Application Modules

System Monitor
Obtains system information from Linux virtual filesystems such as /proc.
Resource Monitor
Provides CPU, memory and disk monitoring.
Process Monitor
Scans /proc, identifies process IDs and reads process information.
It also supports process searching and process control using Linux signals.
Logger
Records SysGuard events in a log file.
Driver Interface
Provides the user-space interface for communicating with /dev/sysguard.

##4. Kernel Driver

The SysGuard driver is implemented as a Linux kernel module and registered as a character device.
The driver provides:
- Character-device registration
- Device creation
- Open operation
- Read operation
- Release operation
- User-space data transfer using copy_to_user()
The resulting device is exposed as:
/dev/sysguard

##5. Communication Flow

C++ Application
      |
      | open()
      v
/dev/sysguard
      |
      v
Character Driver
      |
      | read()
      v
Kernel-space driver
      |
      | copy_to_user()
      v
C++ Application

##6. Process Control Flow

User selects process
        |
        v
Enter PID
        |
        v
SysGuard calls kill()
        |
        v
Linux signal
        |
        v
Target process

Supported signals:
- SIGTERM
- SIGSTOP

- SIGCONT

##7. Design Principles

- Modular separation of functionality
- Clear user-space/kernel-space boundary
- Linux-native interfaces
- Minimal kernel-space logic
- Error checking for system operations
- Separation of monitoring, logging and driver communication
