// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _TREE23_H_
#define _TREE23_H_
#include "Data.h"
#include <string>
#include <vector>

#define TREE23_SIZE 3
#define TREE23_KEY_SIZE TREE23_SIZE - 1

using namespace std;

class Tree23 {
public:

        int size;
        Node *pre;
        Node *subtree[TREE23_SIZE];
    } Node;

private:
    Node *root;

    Node *split(Node *);
    int isNodeN(Node *);
    void removeNode(Node *cur);

    bool isLeaf(Node *);

public:
    void insert(int id, const string &key);
    int height();
    void getRoot(vector<int> &result);
    Tree23();
    void clear();
};

#endif

