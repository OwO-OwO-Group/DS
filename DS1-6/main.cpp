// 第11組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version encoding=utf-8
#include <algorithm>
#include <climits>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

// clang-format off

#define MENU_QUIT               0
#define MENU_LOAD_DATA          1
#define MENU_SHOW_RANGE         2
#define MENU_REMOVE_DATA        3

#define DATA_NUMERO             0
#define DATA_NAME               1
#define DATA_TYPE1              2
#define DATA_TYPE2              3
#define DATA_TOTAL              4
#define DATA_HP                 5
#define DATA_ATTACK             6
#define DATA_DEFENSE            7
#define DATA_SP_ATK             8
#define DATA_SP_DEF             9
#define DATA_SPEED              10
#define DATA_GENERATION         11
#define DATA_LEGENDARY          12

#define DATA_SIZE               13
// clang-format on

using namespace std;

static bool inputSuccess;
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

class Data {
    string column[DATA_SIZE];

    void printColumn(int select)
    {
        cout << left;
        switch (select) {
        case DATA_NAME:
            cout << setw(25);
            break;
        case DATA_GENERATION:
            cout << setw(13);
            break;
        default:
            cout << setw(10);
        };

        cout << column[select];
    }

public:
    void setColumns(string initColumn[DATA_SIZE])
    {
        copy(initColumn, initColumn + DATA_SIZE, column);
    }

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

        if (count != DATA_SIZE)
            inputSuccess = false;

        return in;
    }

    string operator[](int i) const { return column[i]; }
    string &operator[](int i) { return column[i]; }

    friend ostream &operator<<(ostream &out, Data &data)
    {
        for (int i = 0; i < DATA_SIZE; i++)
            out << data.column[i] << (i < DATA_SIZE - 1 ? '\t' : '\n');

        return out;
    }

    void print(vector<int> &select)
    {
        for (auto i : select)
            printColumn(i);
        cout << '\n';
    }

    void printAll()
    {
        for (int i = 0; i < DATA_SIZE; i++)
            printColumn(i);
        cout << '\n';
    }

    int convertToInt(int num) { return stringToInt(column[num]); }
};

enum BSTException { NullTree, NotFound };
string getBSTExceptionString(BSTException e)
{
    switch (e) {
    case NullTree:;
        return "Null tree";
    case NotFound:;
        return "Not Found Node";
    }

    return "Undefine";
}

class BST {

    typedef struct Node {
        vector<shared_ptr<Data>> datas;
        Node *left, *right;
    } Node;

    typedef struct FoundNode {
        Node *root, *child;
        bool isLeft;
    } FoundNode;

    // select column datatype must be integer
    int select;

    Node *treeRoot;
    int visitedCounter;
    bool cmpAMoreThenB(shared_ptr<Data> a, shared_ptr<Data> b)
    {
        return a->convertToInt(select) > b->convertToInt(select);
    }

    bool cmpALessThenB(shared_ptr<Data> a, shared_ptr<Data> b)
    {
        return a->convertToInt(select) < b->convertToInt(select);
    }

    bool cmpEqual(shared_ptr<Data> a, shared_ptr<Data> b)
    {
        return (*a)[select] == (*b)[select];
    }

    Node *insert(Node *root, shared_ptr<Data> data)
    {
        // is null
        if (root == nullptr) {
            Node *newNode = new Node;
            newNode->datas.push_back(data);
            newNode->left = newNode->right = nullptr;
            return newNode;
        }
        else {
            // recurive or push back
            if (cmpEqual(data, root->datas.back()))
                root->datas.push_back(data);
            else if (cmpALessThenB(data, root->datas.back()))
                root->left = insert(root->left, data);
            else
                root->right = insert(root->right, data);

            return root;
        }
    }

    void clear(Node *&root)
    {
        if (root == nullptr)
            return;
        clear(root->right);
        clear(root->left);
        delete root;
        root = nullptr;
    }

    Node *pickInorderSuccessor(Node *root, bool success = false)
    {
        Node *successor, *pre;
        successor = pre = root->right;
        if (successor == nullptr)
            return nullptr;

        while (successor->left != nullptr)
            pre = successor, successor = successor->left;

        if (success)
            pre->left = nullptr;

        return successor;
    }

    Node *remove(Node *root, shared_ptr<Data> data)
    {
        if (root == nullptr)
            return nullptr;

        // not only one data in node
        if (root->datas.size() > 1) {
            vector<shared_ptr<Data>> *datas = &root->datas;
            auto found = std::remove(datas->begin(), datas->end(), data);
            datas->erase(found, datas->end());
            return root;
        }
        else {
            Node *result = nullptr;
            // two child
            if (root->left != nullptr && root->right != nullptr) {
                result = pickInorderSuccessor(root, true);
                result->left = root->left;
                result->right = root->right;
            }
            else if (root->left != nullptr)
                result = root->left, delete root;
            else if (root->right != nullptr)
                result = root->right, delete root;
            else
                delete root;

            return result;
        }
    }

    FoundNode inner_find(int key)
    {
        Node *pre, *cur;
        pre = cur = treeRoot;
        bool isLeft = false;
        while (cur != nullptr) {
            // not null
            // recurive or return
            int rootKey = cur->datas.back()->convertToInt(select);
            if (rootKey == key)
                break;
            else if (key < rootKey)
                pre = cur, cur = cur->left, isLeft = true;
            else
                pre = cur, cur = cur->right, isLeft = false;
        }

        return {pre, cur, isLeft};
    }

    void inorderTraversal(Node *root, vector<shared_ptr<Data>> &result, int min,
                          int max)
    {
        if (root == nullptr)
            return;
        visitedCounter++;
        int rootKey = root->datas.back()->convertToInt(select);

        if (rootKey < max)
            inorderTraversal(root->right, result, min, max);

        if (min <= rootKey && rootKey <= max)
            for (auto it : root->datas)
                result.push_back(it);

        if (min < rootKey)
            inorderTraversal(root->left, result, min, max);
    }

    int getHight(Node *node)
    {
        int result = 0;
        if (node != nullptr)
            result = 1 + max(getHight(node->left), getHight(node->right));

        return result;
    }

public:
    void clear() { clear(treeRoot); }
    void insert(shared_ptr<Data> data) { treeRoot = insert(treeRoot, data); }
    void setOrder(int order = DATA_HP) { select = order; }
    int getHight() { return getHight(treeRoot); }

    BST()
    {
        treeRoot = nullptr;
        setOrder();
    }

    void remove(shared_ptr<Data> data)
    {
        if (treeRoot == nullptr)
            throw BSTException::NullTree;

        FoundNode found = inner_find(data->convertToInt(select));
        if (found.child == nullptr)
            throw BSTException::NotFound;

        if (found.child == found.root)
            treeRoot = remove(found.child, data);
        else if (found.isLeft)
            found.root->left = remove(found.child, data);
        else
            found.root->right = remove(found.child, data);
    }

    vector<shared_ptr<Data>> find(int key)
    {
        if (treeRoot == nullptr)
            throw BSTException::NullTree;

        Node *found = inner_find(key).child;
        if (found == nullptr)
            throw BSTException::NotFound;

        return found->datas;
    }

    int range(vector<shared_ptr<Data>> &result, int min = INT_MIN,
              int max = INT_MAX)
    {
        if (treeRoot == nullptr)
            throw BSTException::NullTree;

        // inorder traversal
        visitedCounter = 0;
        inorderTraversal(treeRoot, result, min, max);
        return visitedCounter;
    }

    int getMinKey()
    {
        Node *cur = treeRoot;
        if (cur == nullptr)
            throw BSTException::NullTree;

        // always left side
        while (cur->left != nullptr)
            cur = cur->left;

        return cur->datas.back()->convertToInt(select);
    }

    int getMaxKey()
    {
        Node *cur = treeRoot;
        if (cur == nullptr)
            throw BSTException::NullTree;

        // always right side
        while (cur->right != nullptr)
            cur = cur->right;

        return cur->datas.back()->convertToInt(select);
    }
};

class HandleFile {
    fstream fin;
    fstream fout;

    BST bst, bstAtt, bstDef;

    vector<shared_ptr<Data>> database;
    Data cloumnName;

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

    void dropHeader(fstream &file)
    {
        for (int i = 0; i < 1; ++i)
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

    void dataOutput(vector<int> &selectOrder, vector<shared_ptr<Data>> &db)
    {

        cout << left << setw(8) << " ";
        cloumnName.print(selectOrder);

        int count = 1;

        for (auto i : db)
            cout << '[' << right << setw(5) << count << "] ",
                i->print(selectOrder), count++;

        cout << '\n';
    }

    void init()
    {
        bst.clear();
        bstAtt.clear();
        bstDef.clear();
        database.clear();
    }

    // use in task1 & set select order
    bool task1_input(string &fileName, vector<shared_ptr<Data>> &database)
    {
        fileName = fileInput(fin, "Input (601, 602, ...[0]Quit): ", "input");

        // if fileName == "" then quit to menu
        if (fileName != "") {
            Data temp;
            while (fin >> temp) // >> overload
                if (inputSuccess)
                    database.push_back(shared_ptr<Data>(new Data(temp)));
        }
        else {
            cout << "switch to menu" << endl;
        }

        fin.close();

        return fileName != ""; // {quit: 0, continue: 1}
    }

    static bool cmp(shared_ptr<Data> a, shared_ptr<Data> b)
    {
        return a->convertToInt(DATA_NUMERO) < b->convertToInt(DATA_NUMERO);
    }

public:
    HandleFile()
    {
        string names[DATA_SIZE] = {"#",        "Name",   "Type 1", "Type 2",
                                   "Total",    "HP",     "Attack", "Defense",
                                   "Sp.Atk",   "Sp.Def", "Speed",  "Generation",
                                   "Legendary"};
        cloumnName.setColumns(names);
    }

    ~HandleFile()
    {
        // clear tree
        bst.clear();
        bstAtt.clear();
        bstDef.clear();
        database.clear();
    }

    bool task1()
    {
        // init
        init();

        // load file
        string fileName;

        if (!task1_input(fileName, database))
            return 0;

        // sort NUMERO
        sort(database.begin(), database.end(), cmp);

        // display vector
        vector<int> selectOrder(6);
        selectOrder = {DATA_NUMERO, DATA_NAME,   DATA_TYPE1,
                       DATA_HP,     DATA_ATTACK, DATA_DEFENSE};

        dataOutput(selectOrder, database);

        // build tree HP
        bst.setOrder();
        for (auto it : database)
            bst.insert(it);

        bstAtt.setOrder(DATA_ATTACK);
        for (auto it : database)
            bstAtt.insert(it);

        bstDef.setOrder(DATA_DEFENSE);
        for (auto it : database)
            bstDef.insert(it);
        // show tree hight
        cout << "HP tree height = " << bst.getHight() << endl;

        return 0;
    }

    bool task2()
    {

        try {
            vector<shared_ptr<Data>> result;
            int min, minAtt, minDef;
            // input range
            min =
                numberInput("Threshold (a positive integer):", "out of range!");
            minAtt =
                numberInput("Threshold (a positive integer):", "out of range!");
            minDef =
                numberInput("Threshold (a positive integer):", "out of range!");
            // get range
            int visted = bst.range(result, min);
            // show visited times
            cout << "Number of visited nodes = " << visted << endl;

            vector<int> selectOrder(1);
            selectOrder = {DATA_HP};
            dataOutput(selectOrder, result);

            // get range
            result.clear();
            visted = bstAtt.range(result, minAtt);
            // show visited times
            cout << "Att Number of visited nodes = " << visted << endl;

            selectOrder = {DATA_ATTACK};
            dataOutput(selectOrder, result);
            // get range
            result.clear();
            visted = bstDef.range(result, minDef);
            // show visited times
            cout << "Def Number of visited nodes = " << visted << endl;

            selectOrder = {DATA_DEFENSE};
            dataOutput(selectOrder, result);
        }
        catch (BSTException e) {
            cout << getBSTExceptionString(e) << endl;
        }
        return 0;
    }

    bool task3()
    {
        try {
            // get max items
            int maxKey = bst.getMaxKey();
            vector<shared_ptr<Data>> max = bst.find(maxKey);

            // show max one data all field
            cloumnName.printAll();

            auto max1 = *max.begin();
            max1->printAll();

            // delete BST max one data
            bst.remove(max1);

            // delete array max
            auto found = std::remove(database.begin(), database.end(), max1);
            database.erase(found, database.end());

            // show tree hight
            cout << "HP tree height = " << bst.getHight() << endl;
        }
        catch (BSTException e) {
            cout << getBSTExceptionString(e) << endl;
        }
        return 0;
    }
};

int main(int argc, char *argv[])
{
    int mode;   // 選單選項
    int result; // 指令回傳檢查

    HandleFile f;
    while (true) {
        // 輸出選單
        cout << "              MENU              " << endl;
        cout << "* 0. Quit                      *" << endl;
        cout << "* 1. Load Data                 *" << endl;
        cout << "* 2. Show Range                *" << endl;
        cout << "* 3. Remove Max                *" << endl;
        cout << "choice: ";

        // 輸入選擇
        cin >> mode;

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0;

        case MENU_LOAD_DATA:
            result = f.task1();
            break;

        case MENU_SHOW_RANGE:
            result = f.task2();
            break;

        case MENU_REMOVE_DATA:
            result = f.task3();
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // 檢查回傳值是否為successful
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

