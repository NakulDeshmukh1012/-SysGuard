# SysGuard Testing

## Test Environment

- Operating System: Ubuntu 26.04.1 LTS
- Kernel: 7.0.0-38-generic
- Language: C++17 and C
- Compiler: GCC/G++
- Build System: GNU Make
- Virtualization: VirtualBox

## Functional Tests

| Test | Expected Result | Status |
|---|---|---|
| System Information | Displays system uptime and kernel information | PASS |
| CPU Monitor | Displays CPU load averages | PASS |
| Memory Monitor | Displays total, available and used memory | PASS |
| Process Monitor | Lists running Linux processes | PASS |
| Process Search | Finds processes by name | PASS |
| Process Control | Sends SIGTERM, SIGSTOP and SIGCONT | PASS |
| Disk Monitor | Displays disk capacity and usage | PASS |
| Event Logs | Displays stored SysGuard events | PASS |
| Driver Status | Communicates with `/dev/sysguard` | PASS |

## Driver Tests

### Kernel Module Compilation

```bash
make
