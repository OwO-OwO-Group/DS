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

// count number of Node
int Tree23::isNodeN(Node *node) { return node->size + 1; }

Tree23::Node Tree23::*split(Tree23::Node *node)
{
    // 2 node
}

// get next node
Tree23::Node *Tree23::nextPtr(Tree23::Node *node, const string &key)
{
    // return if node is leaf or has some key
    if (isLeaf(node) || hasKey(node, key) != -1)
        return node;

    // check left of first key
    if (node->data[0].key > key)
        return node->subtree[0];

    // check betwenn of two key
    int keySize = node->size;
    for (int i = 0; i < keySize - 1; i++)
        if (node->data[i].key < key && node->data[i + 1].key > key)
            return node->subtree[i + 1];

    // check right of last key
    if (node->data[keySize - 1].key < key)
        return node->subtree[keySize];

    return node;
}

// some key return index
// not include return -1
int Tree23::hasKey(Node *node, const string &key)
{
    for (int i = 0; i < isNodeN(node) - 1; i++) {
        if (node->data[i].key == key)
            return i;
    }

    return -1;
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
        root->size = 1;
    }
    else {
        // find correct node and key

        // isSome key
    }
}

// get height
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

// result root data
void Tree23::getRoot(vector<int> &result)
{
    result.clear();
    for (int i = 0; i < root->size; i++) {
        vector<int> *id = &(root->data[i].id);
        result.insert(id->end(), id->begin(), id->end());
    }
}

Tree23::Tree23() { root = NULL; }

void Tree23::removeNode(Node *cur)
{
    if (cur == NULL)
        return;

    for (int i = 0; i < cur->size; i++)
        removeNode(cur->subtree[i]);

    delete cur;
}

void Tree23::clear() { removeNode(root); }
