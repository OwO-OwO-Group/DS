#include <iostream>
#include <vector>

#define MENU_SORT_FILE        1
#define MENU_SINGLE_QUEUE     2
#define MENU_DOUBLE_QUEUE     3
#define MENU_QUIT             4

using namespace std;

// define data and queue
struct Data {
    int oid, arrival;
    int duration, timeout;
};

template <class T>
class Queue {
public:
    T& front();
    T& back();
    int size();
    void pop();
    void push(const T);
};

// task 1
void sortFile();
void shellSort(vector<Data> &);

// task 2
void singleQueue();

// task 3
void doubleQueue();

// general purpose
void errorHandling(string);

/*
 *  loadFile(vector<Data> &datas, string fileName)
 *  saveFile(vector<Data> &datas, string fileName)
 */
void loadFile(vector<Data> &, string);
void saveFile(vector<Data> &, string);

// implement
// task 1
void sortFile()
{
}

void shellSort()
{

}

// task 2
void singleQueue()
{

}

// task 3
void doubleQueue()
{
    // case 1
    // case 2
    // case 3
    // case 4
}

int main()
{
    int mode;                           // ���ﶵ
    int result;                         // ���O�^���ˬd
    while (true) {

        // ��X���
        cout << "              MENU              " << endl;
        cout << "* 1. SORT (sort & save a file) *" << endl;
        cout << "* 2. SINGLE (single queue)     *" << endl;
        cout << "* 3. DOUBLE (double queue)     *" << endl;
        cout << "* 4. Quit                      *" << endl;
        cout << "choice: ";

        // ��J���
        cin >> mode;

        // �P�_��ܪ����e
        switch (mode) {
        case MENU_QUIT:
            return 0;

        case MENU_SORT_FILE:
            break;

        case MENU_SINGLE_QUEUE:
            break;

        case MENU_DOUBLE_QUEUE:
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // �ˬd�^�ǭȬO�_��successful
        if (result)
            return 1;
        else cout << endl;
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
