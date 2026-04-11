#ifndef PLANNER_H
#define PLANNER_H

#include <QVector>
#include "Task.h"
#include <functional>

class Planner
{
public:
    void addTask(const Task &task);
    void updateTask(int index, const Task &task);
    void removeTask(int index);
    void setCompleted(int index, bool value);

    const QVector<Task>& getTasks() const;

    bool loadFromFile(const QString &path);
    bool saveToFile(const QString &path) const;
    int countCompleted() const;
    double averagePriority() const;

    template <typename T>
    int countIf(const QVector<T>& list, std::function<bool(const T&)> predicate) const {
        int count = 0;
        for (const auto& item : list) {
            if (predicate(item))
                count++;
        }
        return count;
    }

private:
    QVector<Task> tasks;
};

#endif // PLANNER_H
