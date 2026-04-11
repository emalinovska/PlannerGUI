#include "Planner.h"
#include <QFile>
#include <QTextStream>

void Planner::addTask(const Task &task)
{
    tasks.append(task);
}

void Planner::updateTask(int index, const Task &task)
{
    if (index >= 0 && index < tasks.size())
        tasks[index] = task;
}

void Planner::removeTask(int index)
{
    if (index >= 0 && index < tasks.size())
        tasks.removeAt(index);
}

const QVector<Task>& Planner::getTasks() const
{
    return tasks;
}

void Planner::setCompleted(int index, bool value)
{
    if (index >= 0 && index < tasks.size())
        tasks[index].setCompleted(value);
}

bool Planner::loadFromFile(const QString &path)
{
    tasks.clear();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");

        // title;date
        if (parts.size() == 2) {
            parts.append("1");  // default priority
            parts.append("0");  // default completed
        }

        // title;date;priority
        if (parts.size() == 3) {
            parts.append("0");  // default completed
        }

        // если всё равно не 4 — пропускаем
        if (parts.size() != 4)
            continue;

        QString title = parts[0];
        QDate date = QDate::fromString(parts[1], "yyyy-MM-dd");
        int priority = parts[2].toInt();
        bool completed = (parts[3] == "1");

        tasks.append(Task(title, date, priority, completed));
    }

    return true;
}

bool Planner::saveToFile(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for (const Task &t : tasks) {
        out << t.getTitle() << ";"
            << t.getDueDate().toString("yyyy-MM-dd") << ";"
            << t.getPriority() << ";"
            << (t.isCompleted() ? "1" : "0")
            << "\n";
    }

    return true;
}

int Planner::countCompleted() const {
    return countIf<Task>(tasks, [](const Task& t) {
        return t.isCompleted();
    });
}

double Planner::averagePriority() const {
    if (tasks.isEmpty())
        return 0;

    int sum = 0;

    for (const Task& t : tasks) {
        sum += t.getPriority();
    }

    return static_cast<double>(sum) / tasks.size();
}
