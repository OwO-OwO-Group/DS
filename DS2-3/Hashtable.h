// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "Data.h"
#include <iostream>
using namespace std;

typedef struct Table {
    int hashcode;
    Column column;
} Table;

class Hashtable {
    int searchCount;
    int successfulCount, unsuccessfulCount;

    Table *hashtable;

public:
    virtual void insert();
    virtual int hash(char *str);
    bool save(string fileName);
    Hashtable(int size);
    void clear();
    void search(char *str);
};

#endif

