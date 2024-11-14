#include <TreeNode.h>

TreeNode::~TreeNode() {

}

void TreeNode::addChild(std::unique_ptr<TreeNode> node) {
    children.push_back(std::move(node)); // передаем владение уникальным указателем в вектор
}
