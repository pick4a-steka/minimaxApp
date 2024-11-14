#include "visualizer.h"

Visualizer::Visualizer(TreeNode *root, QGraphicsScene *scene, qreal sceneWidth, bool isMax, int depth, QObject *parent)
        : QObject(parent), isMax(isMax), scene(scene) {
    drawMinAndMax(depth, isMax);
    drawTreeDFS(root, {0, sceneWidth}, 0);
}

Visualizer::~Visualizer() {
    // Получаем список элементов один раз и сохраняем его в переменной
    QList<QGraphicsItem*> items = scene->items();
    for (auto item : items) {
        scene->removeItem(item);
        delete item;
    }
}

QPointF Visualizer::setRootPosition(qreal sceneWidth, qreal sceneHight) {
    qreal x = sceneWidth / 2;
    qreal y = sceneHight / 7;

    return QPointF(x, y);
}

void Visualizer::drawTreeDFS(TreeNode *node, std::pair<unsigned int, unsigned int> AB, int depth, int levelSpacing) {
    if (!node) {
        return;
    }

    unsigned int numChildren = node->children.size();

    // Координата x для текущего узла как середина области AB
    qreal x = (AB.first + AB.second) / 2;
    qreal y = levelSpacing * depth;

    // Создаем и добавляем узел
    TreeNodeItem *nodeItem = new TreeNodeItem(x, y, 20, 20, node);
    scene->addItem(nodeItem);
    scene->addItem(nodeItem->text);

    // Если у узла нет потомков, выходим из функции, но узел уже добавлен
    if (numChildren == 0) {
        return;
    }

    // Коэффициент приращения для деления области под дочерние узлы
    int delt = qFloor((AB.second - AB.first) / (qreal)numChildren);

    // Отрисовка дочерних узлов
    for (unsigned int j = 0; j < numChildren; ++j) {
        auto &child = node->children[j];

        // Рассчитываем область для дочернего узла и его позицию
        unsigned int childStart = AB.first + j * delt;
        unsigned int childEnd = childStart + delt;
        qreal childX = (childStart + childEnd) / 2;
        QPointF childPos(childX + 10, levelSpacing * (depth + 1));

        // Рекурсивный вызов для дочернего узла с обновленной областью
        drawTreeDFS(child.get(), {childStart, childEnd}, depth + 1, levelSpacing);

        // Отрисовка линии между текущим узлом и дочерним узлом
        EdgeItem *line = new EdgeItem(QPointF(x + 10, y + 20), childPos, node, child.get());
        scene->addItem(line);
    }
}

void Visualizer::drawMinAndMax(int depth, bool isMax, int levelSpacing) {
    for (int i = 0; i < depth; ++i) {
        QGraphicsTextItem *text = new QGraphicsTextItem(isMax ? QString("MAX") : QString("MIN"));
        text->setPos(QPointF(1, 1 + (levelSpacing * i)));
        scene->addItem(text);
        isMax = !isMax;
    }
}

void Visualizer::highligthPrunedSubtree(TreeNode *node) {
    if (!node) {
        return;
    }

    auto nodeItem = findNodeItem(node);
    if (nodeItem) {
        nodeItem->setClippingBrush();
    }

    for (const auto &child : node->children) {
        auto edgeItem = findEdgeItem(node, child.get());
        if (edgeItem) {
            edgeItem->setClippingPen();
        }
        highligthPrunedSubtree(child.get());
    }
}

void Visualizer::highlightPath(TreeNode *parent, TreeNode *child) {
    // Находим узел и ребро для выделения
    TreeNodeItem *childNodeItem = findNodeItem(child);
    EdgeItem *edgeItem = findEdgeItem(parent, child);

    if (childNodeItem) {
        // Меняем цвет узла для выделения
        childNodeItem->setNewBrush(QBrush(QColor(48,186,143))); // горный луг
    }

    if (edgeItem) {
        // Меняем толщину ребра для выделения
        edgeItem->setNewPen(4);
    }
}

void Visualizer::resetHighlight(TreeNode *parent, TreeNode *child) {
    // Находим узел и ребро для сброса цвета
    TreeNodeItem *childNodeItem = findNodeItem(child);
    TreeNodeItem *parentNodeItem = findNodeItem(parent);
    EdgeItem *edgeItem = findEdgeItem(parent, child);

    if (childNodeItem) {
        // Возвращаем исходный цвет
        childNodeItem->setDefaultBrush();
        parentNodeItem->setNewVal();
    }

    if (edgeItem) {
        // Возвращаем ребру исходный стиль
        edgeItem->setDefaultPen();
    }
}

Visualizer::TreeNodeItem* Visualizer::findNodeItem(TreeNode *node) {
    // Проходимся по сцене и ищем TreeNodeItem, который связан с узлом
    for (auto &item : scene->items()) {
        auto nodeItem = dynamic_cast<TreeNodeItem*>(item);
        if (nodeItem && nodeItem->node == node) {
            return nodeItem;
        }
    }
    return nullptr;
}

Visualizer::EdgeItem* Visualizer::findEdgeItem(TreeNode *parent, TreeNode *child) {
    for (auto &item : scene->items()) {
        auto edge = dynamic_cast<EdgeItem*>(item);
        if (edge && edge->getNodeParent() == parent && edge->getNodeChild() == child) {
            return edge;
        }
    }
    return nullptr;
}
