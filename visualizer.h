#pragma once

#include <QObject>
#include <qmath.h>

#include "algo_minimax.h"
#include "TreeNode.h"

// предварительное объявление
// class TreeNode;

class Visualizer : public QObject {
    Q_OBJECT

public:
    Visualizer(QObject *parent = nullptr) : QObject(parent) {}
    Visualizer(TreeNode *root, QGraphicsScene *scene, qreal sceneWidth, bool isMax, int depth, QObject *parent = nullptr);
    virtual ~Visualizer();

public slots:
    void highlightPath(TreeNode *parent, TreeNode *child);
    void resetHighlight(TreeNode *parent, TreeNode *child);
    void highligthPrunedSubtree(TreeNode *node);

private:
    bool isMax;
    // класс для узла
    class TreeNodeItem : public QGraphicsEllipseItem {
    public:
        TreeNodeItem(qreal x, qreal y, qreal width, qreal height, TreeNode *node)
            : QGraphicsEllipseItem(x, y, width, height), node(node) {
            setBrush(Qt::blue);

            // Текст внутри узла (значение узла)
            text = new QGraphicsTextItem(QString::number(node->val));
            text->setPos(x + 2, y);
        }

        void setNewBrush(QBrush brush) {
            setBrush(brush);
        }

        void setNewVal() {
            int val = node->val;
            if (val == std::numeric_limits<int>::max() || val == std::numeric_limits<int>::min()) {
                return;
            }
            text->setPlainText(QString::number(node->val));
            qDebug() << "Изменяем узел на " + QString::number(node->val);
        }

        void setDefaultBrush() {
            setBrush(Qt::blue);
        }

        void setClippingBrush(QBrush brush = QBrush(Qt::red)) {
            setBrush(brush);
        }

        TreeNode *node;
        QGraphicsTextItem *text;
    };


    // класс для ребра
    class EdgeItem : public QGraphicsLineItem {
    public:
        EdgeItem(QPointF start, QPointF end, TreeNode *parent, TreeNode *child)
            : QGraphicsLineItem(QLineF(start, end)), parent(parent), child(child) {
            setPen(QPen(Qt::black, 2));
        }

        void setNewPen(int thikness) {
            setPen(QPen(Qt::black, thikness));
        }

        void setDefaultPen() {
            setPen(QPen(Qt::black, 2));
        }

        void setClippingPen(QBrush brush = QBrush(Qt::red)) {
            setPen(QPen(brush, 2));
        }

        TreeNode* getNodeParent() {
            return parent;
        }

        TreeNode* getNodeChild() {
            return child;
        }
    private:
        TreeNode *parent;
        TreeNode *child;
    };

    TreeNodeItem* findNodeItem(TreeNode *node);
    EdgeItem* findEdgeItem(TreeNode *parent, TreeNode *child);

    void drawTreeDFS(TreeNode *node, std::pair<unsigned int, unsigned int> AB, int depth, int levelSpacing = 70);
    void drawMinAndMax(int depth, bool isMax, int levelSpacing = 70);
    QPointF setRootPosition(double sceneWidth, double sceneHight);
    QGraphicsScene *scene;
};
