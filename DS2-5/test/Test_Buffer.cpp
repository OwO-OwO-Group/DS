#include "Buffer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool operator==(Column const &c1, Column const &c2)
{
    return strcmp(c1.putID, c2.putID) == 0 && strcmp(c1.getID, c2.getID) == 0 &&
           c1.weight == c2.weight;
}

void testRead()
{
    fstream fs;
    fs.open("pairs501.bin", ios::in | ios::binary);
    vector<Column> bufferResult, rightResult;

    if (fs) {

        // gen bufferResult
        BufferRead br = BufferRead(fs, 20, 10);
        Column *data;
        while (!fs.eof()) {
            if ((data = br.read()) != NULL)
                bufferResult.push_back(*data);
            else
                br.resetLimit(20);
        }

        // gen rightResult
        fs.clear();
        fs.seekg(0, ios::beg);

        Column tmp;
        while (!fs.eof()) {
            fs.read((char *)&tmp, sizeof(Column));
            rightResult.push_back(tmp);
        }

        fs.close();

        // compare
        if (!equal(bufferResult.begin(), bufferResult.end(),
                   rightResult.begin())) {
            cout << "read error" << endl;
            cout << "buffer row:" << bufferResult.size() << endl;
            cout << "file row:" << rightResult.size() << endl;
        }
        else
            cout << "file row:" << rightResult.size() << endl;
    }
    else
        cout << "fs error" << endl;
}

void testWrite() {}

int main()
{
    cout << "[Buffer test]" << endl;
    testRead();
    testWrite();
    return 0;
}
