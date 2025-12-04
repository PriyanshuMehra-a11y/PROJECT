#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR() system("cls")
    #define PAUSE_1S() Sleep(1000)
    #define BEEP() Beep(1000, 300)
#else
    #include <unistd.h>
    #define CLEAR() system("clear")
    #define PAUSE_1S() sleep(1)
    #define BEEP() printf("\a")
#endif

// Struct for tasks
typedef struct {
    char name[100];
    int hour24;
    int minute;
    int reminded;
} Task;

