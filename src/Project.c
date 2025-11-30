#include <stdio.h>
#include <time.h>
#include <unistd.h>   // for sleep() on Linux/Unix
#include <stdlib.h>   // for system()

// Function to display current time in HH:MM:SS format
void displayClock() {
    time_t raw_time;
    struct tm *time_info;

    // Get current system time
    time(&raw_time);
    time_info = localtime(&raw_time);

    // Print formatted time
    printf("%02d:%02d:%02d\n",
           time_info->tm_hour,
           time_info->tm_min,
           time_info->tm_sec);
}

int main() {
    while (1) {
        system("clear");   // clears the console (use "cls" on Windows)
        printf("=== Digital Clock ===\n\n");
        displayClock();
        sleep(1);          // wait for 1 second
    }
    return 0;
}