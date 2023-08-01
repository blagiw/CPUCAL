// CPU Usage Calculator for Windows API // 
#include <iostream>
#include <Windows.h>

int main() {
    // Variables to store CPU usage
    double previousIdleTime = 0.0;
    double previousKernelTime = 0.0;
    double previousUserTime = 0.0;

    while (true) {
        // System information
        FILETIME idleTime, kernelTime, userTime;
        if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
            // FILETIME to 64-bit integer for calculations
            ULARGE_INTEGER idle, kernel, user;
            idle.LowPart = idleTime.dwLowDateTime;
            idle.HighPart = idleTime.dwHighDateTime;
            kernel.LowPart = kernelTime.dwLowDateTime;
            kernel.HighPart = kernelTime.dwHighDateTime;
            user.LowPart = userTime.dwLowDateTime;
            user.HighPart = userTime.dwHighDateTime;

            // Calculate CPU percentage usage
            double idleTimeDiff = idle.QuadPart - previousIdleTime;
            double kernelTimeDiff = kernel.QuadPart - previousKernelTime;
            double userTimeDiff = user.QuadPart - previousUserTime;
            double totalTime = kernelTimeDiff + userTimeDiff;
            double cpuUsage = 100.0 * (1.0 - (idleTimeDiff / totalTime));

            // Update previous values for the next iteration
            previousIdleTime = idle.QuadPart;
            previousKernelTime = kernel.QuadPart;
            previousUserTime = user.QuadPart;

            // Display CPU percentage usage
            std::cout << "CPU -> " << cpuUsage << "%" << std::endl;
        }

        // You can adjust the refresh rate if needed
        Sleep(1000);
    }

    return 0;
}
