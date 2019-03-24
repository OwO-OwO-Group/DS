
// ��10�� 106127116 �\�h�� 10612150 �L���� ��T�G��
// must to use -std=c++11 or higher version

#include <ctime>
#include <iostream>
#include <string>
#include "Header.h"
#include "HandleFile.h"
using namespace std;

#define MENU_QUIT               0
#define MENU_MAXHEAP            1
#define MENU_DEAP               2
#define MENU_MINMAX             3

int main(int argc, char *argv[])
{
#ifdef DEBUG1111
    debug();
#else
    int mode;   // ���ﶵ
    int result; // ���O�^���ˬd
    while (true) {

        // ��X���
        cout << "              MENU              " << endl;
        cout << "* 0.          QUIT             *" << endl;
        cout << "* 1.        MAX-HEAP           *" << endl;
        cout << "* 2.          DEAP             *" << endl;
        cout << "* 3.         MINMAX            *" << endl;
        cout << "choice: ";

        // ��J���
        cin >> mode;

        HandleFile f;

        // �P�_��ܪ����e
        switch (mode) {
        case MENU_QUIT:
            return 0; // �h�X

        case MENU_MAXHEAP:
            result = f.task1();
            break;

        case MENU_DEAP:
            result = f.task1();
            break;

        case MENU_MINMAX:
            result = f.task1();
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
#endif
    return 0;
}
