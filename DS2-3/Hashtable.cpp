// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "Hashtable.h"
#include <iostream>
using namespace std;

bool Hashtable::save(string fileName) { return false; }

Hashtable::Hashtable(int rowSize)
{
    size = rowSize;
    hashtable = new Table[size];
}

int Hashtable::hash(char *str)
{
    int hashkey = 1;
    while (*str != '\0') {
        if (hashkey > size)
            hashkey = hashkey % size;
        hashkey = hashkey * *str;
        str++;
    }
    return hashkey;
}

void Hashtable::search(char *str) {}
