// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version encoding=utf-8
#include "HandleFile.h"

int HandleFile ::numberInput(string message, string errorMsg)
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

void HandleFile ::save(string saveName, vector<Data> &database)
{
    // closs all file
    if (fin.is_open())
        fin.close();

    fout.open(saveName, ios::out | ios::trunc);
    for (Data i : database)
        fout << i; // << overload

    fout.close();

    cout << "Total number of records: " << database.size() << endl;
}

void HandleFile ::dropHeader(fstream &file)
{
    for (int i = 0; i < 3; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');
}

string HandleFile ::fileInput(fstream &file, string message, string prefix)
{
    string fileName;
    while (true) {

        // input file name
        cout << message;
        cin >> fileName;

        // quit program if input "0"
        if (fileName == "0")
            return "";

        file.open(prefix + fileName + ".txt", ios::in);

        if (!file) {
            errorHandling("Error : there is no such file!");
            continue; // input again
        }

        dropHeader(file);

        return fileName;
    }
}

bool HandleFile ::task1()
{
    string fileName = fileInput(fin, "Input (101, 102, ...[0]Quit): ", "input");
    // if fileName == "" then quit to menu
    if (fileName != "") {
    }
    else {
        cout << "switch to menu" << endl;
    }

    fin.close();

    return fileName == ""; // {quit: 0, continue: 1}
}

bool HandleFile ::task2()
{
    string fileName = fileInput(fin, "Input (101, 102, ...[0]Quit): ", "input");
    // if fileName == "" then quit to menu
    if (fileName != "") {
    }
    else {
        cout << "switch to menu" << endl;
    }

    fin.close();

    return fileName == ""; // {quit: 0, continue: 1}
}
