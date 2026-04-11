#include <QApplication>
#include "ui/LoginWindow.h"
#include <QSettings>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("PlannerGUI", "PlannerGUI");
    QString theme = settings.value("theme", ":/themes/light.qss").toString();

    QFile file(theme);
    if (file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
    }

    LoginWindow w;
    w.show();

    return a.exec();
}

