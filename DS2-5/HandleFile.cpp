// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "HandleFile.h"
#include "Buffer.h"
#include "Merge.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector> // test
using namespace std;

int HandleFile::numberInput(string message, string errorMsg)
{
    int result;
    while (true) {
        cout << message;
        cin >> result;
        if (cin && result > -1)
            return result;
        else
            errorHandling("Error : " + errorMsg);
    }
}

int HandleFile::fileInput(string message, string prefix)
{
    while (true) {
        // input file name
        cout << message;
        cin >> fileName;

        // quit program if input "0"
        if (fileName == "0")
            return EXIT;

        // load .bin if exist
        fin.open(prefix + fileName + ".bin", ios::in | ios::binary);
        if (fin)
            return BINARY;

        errorHandling("Error : there is no such file!");
    }
}

bool cmp(const Column &a, const Column &b) { return a.weight > b.weight; }

bool HandleFile::task1()
{
    int finmode = fileInput("Input (501, 502, ...[0]Quit): ", "pairs");

    if (finmode == EXIT) {
        cout << "switch to menu" << endl;
        return 0;
    }

    // timing
    clock_t t = clock();
    // open two file
    string tmpFile1 = "tmp1.bin", tmpFile2 = "tmp2.bin";

    // stable sort
    fstream fs;
    fs.open(tmpFile1, ios::out | ios::binary);
    if (fs) {
        Column tmp[BUFFER_MAX_SIZE];
        while (fin.peek() != EOF) {
            fin.read((char *)&tmp, sizeof(Column) * BUFFER_MAX_SIZE);
            int len = fin.gcount() / sizeof(Column);
            stable_sort(tmp, tmp + len, cmp);
            fs.write((char *)&tmp, fin.gcount());
        }

        fs.close();
        fin.close();
    }

    // merge sort
    tmpFile1 = mergeSort(tmpFile1, tmpFile2);

    // rename
    rename(tmpFile1.c_str(), ("sorted" + fileName + ".bin").c_str());
    cout << "time: " << (clock() - t) << " ms" << endl;
    return 0;
}

bool HandleFile::task2()
{
    int finmode = fileInput("Input (501, 502, ...[0]Quit): ", "sorted");

    if (finmode == EXIT) {
        cout << "switch to menu" << endl;
        return 0;
    }

    return 0;
}
