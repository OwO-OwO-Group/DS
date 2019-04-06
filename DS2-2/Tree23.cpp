// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "Tree23.h"
#include <algorithm>

bool Tree23::isLeaf(Node *node)
{
    if (node->subtree[0] == NULL)
        return true;
    else
        return false;
}

// connect two node
void Tree23::connect(Node *pre, Node *sub, int subIndex)
{
    pre->subtree[subIndex] = sub;
    sub->pre = pre;
}

Tree23::Node::Node(Tree23::Node *getPre)
{
    // set NULL
    pre = getPre;
    for (int i = 0; i < TREE23_SIZE; i++)
        subtree[i] = NULL;
    size = 0;
}

void Tree23::Node::addKey(const Data &getData)
{
    data[size] = getData;
    size++;
}

void Tree23::Node::addKey(int id, const string &key)
{
    data[size].key = key;
    data[size].id.push_back(id);
    size++;
}

// count number of Node
int Tree23::isNodeN(Node *node) { return node->size + 1; }

Tree23::Node Tree23::*split(Tree23::Node *node)
{
    // 2 node
}

// get next node
Tree23::Node *Tree23::nextPtr(Tree23::Node *node, const string &key,
                              int &subtreeIndex)
{
    // return if node is leaf or has some key
    if (isLeaf(node) || hasKey(node, key) != -1)
        return node;

    // check left of first key
    if (node->data[0].key > key) {
        return node->subtree[0];
    }

    // check betwenn of two key
    int keySize = node->size;
    for (int i = 0; i < keySize - 1; i++)
        if (node->data[i].key < key && node->data[i + 1].key > key) {
            subtreeIndex = i + 1;
            return node->subtree[i + 1];
        }

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

// insert id to the node
void Tree23::insertToNode(Tree23::Node *node, int id, const string &key)
{
    int keySize = node->size;
    node->data[keySize].key = key;
    node->data[keySize].id.push_back(id);
    node->size++;
}

bool cmp(const Tree23::Data &A, const Tree23::Data &B) { return A.key > B.key; }

// sort and modify leaf
void Tree23::sortLeaf(Tree23::Node *node)
{
    int keySize = node->size;
    sort(node->data, node->data + keySize, cmp);
}

void Tree23::insert(int id, const string &key)
{
    // is null tree
    if (root == NULL) {
        root = new Node(NULL);

        // set first key
        root->addKey(id, key);
    }
    else {
        Node *cur = root, *next = cur;
        int subtreeIndex;
        bool isFull;

        // find correct node and key
        while (cur != (next = nextPtr(cur, key, subtreeIndex)))
            cur = next;

        // isSome key
        int index = hasKey(cur, key);
        if (index == -1)
            cur->data[index].id.push_back(id);
        else // insert to node
            insertToNode(cur, id, key);

        // sort cur
        sortLeaf(cur);

        // split
        cur->pre->subtree[subtreeIndex] = split(cur);
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
