// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "Tree23.h"

bool Tree23::isLeaf(Node *node)
{
    if (isNodeN(node) == 0)
        return true;
    else
        return false;
}

int Tree23::isNodeN(Node *node)
{
    int result = 0;
    for (int i = 0; i < TREE23_SIZE; i++) {
        if (node->subtree[i] != NULL)
            result++;
    }

    return result;
}

Tree23::Node Tree23::*split(Tree23::Node *node)
{
    // 2 node
}

void Tree23::insert(int id, const string &key)
{
    // is null tree
    if (root == NULL) {
        root = new Node();

        // set NULL
        root->pre = NULL;
        for (int i = 0; i < TREE23_SIZE; i++)
            root->subtree[i] = NULL;

        // set first key
        root->data[0].key = key;
        root->data[0].id.push_back(id);
    }
    else {
        Node *cur = root;
        // find correct node and key
        while (!isLeaf(cur) || cur) {
        }

        // isSome key
        // if () {
        //
        // } else {
        // }
    }
}

int Tree23::height()
{
    int count = 0;
    Node *cur = root;
    while (cur != NULL) {
        cur = cur->subtree[0];
        count++;
    }

    return count;
}

void Tree23::getRoot(vector<int> &result)
{
    result.clear();
    for (int i = 0; i < TREE23_SIZE; i++) {
        vector<int> *id = &(root->data[i].id);
        result.insert(id->end(), id->begin(), id->end());
    }
}

Tree23::Tree23() { root = NULL; }

void Tree23::removeNode(Node *cur)
{
    if (cur == NULL)
        return;

    for (int i = 0; i < TREE23_SIZE + 1; i++)
        removeNode(cur->subtree[i]);

    delete cur;
}

void Tree23::clear() { removeNode(root); }
