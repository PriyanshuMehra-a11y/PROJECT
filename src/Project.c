#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


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

#define MAX_TASKS 20

typedef struct {
    char name[100];
    int hour24;
    int minute;
    int reminded;
} Task;

void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

void flush_stdin_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int to_24h(int hour12, const char *ampm) {
    char c = tolower((unsigned char)ampm[0]);
    if (c == 'a') return (hour12 == 12) ? 0 : hour12;
    else return (hour12 == 12) ? 12 : hour12 + 12;
}

void display_clock(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    const char *days[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

    printf("=== Digital Clock ===\n");
    printf("%02d-%02d-%04d (%s)\n",
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, days[t->tm_wday]);
    printf("%02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
    printf("=====================\n");
}

void show_task_status(Task tasks[], int count) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int currentSOD = t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec;

    for (int i = 0; i < count; i++) {
        int taskSOD = tasks[i].hour24 * 3600 + tasks[i].minute * 60;
        int diff = taskSOD - currentSOD;

        if (diff < 0) diff += 24 * 3600;

        if (diff == 0) {
            if (!tasks[i].reminded) {
                printf("🔔 Reminder: %s at %02d:%02d — it's time!\n",
                       tasks[i].name, tasks[i].hour24, tasks[i].minute);
                BEEP();
                tasks[i].reminded = 1;
            } else {
                printf("Task: %-20s | At %02d:%02d | Happening now\n",
                       tasks[i].name, tasks[i].hour24, tasks[i].minute);
            }
        } else {
            int dh = diff / 3600;
            int dm = (diff % 3600) / 60;
            int ds = diff % 60;
            printf("Task: %-20s | At %02d:%02d | Starts in %02d:%02d:%02d\n",
                   tasks[i].name, tasks[i].hour24, tasks[i].minute, dh, dm, ds);
            if (tasks[i].reminded && diff > 60) tasks[i].reminded = 0;
        }
    }
}

int main(void) {
    Task tasks[MAX_TASKS] = {0};
    int taskCount = 0;

    printf("How many tasks do you want to add today (1-%d)? ", MAX_TASKS);
    if (scanf("%d", &taskCount) != 1 || taskCount < 1 || taskCount > MAX_TASKS) {
        fprintf(stderr, "Invalid task count.\n");
        return 1;
    }
    flush_stdin_line();

    for (int i = 0; i < taskCount; i++) {
        printf("Enter task %d name: ", i + 1);
        if (!fgets(tasks[i].name, sizeof(tasks[i].name), stdin)) {
            fprintf(stderr, "Input error.\n");
            return 1;
        }
        trim_newline(tasks[i].name);
        if (tasks[i].name[0] == '\0') snprintf(tasks[i].name, sizeof(tasks[i].name), "Task %d", i + 1);

        int hour12 = 0, minute = 0;
        char ampm[3] = {0};

        while (1) {
            printf("Enter time for \"%s\" (HH MM AM/PM): ", tasks[i].name);
            if (scanf("%d %d %2s", &hour12, &minute, ampm) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                flush_stdin_line();
                continue;
            }
            flush_stdin_line();

            char c = tolower((unsigned char)ampm[0]);
            if (hour12 < 1 || hour12 > 12 || minute < 0 || minute > 59 || !(c == 'a' || c == 'p')) {
                printf("Please enter valid time (1–12 hour, 0–59 minute, AM or PM).\n");
                continue;
            }
            tasks[i].hour24 = to_24h(hour12, ampm);
            tasks[i].minute = minute;
            tasks[i].reminded = 0;
            break;
        }
    }

    // Run clock update exactly 6 times
    for (int i = 0; i < 4; i++) {
        CLEAR();
        display_clock();
        printf("----- Today’s Tasks -----\n");
        show_task_status(tasks, taskCount);
        printf("-------------------------\n");

        fflush(stdout);
        PAUSE_1S();
    }

    printf("\nClock stopped after 6 updates.\n");
    return 0;
}
