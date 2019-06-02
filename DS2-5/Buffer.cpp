// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "Buffer.h"
#include <iostream>

using namespace std;

BufferRead::BufferRead(fstream *in, int limit, int bufferSize)
{
    size = bufferSize;
    buffer = new Column[size];

    fs = in;
    readLimit = limit;

    // set index and load
    load();
}

void BufferRead::setIn(fstream &in)
{
    fs = &in;
    readSize = index = 0;
}

void BufferRead::load()
{
    fs->read((char *)buffer, sizeof(Column) * size);
    readSize = fs->gcount() / sizeof(Column);
    readLimit -= size;
    index = 0;
}

BufferRead::operator bool()
{
    if (index >= readSize && fs->peek() == EOF)
        return false;

    return true;
}

Column *BufferRead::read()
{
    // buffer is empty (index >= 50)
    if (index >= readSize) {
        // readLimit is N
        if (readLimit > 0 && fs->peek() != EOF)
            load();
        else
            return NULL;
    }

    // return current index then plus
    return &buffer[index++];
}

void BufferRead::resetLimit(int limit) { readLimit = limit; }
BufferRead::~BufferRead() { delete buffer; }

BufferWrite::BufferWrite(fstream *out, int bufferSize)
{
    fs = out;
    size = bufferSize;
    buffer = new Column[size];
    count = 0;
}

void BufferWrite::setOut(fstream &out)
{
    fs = &out;
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

