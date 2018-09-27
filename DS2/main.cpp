#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define MENU_COPY_FILE        1 
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3
#define MENU_QUIT             4

static bool inputSuccess;
void errorHandling(string message);

class Data
{
public:
	string column[11];
	/*
	int id;
	string name;
	int departmentId;
	string departmentName;
	string dayAndExtEdu;
	string stage;
	int students;
	int teachers;
	int graduates;
	string city;
	string type;
	*/

	friend istream &operator>>(istream & in, Data & data)
	{
		string input, temp;
		getline(in, input);
		input += '\t';
		if (in) {
			int count = 0;
			inputSuccess = true;
			for (int i = 0; i < input.length(); i++) {
				if (input[i] != '\t') {
					temp += input[i];
				}
				else {
					data.column[count] = temp;
					temp = "";
					count++;
				}
			}
			if (count != 11) inputSuccess = false;
		}
		return in;
	}
	friend ostream& operator<<(ostream & out, Data & data)
	{
		for (int i = 0; i < 11; i++) {
			out << data.column[i] << '\t';
		}
		return out;
	}
};

class HandleFile
{
	vector<Data> database;
public:
	bool task1_input(fstream &fin, fstream &fout) {
		string temp;
		string fin_str, fout_str;
		while (true) {
			cout << "Input 201, 202, ...[0]Quit):";
			cin >> temp;
			if (temp == "0") return 0;
			else {
				fin_str = "input" + temp + ".txt";
				fout_str = "copy" + temp + ".txt";
			}
			fin.open(fin_str, ios::in);
			fout.open(fout_str, ios::out, ios::trunc);
			if (!fin) errorHandling("Error : there is no such file!");
			else return 1;
		}
	}
	bool task1() {
		fstream fin;
		fstream fout;

		if (task1_input(fin, fout)) {
			string trash;
			getline(fin, trash);
			getline(fin, trash);
			getline(fin, trash);
			// skip three line

			Data temp;
			while (fin >> temp) { // >> overload
				if (inputSuccess) database.push_back(temp);
			}
			for (vector<Data>::iterator i = database.begin(); i != database.end(); i++) {
				fout << *i << endl; // << overload
			}
			cout << database.size() << endl;
		}

		return 0;
	}
};

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

		HandleFile f;

		// �P�_��ܪ����e
		switch (mode) {
		case MENU_QUIT:
			return 0;               // �h�X
		case MENU_COPY_FILE:
			result = f.task1();       // ����1
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


