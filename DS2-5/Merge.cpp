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
    BufferRead read1 = BufferRead(NULL, 0, BUFFER_READ_SIZE),
               read2 = BufferRead(NULL, 0, BUFFER_READ_SIZE);
    BufferWrite write1 = BufferWrite(NULL, BUFFER_WRITE_SIZE);

    // set n
    int n = 200;

    // set file pointer
    fstream fs1, fs2;
    fs1.open(nameA, ios::in | ios::out | ios::binary);

    // create nameB
    fs2.open(nameB, ios::out | ios::binary);
    fs2.close();

    fs2.open(nameB, ios::in | ios::out | ios::binary);

    if (!fs1 || !fs2)
        throw "Open block error";

    int fileSize = getRow(fs1);

    int offset = 0;

    cout << "123: " << fileSize << endl;
    do {
        // set block pointer to
        cout << offset << " " << offset + n << endl;
        read1.setIn(fs1, offset);
        read2.setIn(fs1, offset + n);
        write1.setOut(fs2);
        // is eof
        if (offset > fileSize) {
            // swap A B
            swap(fs1, fs2);
            swap(nameA, nameB);

            //
            n *= 2;
            offset = 0;

            // seekg A
            fs1.clear();
            fs1.seekg(0, ios::beg);

            // seekg B
            fs2.clear();
            fs2.seekg(0, ios::beg);

            cout << "reset" << offset << endl;
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
    return nameB;
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
    Column *d1, *d2;
    do {
        d1 = b1.read();
        d2 = b2.read();
        w.write(weightMax(d1, d2));
    } while (d1 != NULL && d2 != NULL);
}

