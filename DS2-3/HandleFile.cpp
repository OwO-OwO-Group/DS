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

int HandleFile::fileInput(fstream &file, string message, string prefix)
{
    while (true) {

        // input file name
        cout << message;
        cin >> fileName;

        // quit program if input "0"
        if (fileName == "0")
            return EXIT;

        file.open(prefix + fileName + ".bin", ios::in | ios::binary);
        if (file)
            return BINARY;

        file.open(prefix + fileName + ".txt", ios::in);
        if (file)
            return NORMAL;

        errorHandling("Error : there is no such file!");
        continue; // input again
    }
}

bool HandleFile::txtToBin()
{
    if (fout.is_open())
        fout.close();
    fout.open("input" + fileName + ".bin", ios::out | ios::app | ios::binary);

    Data temp;
    while (fin >> temp) { // >> overload
        if (inputSuccess) {
            fout.write((char *) &temp, sizeof(temp));
        }
    }
    fout.close();

    if (fin.is_open())
        fin.close();

    fin.open("input" + fileName + ".bin", ios::in | ios::binary);

    return 0;
}

bool HandleFile::task1()
{
    int finmode = fileInput(fin, "Input (301, 302, ...[0]Quit): ", "input");

    if (finmode != EXIT) {
        if (finmode == NORMAL) txtToBin(); // also reopen file

        // prime table
        #define N 1000
        vector<int> prime;
        for (int i = 2; i < N; i++)
        {
            bool isprime = true;
            for (int j = 0; isprime && j < prime.size() && prime[j] <= sqrt(i); j++)
            {
                if (i % prime[j] == 0) isprime = false;
            }
            if (isprime) prime.push_back(i);
        }
        
        fin.seekg(0, fin.end);
        float row = fin.tellg() / sizeof(struct Column);
        fin.seekg(0, fin.beg);

        float size = row * 1.2;
        int mod_num = 0;
        for (int i = 0; !mod_num && i < prime.size(); i++)
            if (prime[i] > size) mod_num = prime[i];

        float step = row / 3;
        int two_mod_num = 0;
        for (int i = 0; !two_mod_num && i < prime.size(); i++)
            if (prime[i] > step) two_mod_num = prime[i];

        cout << mod_num << ' ' << two_mod_num << endl;

        // finmode == BINARY
        Data temp;
        while (fin) {
            fin.read((char *)&temp, sizeof(temp));
            // use tmep

            // hash func
            char* id = temp.getId();
            int hashkey = 1;
            for (int i = 0; id[i] != '\0'; i++) {
                if (hashkey > mod_num) hashkey = hashkey % mod_num;
                hashkey = hashkey * id[i];
            }

            hashkey = hashkey % mod_num;

            cout << hashkey << ' ';
            cout << temp;
        }
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return 0;
}