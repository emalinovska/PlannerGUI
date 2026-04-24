#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>
#include <QDateTime>

class Task
{
private:
    QString title;
    QDate dueDate;
    int priority;
    bool completed;

    // 🔥 TIMER
    qint64 timeSpent;        // секунды
    bool running;
    QDateTime startTime;

public:
    Task();
    Task(const QString &title, const QDate &dueDate, int priority, bool completed = false);

    // getters
    QString getTitle() const;
    QDate getDueDate() const;
    int getPriority() const;
    bool isCompleted() const;
    qint64 getCurrentTimeSpent() const;
    qint64 getTimeSpent() const;
    bool isTimerRunning() const;
    QDateTime getStartTime() const;

    // setters
    void setTitle(const QString &title);
    void setDueDate(const QDate &dueDate);
    void setPriority(int priority);
    void setCompleted(bool completed);

    // 🔥 timer control
    void startTimer();
    void stopTimer();
    void setTimeSpent(qint64 seconds);
};

#endif