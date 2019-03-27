#include "Test.h"
#include <iostream>

using namespace std;

void doTest(bool result, string meg)
{
    cout << "[" << (result ? "done" : "fail") << "]:" << meg << endl;
}

bool testAVLInsert() { return false; }
bool test23Insert() { return false; }

void debug()
{
    cout << "==== debug ==== " << endl;
    doTest(testAVLInsert(), "AVL Insert");
    doTest(test23Insert(), "23 Insert");
}
