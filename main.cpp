/*
 * File:   main.cpp
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 16:53
 */

#include <QApplication>

#include "MainForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainForm mf;
    mf.show();

    return app.exec();
}
