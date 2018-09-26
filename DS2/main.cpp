#include <iostream>
#include <cstring>
using namespace std;
 
#define MENU_COPY_FILE        1 
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3
#define MENU_QUIT             4

void errorHandling(string message);

int main(int argc, char *argv[])
{
    int mode;                           // ���ﶵ
    int result;                         // ���O�^���ˬd
    while (1) {

        // ��X���
        cout << "              MENU              " << endl;
        cout << "* 1. COPY (Read & Save a file) *" << endl;
        cout << "* 2. FILTER (Reduce a file)    *" << endl;
        cout << "* 3. MERGE (Join two files)    *" << endl;
        cout << "* 4. Quit                      *" << endl;
        cout << "choice: ";

        // ��J���
        cin >> mode;
         
        // �P�_��ܪ����e
        switch (mode) {
            case MENU_QUIT:
                return 0;               // �h�X
            case MENU_COPY_FILE:
                // result = task1();       // ����1
                break;
            case MENU_FILTER_FILE:
                // result = task2();       // ����2
                break;
            case MENU_MERGE_FILE:
                // result = task3();       // ����3
                break;
            default:
                errorHandling("Error: Command not found!"); 
                continue;
        }

        // �ˬd�^�ǭȬO�_��successful
        if (result)
            return 1;                   
    };
    return 0;
}

void errorHandling(string message)
{
    // �p�Geof�h�j����{��
    if (cin.eof())
        exit(0);

    // ��_cin�����A 
    cin.clear();

    // �����̦h2048�Ӧr���J��\n 
    cin.ignore(2048, '\n');

    // ��ܿ��~�T��
    cout << message << endl;
}
