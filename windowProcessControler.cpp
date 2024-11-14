#include "windowProcessControler.h"

windowProcessController::windowProcessController(int width, int height, QWidget *parent) : QWidget(parent), w(width), h(height) {
    resize(w, h);
    setWindowTitle("Minimax. Контроль процесса исполнения");

    btn_restart = new QPushButton(this);
    btn_quit = new QPushButton(this);

    btn_restart->setText("Повторить");
    btn_quit->setText("Завершить");

    QVBoxLayout *processController_Layout = new QVBoxLayout(this);
    processController_Layout->addWidget(btn_restart);
    processController_Layout->addWidget(btn_quit);
    //show();
}

windowProcessController::~windowProcessController() {

}
