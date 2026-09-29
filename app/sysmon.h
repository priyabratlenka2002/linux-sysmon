#ifndef SYSMON_H
#define SYSMON_H

struct sysmon_data {
    int cpu_load;
    long mem_total;
    long mem_free;
    long uptime;
};

#endif
