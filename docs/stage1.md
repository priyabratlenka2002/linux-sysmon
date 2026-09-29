# Stage 1: Project Introduction

## Linux System Monitor with Character Device Driver using C++

Student: Priyabrata Lenka
Programme: B.Tech CSE (2023-2027), ITER, Siksha 'O' Anusandhan University, Bhubaneswar

## 1. Project Idea and Objective

This project builds a system monitor in two parts:

1. A Linux character device driver (kernel module, written in C) that creates the device file /dev/sysmonitor and provides live system information from inside the kernel.
2. A C++ user-space application that opens /dev/sysmonitor, reads the data using an object-oriented design, and displays live system statistics.

Objective: To understand and demonstrate how a user program communicates with the Linux kernel through a device driver, and to follow a professional development process from requirements to final delivery.

## 2. Problem Statement

User programs run in a protected area and cannot read kernel-level data directly. The kernel needs a safe, controlled interface to share this information. Existing tools such as top and free hide this mechanism, so it is hard to learn how the interface really works.

This project builds such an interface from scratch: user application -> device file -> driver -> kernel data.

## 3. Project Scope

Included:
- Linux kernel module in C (character device driver)
- Device file /dev/sysmonitor
- Metrics: CPU load, memory usage, system uptime
- Driver operations: open, read, release, ioctl
- C++ command-line application with a live refresh loop
- Error handling, testing, documentation, UML diagrams, Git

Not included:
- Graphical user interface
- Per-process monitoring
- Network and disk monitoring

Environment: Windows 11 laptop, VirtualBox, Ubuntu VM, gcc, g++, make, git.

## 4. Expected Outcome

- A working kernel module that creates /dev/sysmonitor
- A C++ application that shows live CPU, memory and uptime values
- Test results compared with standard tools (free, uptime)
- Documents for all 6 stages, UML diagrams and a Git history

## 5. Applications

- Learning Linux device driver development and system programming
- Base for embedded and system-level monitoring tools
- Foundation for tools similar to top and htop

## 6. Progress Evidence

- Development environment ready (Ubuntu VM, gcc, g++, git): Done
- First hello kernel module built and loaded: Done
- Git repository created and pushed to GitHub: Done
- Screenshot: stage1-build.jpeg (build, insmod, rmmod, dmesg)

## 7. Roadmap for Stage 2

- Write the Project Requirements Document (functional and non-functional)
- Define modules, features and deliverables
- Prepare the development plan and timeline
