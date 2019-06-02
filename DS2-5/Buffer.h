// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#pragma once
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Data.h"
#include <fstream>
#include <iostream>
using namespace std;

class BufferRead {
    fstream *fs;
    int index;
    int readLimit;
    int size, readSize;

    void load();

public:
    operator bool();
    Column *buffer;
    BufferRead(fstream *in, int limit, int bufferSize);
    void resetLimit(int);
    void setIn(fstream &in);
    Column *read();
    ~BufferRead();
};

class BufferWrite {
    fstream *fs;
    int count;
    Column *buffer;
    int size;

public:
    BufferWrite(fstream *out, int bufferSize);
    void setOut(fstream &out) void write(Column *data);
    void flush();
    ~BufferWrite();
};

#endif