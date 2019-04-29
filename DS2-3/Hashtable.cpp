// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "Hashtable.h"
#include <iostream>
using namespace std;

Hashtable::Hashtable(int rowSize)
{
    rows = rowSize;
    buildPrime(20000);
    setSize();
    hashtable = new Table[size];
    for (int i = 0; i < size; i++)
        hashtable[i].hashcode = -1;
}

void Hashtable::setSize() {
    size = findPrimeMoreThan(rows * 1.2);
}

void Hashtable::setTwoStep() {
    twoStep = 1;
}

int Hashtable::hash(char *str)
{
    int hashkey = 1;
    while (*str != '\0') {
        if (hashkey > size)
            hashkey = hashkey % size;
        hashkey = hashkey * *str;
        str++;
    }
    return hashkey % size;
}

void Hashtable::insert(Data data) {
    int hash_index = hash(data.getId());
    int index = hash_index;
    while (hashtable[index].hashcode != -1) {
        index += twoStep;
        if (index >= size) index -= size;
    }
    hashtable[index].hashcode = hash_index;
    hashtable[index].column = data.getColumn();
}

ostream &operator<<(ostream &out, Table &table)
{
    if (table.hashcode != -1) {
        out << setw(10) << table.hashcode << ", "
            << setw(10) << table.column.sid << ", "
            << setw(10) << table.column.sname << ", "
            << setw(10) << table.column.average;
    }
    return out;
}

void Hashtable::save(fstream &fout) {
    int success = 0;
    int unsuccess = 0;
    int count = 0;
    int save_firstCount = 0;

    for (int i = 0; i < size; i++) {
        fout << '[' << setw(3) << i << "] " << hashtable[i] << endl;
        if (hashtable[i].hashcode != -1) {
            int num = (i - hashtable[i].hashcode)/twoStep + 1;
            success += (num < 0) ? (num + size) : num;
            count++;
        }
        else { // hashcode == -1
            unsuccess += (count + 1) * count / 2;
            if (count == i) save_firstCount = count;
            count = 0;
        }
    }

    // hashcode == -1
    unsuccess += (count + 1) * count / 2;
    if (hashtable[size - 1].hashcode != -1)
        unsuccess += count * save_firstCount;

    successful = success / double(rows);
    unsuccessful = unsuccess / double(size);
}

void Hashtable_Linear::save(fstream &fout) {
    fout << " --- Hash Table X --- (linear probing) " << endl;
    Hashtable::save(fout); // pair <success, unsuccess>
    cout << "Hash Table has been created" << endl;
    cout << "successful search: " << fixed << setprecision(4) << successful << " comparisons on average" << endl;
    cout << "unsuccessful search: " << fixed << setprecision(4) << unsuccessful << " comparisons on average" << endl;
}

void Hashtable_Double::setTwoStep() {
    twoStep = findPrimeMoreThan(rows / 3.);
}

void Hashtable_Double::save(fstream &fout) {
    fout << " --- Hash Table Y --- (double hashing) " << endl;
    Hashtable::save(fout); // pair <success, unsuccess>
    cout << "Hash Table has been created" << endl;
    cout << "successful search: " << fixed << setprecision(4) << successful << " comparisons on average" << endl;
}