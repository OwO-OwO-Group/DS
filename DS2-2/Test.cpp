// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include "Test.h"
#include <iostream>

using namespace std;

void doTest(bool result, string meg)
{
    cout << "[" << (result ? "done" : "fail") << "]:" << meg << endl;
}

bool testAVLInsert()
{
    // double rotation case 1
    // RL case 4, 2, 6, 1, 3, 5, 7, 16, 15
    // right inorder 1, 2, 3, 4, 5, 6, 7, 15, 16

    // double rotation case 2
    // RL case 4, 2, 6, 1, 3, 5, 7, 16, 15, 14
    // right inorder 1, 2, 3, 4, 5, 6, 7, 14, 15, 16

    return false;
}
bool test23Insert() { return false; }

void debug()
{
    cout << "==== debug ==== " << endl;
    doTest(testAVLInsert(), "AVL Insert");
    doTest(test23Insert(), "23 Insert");
}
