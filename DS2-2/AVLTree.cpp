// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "AVLTree.h"

AVLTree::Node *AVLTree::LR_roate(AVLTree::Node *cur)
{
    cur->left = RR_roate(cur->right);
    return LL_roate(cur);
}

AVLTree::Node *AVLTree::RL_roate(AVLTree::Node *cur)
{
    cur->right = LL_roate(cur->right);
    return RR_roate(cur);
}

AVLTree::Node *AVLTree::LL_roate(AVLTree::Node *cur)
{
    Node *left = cur->left;
    cur->left = left->right;
    left->right = cur;
    return left;
}

AVLTree::Node *AVLTree::RR_roate(AVLTree::Node *cur)
{
    Node *right = cur->right;
    cur->right = right->left;
    right->left = cur;
    return right;
}

void AVLTree::insert(Data)
{
    if (root == NULL) {
    }
    else {
    }
}
