#pragma once

#include <QObject>
#include <QCheckBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QComboBox>

class inputParametr_window : public QWidget {
    Q_OBJECT

public:
    inputParametr_window(int w, int h, QWidget *parent = nullptr);
    virtual ~inputParametr_window();

    bool getIsLeftToRight() {
        return isLeftToRight;
    }

    bool getIsAlphaBeta() {
        return isAlphaBeta;
    }

    bool getIsTreeGeneration() {
        return isTreeGeneration;
    }

    bool getIsMax() {
        return isMax;
    }

    int getDepth() {
        return depth;
    }

    int getBranching() {
        return branching;
    }

    int getTimer() {
        return timer;
    }

signals:
    void getParameters();

private slots:
    void closeParametrWindow();

private:
    bool isLeftToRight;
    bool isAlphaBeta;
    bool isMax;
    bool isTreeGeneration;

    int depth;
    int branching;
    int timer;
};
