# Digital Clock Application (C Project)

The **Digital Clock Application** is a menu‑driven C program designed to display and manage time in a digital format. It continuously shows the current system time in **HH:MM:SS** format, refreshing every second. The program is developed using a **modular programming approach**, separating the logic into different `.c` and `.h` files for clarity and maintainability. Standard C libraries (`time.h`, `unistd.h`, `stdlib.h`) are used to fetch system time, control delays, and clear the console for a real‑time clock effect.  

The project has been implemented according to standard academic guidelines, including **problem definition, system requirements, flowchart, implementation details, testing, sample output, and conclusion.**

---

## Features
- Display current system time in **HH:MM:SS** format  
- Real‑time update every second  
- Option to switch between **12‑hour and 24‑hour formats**  
- Modular program structure using functions and header files  
- Console cleared and refreshed for a dynamic digital clock effect  

---

## ⚙️ How the Program Works
When the program starts, a menu is displayed to the user. Based on the selected option, the program performs the corresponding operation:

- **Start Clock**: The program continuously fetches system time using `time()` and `localtime()`, then displays it in formatted output.  
- **Switch Format**: The user can toggle between 12‑hour (AM/PM) and 24‑hour display.  
- **Exit**: The program terminates gracefully.  

The clock refreshes every second using the `sleep()` function, while `system("clear")` (or `system("cls")` on Windows) ensures the console is updated dynamically.

---

## Technologies Used
| Component              | Details                                |
|------------------------|----------------------------------------|
| Programming Language   | C                                      |
| Time Source            | System time (`time.h`)                 |
| IDE Used               | VS Code / CodeBlocks / Turbo C         |
| Concepts Used          | Time handling, functions, header files |


## Project Structure

The Digital Clock Application demonstrates the use of **modular programming, time handling, and console manipulation** in C. It provides a simple yet effective way to display real‑time system time, making it a useful academic project for learning **file separation, function design, and dynamic console output.**

