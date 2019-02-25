// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

// clang-format off
#define MENU_QUIT               0
#define MENU_MAXHEAP            1
#define MENU_DEAP               2

#define DATA_SIZE               12
#define DATA_ID                 0
#define DATA_NAME               1
#define DATA_DEPARTMENT_ID      2
#define DATA_DEPARTMENT_NAME    3
#define DATA_DAY_EXT_EDU        4
#define DATA_STAGE              5
#define DATA_STUDENTS           6
#define DATA_TEACHERS           7
#define DATA_GRADUATES          8
#define DATA_CITY               9
#define DATA_TYPE               10
#define DATA_ORDER              11
// clang-format on

static bool inputSuccess;
static int order;
void errorHandling(string message);

static string getOnlyDigits(string str)
{
    string tmp = "";
    for (char c : str)
        if (isdigit(c))
            tmp += c;

    return tmp;
}

static int stringToInt(string str)
{
    try {
        // "1,223,234,234,234"
        if (str[0] == '\"')
            str = getOnlyDigits(str);

        return stoi(str);
    }
    catch (exception e) {
        cout << "ERROR : stoi error!" << endl;
        cout << "Value : " << str << endl;
        return -1; // return error value
    }
}

// select column datatype must be integer
static vector<int> selectOrder = {DATA_STUDENTS};

class Data {
    string column[DATA_SIZE];

public:
    friend istream &operator>>(istream &in, Data &data)
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

        if (count != DATA_SIZE - 1)
            inputSuccess = false;
        else
            data.column[count] = to_string(order);

        return in;
    }

    friend ostream &operator<<(ostream &out, Data &data)
    {
        for (int i = 0; i < DATA_SIZE; i++)
            out << data.column[i] << (i < DATA_SIZE - 1 ? '\t' : '\n');

        return out;
    }

    int convertToInt(int num) { return stringToInt(column[num]); }

    bool operator>(Data &b)
    {
        for (auto i : selectOrder) {
            if (stringToInt(column[i]) > stringToInt(b.column[i]))
                return true;
            else if (stringToInt(column[i]) < stringToInt(b.column[i]))
                return false;
            // else stringToInt(column[i]) == stringToInt(b.column[i] then i++
        }
        return false;
    }

    bool operator>=(Data &b)
    {
        for (auto i : selectOrder) {
            if (stringToInt(column[i]) > stringToInt(b.column[i]))
                return true;
            else if (stringToInt(column[i]) < stringToInt(b.column[i]))
                return false;
            // else stringToInt(column[i]) == stringToInt(b.column[i] then i++
        }
        return true;
    }

    bool operator<=(Data &b)
    {
        for (auto i : selectOrder) {
            if (stringToInt(column[i]) < stringToInt(b.column[i]))
                return true;
            else if (stringToInt(column[i]) > stringToInt(b.column[i]))
                return false;
            // else stringToInt(column[i]) == stringToInt(b.column[i] then i++
        }
        return true;
    }

    bool operator<(Data &b)
    {
        for (auto i : selectOrder) {
            if (stringToInt(column[i]) < stringToInt(b.column[i]))
                return true;
            else if (stringToInt(column[i]) > stringToInt(b.column[i]))
                return false;
            // else stringToInt(column[i]) == stringToInt(b.column[i] then i++
        }
        return false;
    }

    void print()
    {
        for (auto i : selectOrder)
            cout << ' ' << column[i];
    }

    void println()
    {
        for (auto i : selectOrder)
            cout << ' ' << column[i] << endl;
    }

    int getorder() { return convertToInt(DATA_ORDER); }
};

#define preNode(i) (i - 1) / 2
#define rightNode(i) 2 * i + 2
#define leftNode(i) 2 * i + 1

class Heap {

    virtual bool cmp(int &cur, int &pre) = 0;
    bool exist(int index) { return index <= heap.size() - 1; }
    int largestChild(int cur)
    {
        int left = leftNode(cur);
        int right = rightNode(cur);
        int size = heap.size();

        // return size if cur no child
        if (!exist(left) && !exist(right))
            return size;

        // if right not exist, left is largest
        if (!exist(right))
            return left;

        // return largest child
        if (cmp(right, left))
            return right;
        else
            return left;
    }

protected:
    vector<Data> heap;

public:
    int size() { return heap.size(); }
    int root() { return 0; }
    int bottom() { return heap.size() - 1; }
    int leftbottom() { return pow(2, floor(log2(heap.size()))) - 1; }
    Data &operator[](int index) { return heap[index]; }

    // Reheap up from cur to root
    void reheapUp(int cur, int root = 0)
    {
        int pre = preNode(cur);

        // Compare and check is arrival root
        while (cur > root && cmp(cur, pre)) {
            swap(heap[cur], heap[pre]);
            cur = pre;

            // iterate until arrival root
            pre = preNode(cur);
        }
    }

    // Reheap down from root to leaf
    int reheapDown(int cur, int root = 0)
    {
        int child = largestChild(cur);

        // Compare and check is arrival leaf
        while (exist(child) && cmp(child, cur)) {
            swap(heap[cur], heap[child]);
            cur = child;

            // iterate until arrival left
            child = largestChild(cur);
        }
        return cur;
    }

public:
    void rebuild()
    {
        for (int i = heap.size() / 2; i >= 0; i--)
            reheapDown(i);
    }

    void push(Data temp)
    {
        heap.push_back(temp);
        // Reheap last item
        reheapUp(bottom());
    }

    void push_back(Data temp) { heap.push_back(temp); }

    void pop()
    {
        if (heap.size()) {
            swap(heap[root()], heap[bottom()]);
            heap.pop_back();
            reheapDown(root());
        }
    }

    void pop_back() { heap.pop_back(); }

    void print_ans()
    {
        string name[3] = {"root", "bottom", "left bottom"};
        int ans[3] = {0, bottom(), leftbottom()};
        for (int i = 0; i < 3; i++) {
            cout << name[i] << ":[" << heap[ans[i]].getorder() << ']';
            heap[ans[i]].println();
        }
    }
};

class MaxHeap : public Heap {
    bool cmp(int &cur, int &pre)
    {
        return (heap[cur] > heap[pre]) ? true : false;
    }
};

class MinHeap : public Heap {
    bool cmp(int &cur, int &pre)
    {
        return (heap[cur] < heap[pre]) ? true : false;
    }
};

class Deap {
    MaxHeap maxheap;
    MinHeap minheap;
    bool isminheap = true;

    bool isfull(int size)
    {
        return size == 1 ? false
                         : pow(2, floor(log2(size))) == pow(2, log2(size));
    }

    int bottom() { return isminheap ? minheap.size() - 1 : maxheap.size() - 1; }
    int leftbottom() { return pow(2, floor(log2(minheap.size()))) - 1; }

    Heap &bottomHeap()
    {
        if (isminheap)
            return minheap;
        else
            return maxheap;
    }

    int crosspond(int cur, int side)
    {
        if (side) {
            if (maxheap.size()) {
                while (cur > maxheap.size() - 1)
                    cur = (cur - 1) / 2;
                return cur;
            }
            else
                return -1;
        } // min look max
        else {
            if (minheap.size()) {
                while (cur > minheap.size() - 1)
                    cur = (cur - 1) / 2;
                return cur;
            }
            else
                return -1;
        } // max look min
    }

public:
    void push(Data temp)
    {
        if (isminheap && isfull(minheap.size() + 1))
            isminheap = false;
        else if (!isminheap && isfull(maxheap.size() + 1))
            isminheap = true;
        if (isminheap) {
            int cross = crosspond(minheap.size(), true);
            if (cross >= 0 && temp > maxheap[cross]) {
                swap(temp, maxheap[cross]);
                maxheap.reheapUp(cross);
            }
            minheap.push(temp);
        }
        else {
            int cross = crosspond(maxheap.size(), false);
            if (cross >= 0 && temp < minheap[cross]) {
                swap(temp, minheap[cross]);
                minheap.reheapUp(cross);
            }
            maxheap.push(temp);
        }
    }

    void pop_min()
    {
        if (minheap.size()) {
            if (isminheap) {
                swap(minheap[minheap.root()], minheap[minheap.bottom()]);
                minheap.pop_back();
                if (isfull(minheap.size() + 1))
                    isminheap = false;
            }
            else {
                swap(minheap[minheap.root()], maxheap[maxheap.bottom()]);
                maxheap.pop_back();
                if (isfull(maxheap.size() + 1))
                    isminheap = true;
            }
            int cur = minheap.reheapDown(minheap.root());
            int cross = crosspond(cur, true);
            if (minheap[cur] > maxheap[cross]) {
                swap(minheap[cur], maxheap[cross]);
                maxheap.reheapUp(cross);
            }
        }
    }

    void pop_max()
    {
        if (maxheap.size()) {
            if (!isminheap) {
                swap(maxheap[maxheap.root()], maxheap[maxheap.bottom()]);
                maxheap.pop_back();
                if (isfull(maxheap.size() + 1))
                    isminheap = true;
            }
            else {
                swap(maxheap[maxheap.root()], minheap[minheap.bottom()]);
                minheap.pop_back();
                if (isfull(minheap.size() + 1))
                    isminheap = false;
            }
            int cur = maxheap.reheapDown(maxheap.root());
            int cross = crosspond(cur, false);
            if (maxheap[cur] < minheap[cross]) {
                swap(maxheap[cur], minheap[cross]);
                minheap.reheapUp(cross);
            }
        }
    }

    void print_ans()
    {
        int ans[2] = {bottom(), leftbottom()};

        // println left bottom data
        Heap &bottomheap = bottomHeap();
        cout << "bottom"
             << ":[" << bottomheap[ans[0]].getorder() << ']';
        bottomheap[ans[0]].println();

        // left bottom always at minheap
        cout << "left bottom"
             << ":[" << minheap[ans[1]].getorder() << ']';
        minheap[ans[1]].println();
    }
};

class HandleFile {
    fstream fin;
    fstream fout;

    MaxHeap maxheap;
    MinHeap minheap; // test
    Deap deap;

    // common function
    int numberInput(string message, string errorMsg)
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

    void save(string saveName, vector<Data> &database)
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

    void dropHeader(fstream &file)
    {
        for (int i = 0; i < 3; ++i)
            file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string fileInput(fstream &file, string message, string prefix)
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

public:
    bool task1()
    {
        string fileName =
            fileInput(fin, "Input (601, 602, ...[0]Quit): ", "input");
        order = 1;
        // if fileName == "" then quit to menu
        if (fileName != "") {
            Data temp;
            while (fin >> temp) // >> overload
                if (inputSuccess) {
                    maxheap.push(temp);
                    order++;
                }

            maxheap.print_ans();
            // print out something
        }
        else {
            cout << "switch to menu" << endl;
        }

        fin.close();

        return fileName == ""; // {quit: 0, continue: 1}
    }

    bool task2()
    {
        string fileName =
            fileInput(fin, "Input (601, 602, ...[0]Quit): ", "input");
        order = 1;
        // if fileName == "" then quit to menu
        if (fileName != "") {
            Data temp;
            while (fin >> temp) // >> overload
                if (inputSuccess) {
                    deap.push(temp);
                    order++;
                }

            deap.print_ans();
            // print out something
        }
        else {
            cout << "switch to menu" << endl;
        }

        fin.close();

        return fileName == ""; // {quit: 0, continue: 1} }
    }
};

int main(int argc, char *argv[])
{
    int mode;   // 選單選項
    int result; // 指令回傳檢查
    while (true) {

        // 輸出選單
        cout << "              MENU              " << endl;
        cout << "* 0.          QUIT             *" << endl;
        cout << "* 1.        MAX-HEAP           *" << endl;
        cout << "* 2.          DEAP             *" << endl;
        cout << "choice: ";

        // 輸入選擇
        cin >> mode;

        HandleFile f;

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0; // 退出

        case MENU_MAXHEAP:
            result = f.task1();
            break;

        case MENU_DEAP:
            result = f.task2();
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // check is return successful
        if (result)
            return 1;
        else
            cout << endl;
    };
    return 0;
}

void errorHandling(string message)
{
    // 如果eof則強制結束程式
    if (cin.eof())
        exit(0);

    // 恢復cin的狀態
    cin.clear();

    // 消滅最多2048個字元遇到\n
    cin.ignore(2048, '\n');

    // 顯示錯誤訊息
    cout << message << endl;
}
