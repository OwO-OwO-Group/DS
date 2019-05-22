// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "AdjacencyList.h"
#include "Header.h"
#include <iostream>

using namespace std;

int AdjacencyList::numberInput(string message, string errorMsg)
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

int AdjacencyList::fileInput(string message, string prefix)
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
        continue; // input again
    }
}

bool AdjacencyList::task1()
{
    int finmode = fileInput("Input (401, 402, ...[0]Quit): ", "pairs");

    if (finmode != EXIT) {
        // finmode == BINARY
        Column temp;

        // one by one load column
        while (fin.peek() != EOF) {
            fin.read((char *)&temp, sizeof(temp));
        }
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return 0;
}

bool AdjacencyList::task2() { return 0; }

