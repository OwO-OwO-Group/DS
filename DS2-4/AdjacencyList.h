// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _ADJACENCY_LISTS_H_
#define _ADJACENCY_LISTS_H_

#include <map>
#include <vector>

using namespace std;

typedef char Id[10];

typedef struct link {
    ID id;
    float weight;
} Link;

typedef struct node {
    ID id;
    vector<Link>;
} Link;

class AdjacencyList {
    vector<node> nodes;

    void isExistID(ID);

public:
    // connect A to B, weight
    void connect(ID A, ID B, float weight);
    void addNode(ID node);
    void clear();
};

#endif

