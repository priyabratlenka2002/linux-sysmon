# Stage 3: System Design and Architecture

## 1. Architecture

```mermaid
graph LR
    A[C++ Application] -->|read/ioctl| B[/dev/sysmonitor/]
    B --> C[Character Device Driver - C]
    C --> D[Kernel Data: CPU, Memory, Uptime]
```

The application opens the device file, the driver reads live kernel data,
and returns it through the read and ioctl operations.

## 2. Components and Responsibilities

- Driver (C): registers the device, implements open/read/release/ioctl,
  collects CPU, memory and uptime data, protects shared data with a mutex.
- Shared header (sysmon.h): defines the data structure and ioctl commands
  used by both the driver and the application.
- C++ Application: DeviceReader (opens and reads the device), SystemStats
  (stores the values), Display (prints them to the screen).

## 3. Data Structure

```c
struct sysmon_data {
    int cpu_load;      // percentage
    long mem_total;    // KB
    long mem_free;     // KB
    long uptime;       // seconds
};
```

## 4. Class Diagram (C++ application)

```mermaid
classDiagram
    class DeviceReader {
        -int fd
        +open() bool
        +readStats() SystemStats
        +close() void
    }
    class SystemStats {
        -int cpuLoad
        -long memTotal
        -long memFree
        -long uptime
        +getCpuLoad() int
        +getMemUsage() long
    }
    class Display {
        +show(SystemStats) void
    }
    DeviceReader --> SystemStats
    Display --> SystemStats
```

## 5. Sequence Diagram

```mermaid
sequenceDiagram
    participant App as C++ App
    participant Dev as /dev/sysmonitor
    participant Drv as Driver
    App->>Dev: open()
    Dev->>Drv: open callback
    App->>Dev: read()
    Dev->>Drv: read callback
    Drv->>Drv: collect CPU/mem/uptime
    Drv-->>Dev: copy_to_user(data)
    Dev-->>App: return data
    App->>App: display on screen
```

## 6. State Machine Diagram (driver lifecycle)

```mermaid
stateDiagram-v2
    [*] --> Unloaded
    Unloaded --> Loaded: insmod
    Loaded --> Opened: open()
    Opened --> Reading: read()
    Reading --> Opened: data returned
    Opened --> Loaded: release()
    Loaded --> Unloaded: rmmod
```

## 7. Implementation Plan

1. Register the character device and add open/release (Stage 4).
2. Implement read() with dummy data, then real data (Stage 4).
3. Add the ioctl to select a metric (Stage 4-5).
4. Write the C++ classes and connect them to the device (Stage 4).
5. Test and compare with free/uptime (Stage 5).

## 8. Development Environment (already set up)

- Ubuntu VM (VirtualBox), gcc, g++, make, git, kernel headers.
- Git branches: main, develop, feature/driver.

## 9. Roadmap for Stage 4

- Register the character device.
- Implement open, read, release.
- Return dummy data first, then real data.
- Build the first version of the C++ reader.
