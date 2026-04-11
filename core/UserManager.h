#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

class UserManager
{
public:
    UserManager();

    bool login(const QString &username, const QString &password);
    bool userExists(const QString &username) const;
    bool registerUser(const QString &username, const QString &password);

private:
    QString usersFile;

    QJsonArray loadUsers() const;
    bool saveUsers(const QJsonArray &users) const;

    QString hashPassword(const QString &password) const;
};

#endif // USERMANAGER_H
