#pragma once

#include <random>
#include <algorithm>
#include <iterator>

#include "windowProcessControler.h"
#include "visualizer.h"

class windowProcessController;

class mainApplication : public QObject {
    Q_OBJECT

public:
    explicit mainApplication(TreeNode *root, QGraphicsScene *scene, bool isLtoR, \
                             bool max_or_min, bool isA_B, bool isTreeGen, int depth, int branching, int timer, QObject *parent = nullptr);

    virtual ~mainApplication();

    void startMinimax();

    QThread* getThread() const {
        return thread;
    }

    windowProcessController* getPocessController() const {
        return window_process_controller;
    }

signals:
    void endSignal();

private slots:
    void startProcessController();

    void onQuitButtonClicked();

    void onRestartButtonClicked();

private:
    TreeNode *root;
    QGraphicsScene *scene;
    Visualizer *visualizer = nullptr;
    QThread *thread = nullptr;
    Minimax *minimax = nullptr;
    windowProcessController *window_process_controller = nullptr;
    std::queue<int> leaves;
    std::vector<unsigned int> numChildren;
    std::vector<int> v_leaves;

    bool isLeftToRight;
    bool isMax;
    bool isAlphaBeta;
    bool isTreeGeneration;

    int depth;
    int branching;
    int timer;

    void restartMinimax();
    void deleteController();
    void generationLeaves(int depth, int branching);
};
