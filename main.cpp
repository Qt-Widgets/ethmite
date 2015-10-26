/*
 * File:   main.cpp
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 16:53
 */

#include <QApplication>
#include <QMessageBox>
#include "MainForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
     Q_INIT_RESOURCE(qml);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
            QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    
    QApplication::setQuitOnLastWindowClosed(false);
    MainForm mf;
    mf.show();

    return app.exec();
}
