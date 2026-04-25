# PlannerGUI

A desktop task management application built with **C++** and **Qt**.
Designed to help users organize tasks, track time, and improve productivity.

## Features

* Add, edit, and delete tasks
* Mark tasks as completed
* Filter tasks by date and priority
* Sort tasks in the table
* Track time spent on each task (live timer)
* 📊 Display statistics:
** Total tasks
** Completed tasks
** Average priority
** Average time spent
* User login and registration
* Multiple UI themes(Light, Dark, Blue, Pastel)

## Build instructions

1) Open the project in Qt Creator
2) Select:
* Qt 6
* MinGW 64-bit compiler
3) Build in Release mode

## Run

Run the generated `.exe` file after building.

## Project Structure
PlannerGUI/
│── core/          # Task & Planner logic
│── ui/            # UI (MainWindow, dialogs)
│── data/          # User data (JSON + binary)
│── themes/        # UI themes (QSS)
## Highlights
* Binary file storage for tasks
* Real-time task timer
* Clean and responsive UI
* Multi-user support
## Future Improvements
* Pomodoro mode
* Charts & analytics
* Cloud sync
* Notifications
