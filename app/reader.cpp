#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "sysmon.h"

int main() {
    int fd = open("/dev/sysmonitor", O_RDONLY);
    if (fd < 0) {
        std::cerr << "Error: could not open /dev/sysmonitor" << std::endl;
        std::cerr << "Did you run: sudo insmod sysmon_driver.ko ?" << std::endl;
        return 1;
    }

    sysmon_data data;
    ssize_t n = read(fd, &data, sizeof(data));

    if (n == sizeof(data)) {
        std::cout << "CPU Load: " << data.cpu_load << " %" << std::endl;
        std::cout << "Memory Total: " << data.mem_total << " KB" << std::endl;
        std::cout << "Memory Free: " << data.mem_free << " KB" << std::endl;
        std::cout << "Uptime: " << data.uptime << " seconds" << std::endl;
    } else {
        std::cerr << "Error: could not read data" << std::endl;
    }

    close(fd);
    return 0;
}
