#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{
private:
    QString title;
    QDate dueDate;
    int priority;
    bool completed;

public:
    // 🔹 Конструкторы (перегрузка)
    Task();
    Task(const QString &title);
    Task(const QString &title, const QDate &dueDate);
    Task(const QString &title, const QDate &dueDate, int priority, bool completed = false);

    // 🔹 Геттеры
    QString getTitle() const;
    QDate getDueDate() const;
    int getPriority() const;
    bool isCompleted() const;

    // 🔹 Сеттеры
    void setTitle(const QString &title);
    void setDueDate(const QDate &dueDate);
    void setPriority(int priority);
    void setCompleted(bool completed);
};

#endif // TASK_H
