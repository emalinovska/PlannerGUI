#include "Planner.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <cstring>

// ===== GET TASKS =====
const QVector<Task>& Planner::getTasks() const
{
    return tasks;
}

// ===== ADD =====
void Planner::addTask(const Task &task)
{
    tasks.append(task);
}

// ===== REMOVE =====
void Planner::removeTask(int index)
{
    if (index >= 0 && index < tasks.size())
        tasks.removeAt(index);
}

// ===== UPDATE =====
void Planner::updateTask(int index, const Task &task)
{
    if (index >= 0 && index < tasks.size())
        tasks[index] = task;
}

// ===== SET COMPLETED =====
void Planner::setCompleted(int index, bool done){
    if (index >= 0 && index < tasks.size())
        tasks[index].setCompleted(done);
}

void Planner::startTaskTimer(int index) {
    if (index >= 0 && index < tasks.size())
        tasks[index].startTimer();
}

void Planner::stopTaskTimer(int index) {
    if (index>= 0 && index < tasks.size())
        tasks[index].stopTimer();
}
// ================= SAVE =================
void Planner::saveToBinaryFile(const QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Cannot save file:" << path;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);

    // 🔥 HEADER
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
    qDebug() << "File size:" << QFile(path).size();
}

// ================= LOAD =================
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

    // 🔥 HEADER
    char header[4];
    in.readRawData(header, 4);

    if (strncmp(header, "TSK1", 4) != 0) {
        qDebug() << "Wrong file format!";
        file.close();
        return;
    }

    qint32 size;
    in >> size;

    qDebug() << "READ SIZE =" << size;

    for (int i = 0; i < size; ++i) {

        QString title;
        QDate date;
        int priority;
        bool completed;

        qint64 timeSpent;
        bool running;
        QDateTime start;

        in >> title >> date >> priority >> completed
            >> timeSpent >> running >> start;

        Task t(title, date, priority, completed);

        // 🔥 ВОССТАНОВЛЕНИЕ ТАЙМЕРА
        if (running) {
            qint64 extra = start.secsTo(QDateTime::currentDateTime());
            timeSpent+= extra;
        }

        // 🔥 СЕТТЕРЫ (добавь их в Task!)
        t.setTimeSpent(timeSpent);

        tasks.append(t);
    }

    file.close();

    qDebug() << "Loaded tasks:" << tasks.size();
    qDebug() << "Loading from:" << path;
}