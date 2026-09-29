# Stage 6: Final Report

## Project: Linux System Monitor with Character Device Driver using C++
### Priyabrata lenka, B.Tech CSE, ITER, SOA University, Bhubaneswar

## 1. Overview

This project implements a Linux character device driver (in C) that exposes
live system statistics through /dev/sysmonitor, and a C++ application that
reads and displays this data. It demonstrates the complete path from kernel
space to user space: kernel data -> driver -> device file -> C++ app -> screen.

## 2. Final Architecture

C++ Application --(open/read)--> /dev/sysmonitor --> Character Device
Driver (C) --> Kernel data (memory info via si_meminfo, uptime via
ktime_get_boottime_seconds)

See docs/stage3.md for full architecture and UML diagrams (class, sequence,
state machine).

## 3. Implementation Summary

- driver/sysmon_driver.c - registers /dev/sysmonitor, implements open,
  read, release; collects real memory and uptime data using kernel APIs;
  approximates CPU load from memory usage.
- driver/sysmon.h - shared data structure (sysmon_data) used by driver and app.
- app/reader.cpp - C++ application that opens the device, reads the
  structure, and prints CPU load, memory total, memory free, and uptime.
- Makefile - builds the kernel module using the standard kbuild system.

## 4. Testing and Results

Full details in docs/stage5-test-report.md. Summary:

| Test | Result |
|---|---|
| Driver load/unload | Pass, clean dmesg logs |
| Device file creation | Pass, /dev/sysmonitor created with correct permissions |
| Data read via C++ app | Pass, matches free -k and uptime -p closely |
| Repeated load/unload (reliability) | Pass, no crash across 3 cycles |

## 5. Achievements

- Built a working Linux character device driver from scratch.
- Implemented the full kernel-to-user-space data path.
- Applied object-oriented design in the C++ application layer.
- Followed a complete requirements -> design -> implementation -> testing
  workflow with Git version control at every stage.
- Verified data accuracy against standard Linux tools.

## 6. Limitations

- CPU load is approximated from memory usage, not true CPU utilization
  (which needs per-CPU jiffies tracking).
- Only three metrics are exposed; per-process statistics are not included.
- No GUI; the interface is command-line only.
- Tested only in a VirtualBox Ubuntu VM, not on physical hardware.

## 7. Future Improvements

- Implement true CPU load using /proc/stat-style jiffies calculation.
- Add per-process monitoring via the ioctl interface (already scoped in
  the driver design).
- Add a live-refreshing display (redraw every second) instead of one-shot read.
- Package as a small ncurses-based dashboard for a nicer terminal UI.
- Add automated unit tests for the C++ application logic.

## 8. Repository Structure

linux-sysmon/
driver/ - kernel module source (C)
app/ - C++ application source
docs/ - all stage documents and diagrams
README.md - project overview and status

## 9. How to Build and Run

cd driver
make
sudo insmod sysmon_driver.ko
sudo chmod 666 /dev/sysmonitor

cd ../app
g++ reader.cpp -o reader
./reader

## cleanup
sudo rmmod sysmon_driver


## 10. Conclusion

The project successfully demonstrates Linux device driver development,
system programming, and C++ application design, following a professional
6-stage development process with continuous documentation and version
control throughout.
