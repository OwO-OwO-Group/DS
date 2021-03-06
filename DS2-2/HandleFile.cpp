// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version encoding=utf-8
#include "HandleFile.h"
#include "AVLTree.h"
#include "Data.h"
#include "Tree23.h"

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

void HandleFile::save(string saveName, vector<Data> &database)
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

void HandleFile::dropHeader(fstream &file)
{
    for (int i = 0; i < 3; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');
}

string HandleFile::fileInput(fstream &file, string message, string prefix)
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

bool HandleFile::task1()
{
    string fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", "input");
    vector<Data> database;
    // if fileName == "" then quit to menu
    if (fileName != "") {
        Tree23 tree;
        Data temp;
        while (fin >> temp) { // >> overload
            if (inputSuccess) {
                tree.insert(database.size(), temp.getData(DATA_NAME));
                database.push_back(temp);
            }
        }

        // show height
        cout << "Tree height = " << tree.height() << endl;

        // show root
        vector<int> result;
        tree.getRoot(result);
        for (int i = 0; i < result.size(); i++) {
            cout << (i + 1) << ": [" << (result[i] + 1) << "] ";
            database[result[i]].print();
            cout << endl;
        }
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return fileName == ""; // {quit: 0, continue: 1}
}

bool HandleFile::task2()
{
    string fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", "input");
    vector<Data> database;
    // if fileName == "" then quit to menu
    if (fileName != "") {
        AVLTree tree;
        Data temp;
        while (fin >> temp) { // >> overload
            if (inputSuccess) {
                tree.insert(database.size(),
                            temp.getData(DATA_DEPARTMENT_NAME));
                database.push_back(temp);
            }
        }

        // show height
        cout << "Tree height = " << tree.height() << endl;

        // show root
        vector<int> result;
        tree.getRoot(result);
        for (int i = 0; i < result.size(); i++) {
            cout << (i + 1) << ": [" << (result[i] + 1) << "] ";
            database[result[i]].print();
            cout << endl;
        }
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return fileName == ""; // {quit: 0, continue: 1}
}
