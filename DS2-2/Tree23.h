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
    typedef struct {
        string key;
        vector<int> id;
    } Data;

    class Node {
    public:
        // key size + one buffer
        Data data[TREE23_KEY_SIZE + 1];
        int size;
        Node *pre;
        Node *subtree[TREE23_SIZE];

        void addKey(const Data &);
        void addKey(int id, const string &key);
        Node(Node *);
    };

private:
    Node *root;

    Node *split(Node *);
    Node *newNode(Node *);
    int isNodeN(Node *);
    void removeNode(Node *cur);

    Node *nextPtr(Node *, const string &key, int &);
    void insertToNode(Node *, int id, const string &key);
    void sortLeaf(Tree23::Node *);
    bool isLeaf(Node *);

public:
    void insert(int id, const string &key);
    int height();
    void getRoot(vector<int> &result);
    Tree23();
    void clear();
};

#endif

