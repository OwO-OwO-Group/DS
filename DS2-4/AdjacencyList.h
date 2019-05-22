// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _ADJACENCY_LISTS_H_
#define _ADJACENCY_LISTS_H_

#include "Data.h"
#include <fstream>
#include <map>
#include <vector>

using namespace std;

#define EXIT -1
#define BINARY 0

typedef char ID[10];

typedef struct link {
    ID id;
    float weight;
} Link;

typedef struct node {
    ID id;
    vector<Link> linked;
} Node;

class AdjacencyList {
    vector<node> nodes;
    map<string, int> indexMapping;

    fstream fin;
    fstream fout;
    string fileName;

    void isExistID(ID);

    // common function
    int numberInput(string message, string errorMsg);

    int fileInput(string message, string prefix);

    // Add node if not exist
    vector<node>::iterator addNode(ID id);

    // build map
    void buildMapping();

    // connect A to B, weight
    void connect(ID A, ID B, float weight);

    // test function
    void debug_buildMapping();

public:
    void clear();
    void load();
    void BFS(ID, vector<ID>);
    bool task1();
    bool task2();
};

#endif

