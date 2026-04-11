#include "UserManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QDir>
#include <QDebug>

UserManager::UserManager()
{
    usersFile = "data/users.json";

    QDir().mkpath("data");

    QFile file(usersFile);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QJsonObject root;
            root["users"] = QJsonArray();
            file.write(QJsonDocument(root).toJson());
            file.close();
        }
    }

    qDebug() << "Using JSON file:" << QFileInfo(usersFile).absoluteFilePath();
}

QString UserManager::hashPassword(const QString &password) const
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QJsonArray UserManager::loadUsers() const
{
    QFile file(usersFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QJsonArray();

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject())
        return QJsonArray();

    return doc.object().value("users").toArray();
}

bool UserManager::saveUsers(const QJsonArray &users) const
{
    QFile file(usersFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QJsonObject root;
    root["users"] = users;

    file.write(QJsonDocument(root).toJson());
    file.close();
    return true;
}

bool UserManager::userExists(const QString &username) const
{
    QJsonArray users = loadUsers();

    for (int i = 0; i < users.size(); ++i) {
        QJsonObject obj = users[i].toObject();
        if (obj["username"].toString() == username)
            return true;
    }
    return false;
}

bool UserManager::registerUser(const QString &username, const QString &password)
{
    if (userExists(username))
        return false;

    QJsonArray users = loadUsers();

    QJsonObject newUser;
    newUser["username"] = username;
    newUser["password"] = hashPassword(password);

    users.append(newUser);

    return saveUsers(users);
}

bool UserManager::login(const QString &username, const QString &password)
{
    QString hashed = hashPassword(password);
    QJsonArray users = loadUsers();

    for (int i = 0; i < users.size(); ++i) {
        QJsonObject obj = users[i].toObject();

        if (obj["username"].toString() == username &&
            obj["password"].toString() == hashed)
        {
            return true;
        }
    }

    return false;
}
