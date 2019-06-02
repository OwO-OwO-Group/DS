// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "HandleFile.h"
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

bool HandleFile::task1()
{
    int finmode = fileInput("Input (401, 402, ...[0]Quit): ", "pairs");

    if (finmode == EXIT) {
        cout << "switch to menu" << endl;
        return 0;
    }

    return 0;
}

bool HandleFile::task2()
{
    // is task1 not done
    if (1) {
        cout << "Please execute task1 first." << endl;
        return 0;
    }

    return 0;
}
