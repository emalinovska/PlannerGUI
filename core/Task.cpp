#include "task.h"

// ===== КОНСТРУКТОРЫ =====
Task::Task()
    : title(""),
    dueDate(QDate::currentDate()),
    priority(1),
    completed(false)
{
}

Task::Task(const QString &title)
    : title(title),
    dueDate(QDate::currentDate()),
    priority(1),
    completed(false)
{
}

Task::Task(const QString &title, const QDate &dueDate)
    : title(title),
    dueDate(dueDate),
    priority(1),
    completed(false)
{
}

Task::Task(const QString &title, const QDate &dueDate, int priority, bool completed)
    : title(title),
    dueDate(dueDate),
    priority(priority),
    completed(completed)
{
}

// ===== ГЕТТЕРЫ =====
QString Task::getTitle() const {
    return title;
}

QDate Task::getDueDate() const {
    return dueDate;
}

int Task::getPriority() const {
    return priority;
}

bool Task::isCompleted() const {
    return completed;
}

// ===== СЕТТЕРЫ =====
void Task::setTitle(const QString &title) {
    this->title = title;
}

void Task::setDueDate(const QDate &dueDate) {
    this->dueDate = dueDate;
}

void Task::setPriority(int priority) {
    this->priority = priority;
}

void Task::setCompleted(bool completed) {
    this->completed = completed;
}
