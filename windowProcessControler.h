#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class windowProcessController : public QWidget  {
    Q_OBJECT

public:
    windowProcessController() {}
    windowProcessController(int width, int height, QWidget *parent = nullptr);
    virtual ~windowProcessController();

    QPushButton* get_btnRestart() {
        return btn_restart;
    }

    QPushButton* get_btnQuit() {
        return btn_quit;
    }

signals:
    void signalRestartMinimax();
    void signalQuitMinimax();

private:
    int w;
    int h;
    QPushButton *btn_restart;
    QPushButton *btn_quit;
};
