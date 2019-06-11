// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "Merge.h"
#include "Data.h"

using namespace std;

int getRow(fstream &fin)
{
    // counting rows number
    fin.seekg(0, fin.end);
    int row = fin.tellg() / sizeof(struct Column);
    fin.seekg(0, fin.beg);
    return row;
}

// return sorted file
string mergeSort(string nameA, string nameB)
{
    // set n
    int n = 1600;

    // set buffer size
    BufferRead read1 = BufferRead(NULL, 0, n / 4),
               read2 = BufferRead(NULL, 0, n / 4);
    BufferWrite write1 = BufferWrite(NULL, n / 2);

    // set file pointer
    fstream fs1, fs2;
    fs1.open(nameA, ios::in | ios::binary);

    int fileSize = getRow(fs1);
    // create nameB
    fs2.open(nameB, ios::out | ios::binary);

    if (!fs1 || !fs2)
        throw "Open block error";

    int offset = 0;

    do {
        // set block pointer to
        read1.setIn(&fs1, offset);
        read2.setIn(&fs1, offset + n);
        write1.setOut(&fs2);
        // is eof
        if (offset >= fileSize) {
            // swap A B
            swap(nameA, nameB);

            // increase block size
            n *= 2;
            offset = 0;

            // reopen
            fs1.close();
            fs2.close();
            fs1.open(nameA, ios::in | ios::binary);
            fs2.open(nameB, ios::out | ios::binary);
        }
        else {
            read1.resetLimit(n);
            read2.resetLimit(n);
            mergeSortBlock(read1, read2, write1);
            offset += 2 * n;
        }
    } while (n < fileSize);

    fs1.close();
    fs2.close();
    return nameA;
}

Column *weightMax(Column *d1, Column *d2)
{
    if (d1 == NULL && d2 == NULL)
        return NULL;
    if (d1 == NULL)
        return d2;
    if (d2 == NULL)
        return d1;

    if (d1->weight > d2->weight)
        return d1;
    else if (d1->weight < d2->weight)
        return d2;
    return d1;
}

void mergeSortBlock(BufferRead &b1, BufferRead &b2, BufferWrite &w)
{
    Column *d1, *d2, *max;
    do {
        d1 = b1.getCurrent();
        d2 = b2.getCurrent();

        // pop max
        max = weightMax(d1, d2);
        if (max == d1)
            b1.read();
        else if (max == d2)
            b2.read();

        w.write(max);
    } while (d1 != NULL || d2 != NULL);
}

