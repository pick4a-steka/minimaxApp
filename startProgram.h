#pragma once

#include "mainwindow.h"
#include "algo_minimax.h"
#include "visualizer.h"
#include "mainApplication.h"
#include "inputParametr.h"

#include <QApplication>
#include <QObject>

class StartProgram : public QObject {
    Q_OBJECT

public:
    StartProgram(int w, int h, QObject *parent = nullptr);
    virtual ~StartProgram();

private slots:
    void startProgram();
    void closeScene();

private:
    inputParametr_window *parametrWindow;
    QGraphicsScene *scene;
    QGraphicsView *view;
};
