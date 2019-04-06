// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "Tree23.h"
#include <algorithm>

bool Tree23::Node::isLeaf()
{
    if (subtree[0] == NULL)
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
int Tree23::Node::isNodeN() { return size + 1; }

void Tree23::Node::remove(int index)
{
    for (int i = index; i < size - 1; i++)
        data[i] = data[i + 1];
}

// merge to left or right by order
void Tree23::Node::merge(Node *node)
{
    if (data[size - 1].key < node->data[0].key) { // rightmost
        data[size] = node->data[0];               // add a key
        subtree[size] = node->subtree[0];
        subtree[size + 1] = node->subtree[1];
        size++;
    }
    else if (data[0].key > node->data[0].key) { // leftmost
        for (int i = size; i >= 1; i--) {       // shift
            data[i] = data[i - 1];
            subtree[i] = subtree[i - 1];
        }

        // merge
        data[0] = node->data[0]; // add a key
        subtree[0] = node->subtree[0];
        subtree[1] = node->subtree[1];

        size++;
    }
}

Tree23::Node *Tree23::split(Tree23::Node *node)
{
    // node is exist and full
    if (node->size > TREE23_KEY_SIZE) {
        if (node == NULL) { // is root
            // create new root
            Node *newRoot = new Node(NULL);
            connect(newRoot, root, 0); // set pre
            root = newRoot;            // replace root
        }
        else {
            Node *left = new Node(node), *right = new Node(node),
                 *pre = node->pre;

            // key1
            left->addKey(node->data[0]);
            left->subtree[0] = node->subtree[0];
            left->subtree[1] = node->subtree[1];

            // key3
            left->addKey(node->data[2]);
            right->subtree[0] = node->subtree[2];
            right->subtree[1] = node->subtree[3];

            // merge node and pre_node
            node->data[0] = node->data[1];
            node->subtree[0] = left;
            node->subtree[1] = right;
            node->size = 1;
            pre->merge(node);

            // remove node
            delete node;

            // recursive
            split(pre);
        }
    }
    else
        return node;
}

// get next node
Tree23::Node *Tree23::nextPtr(Tree23::Node *node, const string &key,
                              int &subtreeIndex)
{
    // return if node is leaf or has some key
    if (node->isLeaf() || node->hasKey(key) != -1)
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
int Tree23::Node::hasKey(const string &key)
{
    for (int i = 0; i < isNodeN() - 1; i++) {
        if (data[i].key == key)
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
void Tree23::Node::sortLeaf()
{
    int keySize = size;
    sort(data, data + keySize, cmp);
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
        int index = cur->hasKey(key);
        if (index == -1)
            cur->data[index].id.push_back(id);
        else // insert to node
        {
            insertToNode(cur, id, key);

            // sort cur
            cur->sortLeaf();

            // split
            split(cur);
        }
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
