#include "Task.h"

// ===== CONSTRUCTORS =====
Task::Task()
    : title(""),
    dueDate(QDate::currentDate()),
    priority(1),
    completed(false),
    timeSpent(0),
    running(false)
{}

Task::Task(const QString &title, const QDate &dueDate, int priority, bool completed)
    : title(title),
    dueDate(dueDate),
    priority(priority),
    completed(completed),
    timeSpent(0),
    running(false)
{}

// ===== GETTERS =====
QString Task::getTitle() const { return title; }
QDate Task::getDueDate() const { return dueDate; }
int Task::getPriority() const { return priority; }
bool Task::isCompleted() const { return completed; }

qint64 Task::getTimeSpent() const { return timeSpent; }
bool Task::isTimerRunning() const { return running; }
QDateTime Task::getStartTime() const { return startTime; }

// ===== SETTERS =====
void Task::setTitle(const QString &title) { this->title = title; }
void Task::setDueDate(const QDate &dueDate) { this->dueDate = dueDate; }
void Task::setPriority(int priority) { this->priority = priority; }
void Task::setCompleted(bool completed) { this->completed = completed; }

// ===== TIMER =====
void Task::startTimer()
{
    if (!running) {
        startTime = QDateTime::currentDateTime();
        running = true;
    }
}

void Task::stopTimer()
{
    if (running) {
        qint64 seconds = startTime.secsTo(QDateTime::currentDateTime());
        timeSpent += seconds;
        running = false;
    }
}


qint64 Task::getCurrentTimeSpent() const {
    if (!running)
        return timeSpent;

    return timeSpent + startTime.secsTo(QDateTime::currentDateTime());
}

void Task::setTimeSpent(qint64 seconds){
    timeSpent = seconds;
}
