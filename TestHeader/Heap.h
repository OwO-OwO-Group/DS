#pragma once
#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class HEAP {
    vector<T> data;
public:
    HEAP () {}
    void print();
    void insert(T temp);
};

#endif

