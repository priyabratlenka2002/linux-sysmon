# Stage 2: Requirements and Development Plan

## Project: Linux System Monitor with Character Device Driver using C++

## 1. Functional Requirements

FR1. The driver shall load and unload cleanly (insmod / rmmod).
FR2. The driver shall create the device file /dev/sysmonitor.
FR3. The driver shall support open, read and release operations.
FR4. The driver shall return CPU load, memory usage and uptime.
FR5. The driver shall support an ioctl call to select the metric.
FR6. The C++ application shall open the device and read the data.
FR7. The C++ application shall display live values, refreshed every second.
FR8. The application shall show a clear error if the device is missing.

## 2. Non-Functional Requirements

NFR1. Reliability: no kernel crash on repeated load and unload.
NFR2. Performance: low CPU overhead, one read under 10 ms.
NFR3. Safety: use copy_to_user and a mutex for shared data.
NFR4. Accuracy: values match free and uptime within a small margin.
NFR5. Maintainability: clean, commented code with a clear folder structure.
NFR6. Portability: builds on Ubuntu with standard gcc, g++ and make.

## 3. Scope, Modules and Features

Module 1: Kernel driver (C) - device registration, file operations, data collection.
Module 2: Shared header - one data structure used by driver and app.
Module 3: C++ application - DeviceReader, SystemStats and Display classes.
Module 4: Build and test - Makefile, test script, documentation.

Out of scope: GUI, per-process monitoring, network and disk monitoring.

## 4. Deliverables

- Source code (driver and application) in Git
- Stage documents 1 to 6
- UML diagrams (class, sequence, state machine)
- Test report and screenshots
- Final project report and demo

## 5. Development Plan and Timeline

| Stage | Work | Time |
|---|---|---|
| 1 | Introduction, environment, hello module | Done |
| 2 | Requirements and plan | Day 1-2 |
| 3 | Design, UML, architecture | Day 3-5 |
| 4 | Driver prototype and C++ reader | Week 2 |
| 5 | Real data, testing, fixes | Week 3 |
| 6 | Final demo, report, presentation | Week 4 |

(Adjust the dates to your college deadlines.)

## 6. Risks

- Kernel crashes in the VM: mitigated by VirtualBox snapshots.
- Wrong data in the driver: mitigated by comparing with free and uptime.
- Lost work: mitigated by regular Git commits and pushes.

## 7. Roadmap for Stage 3

- Architecture diagram
- Class, sequence and state machine diagrams
- Data structure definition
- Branching strategy in Git
