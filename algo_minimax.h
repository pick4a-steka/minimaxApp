#pragma once

#include <mainwindow.h>
#include <vector>
#include <queue>
#include <memory>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QObject>
#include <QThread>
#include <QDebug>

#include "visualizer.h"
#include "TreeNode.h"

class Visualizer;

class Minimax : public QObject {
    Q_OBJECT

public:
    Minimax() {}
    Minimax(TreeNode *root, std::queue<int> &leaves, std::vector<unsigned int> &numChildren, unsigned int &index, bool isLeftToRight, \
            bool isMax, bool isAlphaBeta, bool isTreeGeneration, \
            int depth, int branching, int timer, QObject *parent = nullptr);
    virtual ~Minimax();

    void DFS_minimax(TreeNode *node, bool isMax, int alpha, int beta);

signals:
    void highlightPath(TreeNode *parent, TreeNode *child);
    void resetHighlight(TreeNode *parent, TreeNode *child);
    void highlightPrunedSubtree(TreeNode *node);
    void minimaxFinished(TreeNode *root);

public slots:
    // void resetTree(TreeNode *node);
    // запускаем рекурсивный алгоритм в отдельном потоке
    void runMinimax() {
        DFS_minimax(root, isMax, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        qDebug() << "DFS_minimax прекратил работу";
        emit minimaxFinished(root);
    }

private:
    // Переменные
    TreeNode *root;
    bool isMax;
    bool isAlphaBeta;
    bool isLeftToRight;

    int timer;

    // Методы
    void buildTree(TreeNode *node, std::queue<int> &leaves, std::vector<unsigned int> &numChildren, unsigned int &index);
    void buildTree(TreeNode *node, std::queue<int> &leaves, int depth, int &branching);
};
