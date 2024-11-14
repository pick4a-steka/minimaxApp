#include "mainwindow.h"
#include "algo_minimax.h"
#include "visualizer.h"
#include "mainApplication.h"
#include "startProgram.h"

#include <QApplication>
#include <QObject>

#define N 200
#define M 300

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    StartProgram program(N, M);

    //w.show();

    return a.exec();
}
