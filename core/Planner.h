#ifndef PLANNER_H
#define PLANNER_H

#include <QVector>
#include <QDate>
#include <QString>
#include <functional>

#include "Task.h"

class Planner
{
public:
    // ===== BASIC =====
    void addTask(const Task &task);
    void updateTask(int index, const Task &task);
    void removeTask(int index);
    void setCompleted(int index, bool value);

    const QVector<Task>& getTasks() const;

    // ===== FILES =====
    void saveToBinaryFile(const QString &path);
    void loadFromBinaryFile(const QString &path);

    // ===== STATISTICS =====
    int countCompleted() const;
    double averagePriority() const;
    qint64 averageTimeSpent() const;

    // ===== TIMER =====
    void startTaskTimer(int index);
    void stopTaskTimer(int index);

    // ===== SORTING =====
    void sortByPriority();
    void sortByDate();
    void sortByTitle();

    // ===== FILTERING =====
    QVector<Task> filterByPriority(int minPriority) const;
    QVector<Task> filterByCompleted(bool completed) const;
    QVector<Task> filterByDueDate(const QDate &date) const;

    // ===== TEMPLATE =====
    template <typename T>
    int countIf(const QVector<T>& list,
                std::function<bool(const T&)> predicate) const
    {
        int count = 0;

        for (const auto &item : list) {
            if (predicate(item))
                count++;
        }

        return count;
    }

private:
    QVector<Task> tasks;
};

#endif // PLANNER_H
