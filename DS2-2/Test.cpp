// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "Test.h"
#include "AVLTree.h"
#include <iostream>

using namespace std;

void doTest(int result, string meg)
{
    cout << "[" << (result == 0 ? "done" : "fail" + to_string(result))
         << "]:" << meg << endl;
}

bool testAVLInsert_inorder(vector<string> &case1,
                           vector<string> &case1RightInorder)
{
    vector<string> result;
    AVLTree tree;

    for (auto item : case1)
        tree.insert(0, item);

    tree.inorder(result);
    if (result != case1RightInorder) {
        cout << endl;
        for (auto item : result)
            cout << item << ", ";

        cout << endl;
        return false;
    }
    result.clear();
    tree.clear();
    return true;
}

int testAVLInsert()
{

    vector<string> result, cases, rightResult;
    AVLTree tree;

    // double rotation case 1 RL
    cases = {"4", "2", "6", "1", "3", "5", "7", "G", "F"};
    rightResult = {"1", "2", "3", "4", "5", "6", "7", "F", "G"};
    if (!testAVLInsert_inorder(cases, rightResult))
        return 1;

    // double rotation case 2 RL
    cases = {"4", "2", "6", "1", "3", "5", "7", "G", "F", "E"};
    rightResult = {"1", "2", "3", "4", "5", "6", "7", "E", "F", "G"};
    if (!testAVLInsert_inorder(cases, rightResult))
        return 2;

    return 0;
}
int test23Insert() { return 1; }

void debug()
{
    cout << "==== debug ==== " << endl;
    doTest(testAVLInsert(), "AVL Insert");
    doTest(test23Insert(), "23 Insert");
}
