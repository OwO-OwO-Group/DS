// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _TREE23_H_
#define _TREE23_H_
#include "Data.h"
#include <string>
#include <vector>

#define TREE23_SIZE 2

using namespace std;

class Tree23 {
public:
    typedef struct Node {
        struct {
            string key;
            vector<int> id;
        } data[TREE23_SIZE];

        Node *pre;
        Node *subtree[TREE23_SIZE + 1];
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

