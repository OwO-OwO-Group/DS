// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "Buffer.h"
#include <iostream>

using namespace std;

BufferRead::BufferRead(fstream &in, int limit, int bufferSize)
{
    fs = &in;
    size = bufferSize;
    buffer = new Column[size];
    readLimit = limit;

    // set index and load
    load();
}

void BufferRead::load()
{
    fs->read((char *)buffer, sizeof(Column) * size);
    readLimit -= size;
    index = 0;
}

Column *BufferRead::read()
{
    // buffer is empty (index >= 50)
    if (index >= size) {
        // readLimit is N
        if (readLimit > 0 && !fs->eof())
            load();
        else
            return NULL;
    }

    // return current index then plus
    return &buffer[index++];
}

void BufferRead::resetLimit(int limit) { readLimit = limit; }
BufferRead::~BufferRead() { delete buffer; }

BufferWrite::BufferWrite(fstream &out, int bufferSize)
{
    fs = &out;
    size = bufferSize;
    buffer = new Column[size];
    count = 0;
}

void BufferWrite::write(Column *data)
{
    if (data == NULL) {
        flush();
        return;
    }

    // write to buffer
    buffer[count] = *data;
    count++;

    if (count >= size)
        flush();
}

void BufferWrite::flush()
{
    fs->write((char *)buffer, sizeof(Column) * count);
    count = 0;
}

BufferWrite::~BufferWrite() { delete buffer; }

