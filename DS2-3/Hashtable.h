// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "Data.h"
#include "Prime.h"
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

class Table {
public:
    int hashcode;
    Column column;

    friend ostream &operator<<(ostream &out, Table &table);
};

class Hashtable {
protected:
    int rows;
    int size; // prime
    int twoStep; // prime
    double successful;
    double unsuccessful;
    Table *hashtable;

    int hash(char *str);
    void setTwoStep();
    void setSize();
public:
    Hashtable(int size);
    void clear();

    void insert(Data data);
    virtual void save(fstream &fout); // overload
};

class Hashtable_Linear : public Hashtable {
public:
    Hashtable_Linear(int size) :Hashtable(size) { setTwoStep(); };
    virtual void save(fstream &fout); // overload
};

class Hashtable_Double : public Hashtable {
    void setTwoStep();
public:
    Hashtable_Double(int size) :Hashtable(size) { setTwoStep(); };
    virtual void save(fstream &fout); // overload
};

#endif

