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
    // set buffer size
    BufferRead read1 = BufferRead(NULL, 0, 50), read2 = BufferRead(NULL, 0, 50);
    BufferWrite write1 = BufferWrite(NULL, 100);

    // set n
    int n = 200;

    // set file pointer
    fstream block1, block2, fout1, fout2;
    block1.open(nameA, ios::in | ios::out | ios::binary);
    block2.open(nameA, ios::in | ios::out | ios::binary);
    fout1.open(nameB, ios::in | ios::out | ios::binary);
    fout2.open(nameB, ios::in | ios::out | ios::binary);

    if (!block1 || !block2 || !fout1 || !fout2)
        throw "Open block error";

    int fileSize = getRow(block1);

    int offset = 0;

    do {
        // set block pointer to
        block1.seekg(offset, ios::beg);
        block2.seekg(offset + n, ios::beg);
        read1.setIn(block1);
        read2.setIn(block1);
        write1.setOut(fout1);

        // is eof
        if (block1.eof()) {
            // swap A B
            swap(block1, fout1);
            swap(block2, fout2);

            //
            n *= 2;
            offset = 0;

            // seekg A
            block1.clear();
            block1.seekg(0, ios::beg);
            block2.clear();
            block2.seekg(0, ios::beg);

            // seekg B
            fout1.clear();
            fout1.seekg(0, ios::beg);
        }
        else {
            read1.resetLimit(n);
            read2.resetLimit(n);
            mergeSortBlock(read1, read2, write1);
            offset += 2 * n;
        }
    } while (n >= fileSize);
}

Column *weightMax(Column *d1, Column *d2)
{
    if (d1 == NULL && d2 == NULL)
        return NULL;
    if (d1 == NULL)
        return d2;
    if (d2 == NULL)
        return d1;

    return d1->weight > d2->weight ? d1 : d2;
}

void mergeSortBlock(BufferRead &b1, BufferRead &b2, BufferWrite &w)
{
    Column *d1, *d2;
    do {
        d1 = b1.read();
        d2 = b2.read();
        w.write(weightMax(d1, d2));
    } while (d1 == NULL && d2 == NULL);
}

