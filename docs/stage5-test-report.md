# Stage 5: Testing Report

## 1. Functional Testing

| Test | Expected | Result |
|---|---|---|
| insmod loads driver | /dev/sysmonitor appears | Pass |
| Driver returns data | C++ app prints 4 values | Pass |
| rmmod unloads driver | Device file removed, no crash | Pass |
| Repeated load/unload (3x) | No kernel crash or hang | Pass |

## 2. Accuracy Testing

Compared driver output against standard Linux tools:

| Metric | Driver Output | free -k / uptime -p | Notes |
|---|---|---|---|
| Memory Total | 3383744 KB | 3383744 KB | Exact match |
| Memory Free | 205736 KB | 193220 KB | Close; small gap due to timing between commands |
| Uptime | 84305 sec (~23.4 hr) | 23 hours 26 minutes | Matches closely |

## 3. Known Limitations

- CPU load (93%) is approximated from memory usage, not a true CPU
  utilization reading, since real CPU load requires deeper kernel timing
  APIs (per-CPU jiffies). Documented as a Stage 6 improvement idea.

## 4. Reliability Testing

Loaded and unloaded the driver 3 times in a row using a shell loop.
dmesg confirmed clean "driver loaded" / "driver unloaded" messages each
cycle, with no kernel crash or hang.

## 5. Roadmap for Stage 6

- Final polish: improve cpu_load calculation if time permits
- Write the final project report
- Prepare the demo and presentation
- Push final code, docs, and diagrams to GitHub
