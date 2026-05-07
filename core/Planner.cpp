#include "Planner.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <algorithm>
#include <cstring>

// ================= GET TASKS =================
const QVector<Task>& Planner::getTasks() const
{
    return tasks;
}

// ================= ADD TASK =================
void Planner::addTask(const Task &task)
{
    tasks.append(task);
}

// ================= REMOVE TASK =================
void Planner::removeTask(int index)
{
    if (index >= 0 && index < tasks.size()) {
        tasks.removeAt(index);
    }
}

// ================= UPDATE TASK =================
void Planner::updateTask(int index, const Task &task)
{
    if (index >= 0 && index < tasks.size()) {
        tasks[index] = task;
    }
}

// ================= COMPLETE TASK =================
void Planner::setCompleted(int index, bool done)
{
    if (index >= 0 && index < tasks.size()) {
        tasks[index].setCompleted(done);
    }
}

// ================= TIMER CONTROL =================
void Planner::startTaskTimer(int index)
{
    if (index >= 0 && index < tasks.size()) {
        tasks[index].startTimer();
    }
}

void Planner::stopTaskTimer(int index)
{
    if (index >= 0 && index < tasks.size()) {
        tasks[index].stopTimer();
    }
}

// ================= SORTING =================

// Sort tasks by priority (highest first)
void Planner::sortByPriority()
{
    std::sort(tasks.begin(), tasks.end(),
              [](const Task &a, const Task &b)
              {
                  return a.getPriority() > b.getPriority();
              });
}

// Sort tasks by due date (nearest first)
void Planner::sortByDate()
{
    std::sort(tasks.begin(), tasks.end(),
              [](const Task &a, const Task &b)
              {
                  return a.getDueDate() < b.getDueDate();
              });
}
void Planner::sortByTitle()
{
    std::sort(tasks.begin(), tasks.end(),
              [](const Task &a, const Task &b)
              {
                  return a.getTitle().toLower()
                  < b.getTitle().toLower();
              });
}

// ================= FILTERING =================

// Filter tasks by minimum priority
QVector<Task> Planner::filterByPriority(int minPriority) const
{
    QVector<Task> result;

    for (const Task &t : tasks) {
        if (t.getPriority() >= minPriority)
            result.append(t);
    }

    return result;
}

// Filter tasks by completion status
QVector<Task> Planner::filterByCompleted(bool completed) const
{
    QVector<Task> result;

    for (const Task &t : tasks) {
        if (t.isCompleted() == completed)
            result.append(t);
    }

    return result;
}

// Filter tasks by due date
QVector<Task> Planner::filterByDueDate(const QDate &date) const
{
    QVector<Task> result;

    for (const Task &t : tasks) {
        if (t.getDueDate() == date)
            result.append(t);
    }

    return result;
}

// ================= SUMMARY =================

// Calculate average priority
double Planner::averagePriority() const
{
    if (tasks.isEmpty())
        return 0;

    int sum = 0;

    for (const Task &t : tasks) {
        sum += t.getPriority();
    }

    return static_cast<double>(sum) / tasks.size();
}

// Calculate average time spent
qint64 Planner::averageTimeSpent() const
{
    if (tasks.isEmpty())
        return 0;

    qint64 total = 0;

    for (const Task &t : tasks) {
        total += t.getCurrentTimeSpent();
    }

    return total / tasks.size();
}
// ================= SAVE TO BINARY FILE =================
void Planner::saveToBinaryFile(const QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Cannot save file:" << path;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);

    // File header
    out.writeRawData("TSK1", 4);

    qint32 size = tasks.size();
    out << size;

    for (const Task &t : tasks) {

        out << t.getTitle()
        << t.getDueDate()
        << t.getPriority()
        << t.isCompleted()
        << t.getTimeSpent()
        << t.isTimerRunning()
        << t.getStartTime();
    }

    file.close();

    qDebug() << "Saved tasks:" << size;
    qDebug() << "Saving to:" << path;
}

// ================= LOAD FROM BINARY FILE =================
void Planner::loadFromBinaryFile(const QString &path)
{
    QFile file(path);

    if (!file.exists()) {
        qDebug() << "File does not exist:" << path;
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file:" << path;
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    tasks.clear();

    // Read header
    char header[4];
    in.readRawData(header, 4);

    if (strncmp(header, "TSK1", 4) != 0) {
        qDebug() << "Invalid binary file!";
        file.close();
        return;
    }

    qint32 size;
    in >> size;

    qDebug() << "Tasks to load:" << size;

    for (int i = 0; i < size; ++i) {

        QString title;
        QDate dueDate;
        int priority;
        bool completed;

        qint64 timeSpent;
        bool running;
        QDateTime startTime;

        in >> title
            >> dueDate
            >> priority
            >> completed
            >> timeSpent
            >> running
            >> startTime;

        Task task(title, dueDate, priority, completed);

        // Restore timer progress
        if (running) {

            qint64 extraSeconds =
                startTime.secsTo(QDateTime::currentDateTime());

            timeSpent += extraSeconds;
        }

        task.setTimeSpent(timeSpent);

        tasks.append(task);
    }

    file.close();

    qDebug() << "Loaded tasks:" << tasks.size();
    qDebug() << "Loading from:" << path;
}