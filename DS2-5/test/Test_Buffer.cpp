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

void loadToVector(vector<Column> &v, fstream &fs)
{
    fs.clear();
    fs.seekg(0, ios::beg);

    Column tmp;
    while (fs.peek() != EOF) {
        fs.read((char *)&tmp, sizeof(Column));
        v.push_back(tmp);
    }
}

void compare(vector<Column> &v1, vector<Column> &v2, const string &name1,
             const string &name2)
{
    if (!equal(v1.begin(), v1.end(), v2.begin()) || v1.size() != v2.size()) {
        cout << "error" << endl;
        cout << name1 << " row:" << v1.size() << endl;
        cout << name2 << " row:" << v2.size() << endl;
    }
    else
        cout << name1 << " row:" << v1.size() << endl;
}

void testRead()
{
    cout << "[testRead]" << endl;
    fstream fs;
    fs.open("pairs501.bin", ios::in | ios::binary);
    vector<Column> bufferResult, rightResult;

    if (fs) {

        // gen bufferResult
        BufferRead br = BufferRead(fs, 20, 10);
        Column *data;
        while (br) {
            if ((data = br.read()) != NULL)
                bufferResult.push_back(*data);
            else
                br.resetLimit(20);
        }

        // gen rightResult
        loadToVector(rightResult, fs);

        fs.close();

        // compare
        compare(rightResult, bufferResult, "file", "buffer");
    }
    else
        cout << "fs error" << endl;
}

void testWrite()
{
    cout << "[testWrite]" << endl;
    fstream fs, fout;
    string debug1 = "debug501.bin", input1 = "pairs501.bin";
    // gen debug file
    fs.open(input1, ios::in | ios::binary);
    fout.open(debug1, ios::out | ios::binary);
    if (fs && fout) {
        Column tmp;
        BufferWrite bw = BufferWrite(fout, 200);
        while (fs.peek() != EOF) {
            fs.read((char *)&tmp, sizeof(Column));
            bw.write(&tmp);
        }

        bw.flush();
        fs.close();
        fout.close();
    }
    else
        cout << "gen write fs error" << endl;

    // read two file
    vector<Column> bufferResult, rightResult;
    fs.open(input1, ios::in | ios::binary);
    if (fs) {
        loadToVector(rightResult, fs);
        fs.close();
    }
    else
        cout << "load pairs fs error" << endl;

    fs.open(debug1, ios::in | ios::binary);
    if (fs) {
        loadToVector(bufferResult, fs);
        fs.close();
    }
    else
        cout << "load debug fs error" << endl;

    // compare
    compare(rightResult, bufferResult, "file", "buffer");
}

int main()
{
    cout << "[Buffer test]" << endl;
    testRead();
    testWrite();
    return 0;
}
