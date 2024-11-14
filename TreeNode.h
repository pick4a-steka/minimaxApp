#pragma once

#include <vector>
#include <memory>
#include <QObject>

class TreeNode {

public:
    TreeNode() : val(0) {}
    TreeNode(int x) : val(x) {}
    virtual ~TreeNode();

    void addChild(std::unique_ptr<TreeNode> node);

    int val;
    std::vector<std::unique_ptr<TreeNode>> children;
};
