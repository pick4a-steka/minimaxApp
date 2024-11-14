#include "startProgram.h"

#define N 1200
#define M 600
#define pw parametrWindow

StartProgram::StartProgram(int w, int h, QObject *parent) : QObject(parent) {
    parametrWindow = new inputParametr_window(w, h);
    parametrWindow->show();

    connect(parametrWindow, &inputParametr_window::getParameters, this, &StartProgram::startProgram);
}

StartProgram::~StartProgram() {
    delete parametrWindow;
}

void StartProgram::startProgram() {
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, N, M);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing); // сглаживание
    view->setWindowTitle("Minimax with alptha-beta-prunning");
    view->show();

    TreeNode *root = new TreeNode();
    mainApplication *app = new mainApplication(root, scene, pw->getIsLeftToRight(), pw->getIsMax(), pw->getIsAlphaBeta(), pw->getIsTreeGeneration(), \
                                               pw->getDepth(), pw->getBranching(), pw->getTimer());

    connect(app, &mainApplication::endSignal, app, &mainApplication::deleteLater);
    connect(app, &mainApplication::endSignal, this, &StartProgram::closeScene);

    app->startMinimax();
}

void StartProgram::closeScene() {
    qDebug() << "closeScene";
    scene->clear();
    view->close();
    view->deleteLater();
}
