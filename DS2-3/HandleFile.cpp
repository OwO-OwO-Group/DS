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

void HandleFile::save(Hashtable &table, string prefix)
{
    if (fout.is_open())
        fout.close();

    fout.open(prefix + fileName + ".txt", ios::out | ios::trunc);
    table.save(fout);

    fout.close();
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

        fin.open(prefix + fileName + ".bin", ios::in | ios::binary);
        if (fin)
            return BINARY;

        fin.open(prefix + fileName + ".txt", ios::in);
        if (fin)
            return NORMAL;

        errorHandling("Error : there is no such file!");
        continue; // input again
    }
}

bool HandleFile::txtToBin(string prefix)
{
    if (fout.is_open())
        fout.close();
    fout.open(prefix + fileName + ".bin", ios::out | ios::app | ios::binary);

    Data temp;
    while (fin >> temp) { // >> overload
        if (inputSuccess) {
            fout.write((char *) &temp, sizeof(temp));
        }
    }
    fout.close();

    if (fin.is_open())
        fin.close();
    fin.open(prefix + fileName + ".bin", ios::in | ios::binary);

    return 0;
}

int HandleFile::getRow() {
    fin.seekg(0, fin.end);
    int row = fin.tellg() / sizeof(struct Column);
    fin.seekg(0, fin.beg);
    return row;
}

bool HandleFile::task1()
{
    int finmode = fileInput("Input (301, 302, ...[0]Quit): ", "input");

    if (finmode != EXIT) {
        if (finmode == NORMAL) txtToBin("input"); // also reopen file

        // finmode == BINARY
        int rows = getRow();
        Hashtable_Linear table(rows);
        Data temp;
        while (fin.peek() != EOF) {
            fin.read((char *)&temp, sizeof(temp));
            table.insert(temp);
        }

        save(table, "linear");
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return 0;
}

bool HandleFile::task2()
{
    int finmode = fileInput("Input (301, 302, ...[0]Quit): ", "input");

    if (finmode != EXIT) {
        if (finmode == NORMAL) txtToBin("input"); // also reopen file

        // finmode == BINARY
        int rows = getRow();
        Hashtable_Double table(rows);
        Data temp;
        while (fin.peek() != EOF) {
            fin.read((char *)&temp, sizeof(temp));
            table.insert(temp);
        }

        save(table, "double");
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return 0;
}