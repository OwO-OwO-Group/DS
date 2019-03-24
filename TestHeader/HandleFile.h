#pragma once
#ifndef _HANDLEFILE_H_
#define _HANDLEFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"
#include "Heap.h"
#include "Heap.cpp"
#include "Data.h"
using namespace std;

class HandleFile {
    fstream fin;
    fstream fout;

    HEAP<Data> heap;

    // common function
    int numberInput(string message, string errorMsg);

    void save(string saveName, vector<Data> &database);

    void dropHeader(fstream &file);

    string fileInput(fstream &file, string message, string prefix);

public:
    bool task1();
};

#endif