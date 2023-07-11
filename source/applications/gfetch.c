#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>

void show_system_info()
{
    struct utsname unameData;
    struct sysinfo sysInfo;

    uname(&unameData);
    sysinfo(&sysInfo);

    printf("System name: %s\n", unameData.sysname);
    printf("Node name: %s\n", unameData.nodename);
    printf("Kernel version: %s\n", unameData.release);
    printf("Uptime: %ld seconds\n", sysInfo.uptime);
}

int main()
{
    show_system_info();
    return 0;
}
