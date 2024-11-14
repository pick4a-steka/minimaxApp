#include "algo_minimax.h"

Minimax::Minimax(TreeNode *root, std::queue<int> &leaves, std::vector<unsigned int> &numChildren, unsigned int &index, bool isLeftToRight, \
                 bool isMax, bool isAlphaBeta, \
                 bool isTreeGeneration, int depth, int branching, int timer, QObject *parent)
        : QObject(parent), root(root), isMax(isMax), isAlphaBeta(isAlphaBeta), isLeftToRight(isLeftToRight), timer(timer) {
    if (isTreeGeneration) {
        buildTree(root, leaves, depth, branching);
    }
    else {
        buildTree(root, leaves, numChildren, index);
    }
}

Minimax::~Minimax() {

}

void Minimax::buildTree(TreeNode *node, std::queue<int> &leaves, std::vector<unsigned int> &childrenCount, unsigned int &index) {
    if (index >= childrenCount.size()) {
        return;
    }

    unsigned int numChildren = childrenCount[index];
    index++;

    for (unsigned int i = 0; i < numChildren; ++i) {
        std::unique_ptr<TreeNode> new_node = std::make_unique<TreeNode>();
        buildTree(new_node.get(), leaves, childrenCount, index);
        node->addChild(std::move(new_node));
    }

    if (node->children.size() == 0 && !leaves.empty()) {
        qDebug() << "Записали значение листа";
        node->val = leaves.front();
        leaves.pop();
        //return;
    }
}

void Minimax::buildTree(TreeNode *node, std::queue<int> &leaves, int depth, int &branching) {
    if (!depth) {
        if (!leaves.empty()) {
            qDebug() << "Записали значение листа";
            node->val = leaves.front();
            leaves.pop();
        }
        return;
    }

    for (int i = 0; i < branching; ++i) {
        std::unique_ptr<TreeNode> new_node = std::make_unique<TreeNode>();
        buildTree(new_node.get(), leaves, depth - 1, branching);
        node->addChild(std::move(new_node));
    }
}

void Minimax::DFS_minimax(TreeNode *node, bool isMax, int alpha = std::numeric_limits<int>::min(), int beta = std::numeric_limits<int>::max()) {
    if (node->children.empty()) {
        return;
    }

    if (isLeftToRight) {
        if (isMax) {
            node->val = std::numeric_limits<int>::min();
            for (unsigned int i = 0; i < node->children.size(); ++i) {
                emit highlightPath(node, node->children[i].get());

                QThread::msleep(timer);
                DFS_minimax(node->children[i].get(), false, alpha, beta);
                node->val = std::max(node->val, node->children[i]->val);
                alpha = std::max(alpha, node->val); // Обновление alpha для текущего узла

                emit resetHighlight(node, node->children[i].get());

                if (isAlphaBeta && alpha >= beta) {
                    unsigned int j = i + 1;
                    while (j < node->children.size()) {
                        emit highlightPrunedSubtree(node->children[j].get());
                        j++;
                    }
                    break;
                }
            }
        } else {
            node->val = std::numeric_limits<int>::max();
            for (unsigned int i = 0; i < node->children.size(); ++i) {
                emit highlightPath(node, node->children[i].get());

                QThread::msleep(timer);
                DFS_minimax(node->children[i].get(), true, alpha, beta);
                node->val = std::min(node->val, node->children[i]->val);
                beta = std::min(beta, node->val); // Обновление beta для текущего узла

                emit resetHighlight(node, node->children[i].get());

                if (isAlphaBeta && beta <= alpha) {
                    unsigned int j = i + 1;
                    while (j < node->children.size()) {
                        emit highlightPrunedSubtree(node->children[j].get());
                        j++;
                    }
                    break;
                }
            }
        }
    }
    else {
        if (isMax) {
            node->val = std::numeric_limits<int>::min();
            for (int i = node->children.size() - 1; i >= 0; --i) {
                emit highlightPath(node, node->children[i].get());

                QThread::msleep(timer);
                DFS_minimax(node->children[i].get(), false, alpha, beta);
                node->val = std::max(node->val, node->children[i]->val);
                alpha = std::max(alpha, node->val); // Обновление alpha для текущего узла

                emit resetHighlight(node, node->children[i].get());

                if (isAlphaBeta && alpha >= beta) {
                    for (int j = i - 1; j >= 0; --j) {
                        emit highlightPrunedSubtree(node->children[j].get());
                    }
                    break;
                }
            }
        } else {
            node->val = std::numeric_limits<int>::max();
            for (int i = node->children.size() - 1; i >= 0; --i) {
                emit highlightPath(node, node->children[i].get());

                QThread::msleep(timer);
                DFS_minimax(node->children[i].get(), true, alpha, beta);
                node->val = std::min(node->val, node->children[i]->val);
                beta = std::min(beta, node->val); // Обновление beta для текущего узла

                emit resetHighlight(node, node->children[i].get());

                if (isAlphaBeta && beta <= alpha) {
                    for (int j = i - 1; j >= 0; --j) {
                        emit highlightPrunedSubtree(node->children[j].get());
                    }
                    break;
                }
            }
        }
    }
}

