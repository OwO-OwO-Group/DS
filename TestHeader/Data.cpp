#include "Data.h"

void Data :: updateCache()
{
    for (auto i : selectOrder)
        cache[i] = stringToInt(column[i]);
}

istream& operator>>(istream &in, Data &data)
{
    string input, temp;
    getline(in, input);

    if (!in)
        return in;
    // drop \r if the program running on unix
    // or unix like system, the string may be
    // contained '\r'
    if (input.back() == '\r')
        input.pop_back();

    // put \t for split easily
    input += '\t';

    // splitting
    int count = 0;
    inputSuccess = true;
    for (char c : input) {
        if (c != '\t')
            temp += c;
        else {
            data.column[count++] = temp;
            temp = "";
        }
    }

    if (count != DATA_SIZE)
        inputSuccess = false;

    data.updateCache();
    return in;
}

ostream& operator<<(ostream &out, Data &data)
{
    for (int i = 0; i < DATA_SIZE; i++)
        out << data.column[i] << (i < DATA_SIZE - 1 ? '\t' : '\n');

    return out;
}

void Data :: setData(int index, string data)
{
    column[index] = data;
    updateCache();
}

bool Data :: operator>(Data &b)
{
    for (auto i : selectOrder) {
        if (cache[i] > b.cache[i])
            return true;
        else if (cache[i] < b.cache[i])
            return false;
        // else cache[i] == b.cache[i] then i++
    }
    return false;
}

bool Data :: operator>=(Data &b)
{
    for (auto i : selectOrder) {
        if (cache[i] > b.cache[i])
            return true;
        else if (cache[i] < b.cache[i])
            return false;
        // else cache[i] == b.cache[i] then i++
    }
    return true;
}

bool Data :: operator<=(Data &b)
{
    for (auto i : selectOrder) {
        if (cache[i] < b.cache[i])
            return true;
        else if (cache[i] > b.cache[i])
            return false;
        // else cache[i] == b.cache[i] then i++
    }
    return true;
}

bool Data :: operator<(Data &b)
{
    for (auto i : selectOrder) {
        if (cache[i] < b.cache[i])
            return true;
        else if (cache[i] > b.cache[i])
            return false;
        // else cache[i] == b.cache[i] then i++
    }
    return false;
}

void Data :: print()
{
    for (auto i : selectOrder)
        cout << ' ' << column[i];
}

void Data :: println()
{
    for (auto i : selectOrder)
        cout << ' ' << column[i] << endl;
}