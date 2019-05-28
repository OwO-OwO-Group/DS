// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "AdjacencyList.h"
#include "Header.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int AdjacencyList::numberInput(const string &message, const string &errorMsg)
{
    int result;
    while (true) {
        cout << message;
        cin >> result;

        if (cin && result > -1)
            return result;

        errorHandling("Error : " + errorMsg);
    }
}

float AdjacencyList::floatInput(const string &message, const string &errorMsg)
{
    float result;
    while (true) {
        cout << message;
        cin >> result;

        if (cin && 0 < result && result <= 1)
            return result;

        errorHandling("Error : " + errorMsg);
    }
}

bool operator<(Node const &n, string const id) { return n.id < id; }

// Add node if not exist
vector<node>::iterator AdjacencyList::addNode(const string &id)
{
    // Binary search
    auto it = lower_bound(nodes.begin(), nodes.end(), id);

    // has putID
    if (it == nodes.end() || it->id != id)
        it = nodes.insert(it, {id, vector<Link>()});

    return it;
}

bool operator<(Link const &l, float const weight) { return l.weight < weight; }

void AdjacencyList::connect(ID A, ID B, float weight)
{

    // add getID if not exist
    auto getIt = addNode(B);

    // add putID if not exist
    auto putIt = addNode(A);

    // linear search and insert
    vector<Link> &list = putIt->linked;
    auto insertIt = list.begin();
    while (insertIt != list.end() && insertIt->weight >= weight)
        ++insertIt;

    // insert
    insertIt = list.insert(insertIt, {B, weight});
}

#define notExist(vec1, str1) find(vec1.begin(), vec1.end(), str1) == vec1.end()
void AdjacencyList::BFS(const string &id, set<string> &v)
{
    // clear old vector
    v.clear();

    queue<string> bfsQueue;

    // add first node
    bfsQueue.push(id);
    string nodeID;

    // BFS
    while (!bfsQueue.empty()) {
        // current node
        nodeID = bfsQueue.front();
        bfsQueue.pop();

        // has not visited
        if (v.find(nodeID) == v.end()) {
            int i = indexMapping[nodeID];
            v.insert(nodeID);

            // put all data to vector and queue
            for (auto it : nodes[i].linked) {
                if (v.find(it.id) == v.end())
                    bfsQueue.push(it.id);
            }
        }
    }

    v.erase(v.begin());
}

void AdjacencyList::buildMapping()
{
    // clear old map
    indexMapping.clear();

    for (int i = 0; i < nodes.size(); i++)
        indexMapping[nodes[i].id] = i;
}

void AdjacencyList::debug_buildMapping()
{
    for (auto it : nodes)
        cout << it.id << " " << indexMapping[it.id] << endl;
}

int AdjacencyList::fileInput(const string &message, const string &prefix)
{
    while (true) {
        // input file name
        cout << message;
        cin >> fileName;

        // quit program if input "0"
        if (fileName == "0")
            return EXIT;

        // load .bin if exist
        fin.open(prefix + fileName + ".bin", ios::in | ios::binary);
        if (fin)
            return BINARY;

        errorHandling("Error : there is no such file!");
    }
}

bool AdjacencyList::task1()
{
    int finmode = fileInput("Input (401, 402, ...[0]Quit): ", "pairs");

    if (finmode == EXIT) {
        cout << "switch to menu" << endl;
        return 0;
    }

    // clear vector
    nodes.clear();

    // finmode == BINARY
    Column temp;

    // one by one load column
    while (fin.peek() != EOF) {
        fin.read((char *)&temp, sizeof(temp));
        connect(temp.putID, temp.getID, temp.weight);
    }

    fin.close();

    // speed up search id
    buildMapping();

    // output adj file
    fout.open("pairs" + fileName + ".adj", ios::out);
    if (fout) {
        int count = 1;
        for (auto putIt : nodes) {
            int count_L = 1;
            fout << "[" << count << "] " << putIt.id << " : total "
                 << putIt.linked.size() << " edges\n";
            for (auto linkIt : putIt.linked)
                fout << "\t(" << count_L++ << ") " << linkIt.id << " "
                     << linkIt.weight << " ";
            fout << endl << endl;
            count++;
        }

        fout.close();
    }

    return 0;
}

bool cmpINode(const INode &A, const INode &B)
{
    if (A.list.size() > B.list.size())
        return true;
    else if (A.list.size() < B.list.size())
        return false;
    else
        return A.id < B.id;
}

bool AdjacencyList::task2()
{
    // is task1 not done
    if (nodes.empty()) {
        cout << "Please execute task1 first." << endl;
        return 0;
    }

    // influence data
    vector<INode> inodes;

    // Traversing
    for (auto it : nodes) {
        INode tmp = {it.id, set<string>()}; //
        BFS(tmp.id, tmp.list);              // BFS
        inodes.push_back(tmp);              // push
    }

    // sort influence
    sort(inodes.begin(), inodes.end(), cmpINode);

    // save cnt file
    fout.open("pairs" + fileName + ".cnt", ios::out);
    if (fout) {
        int count = 1;
        for (auto infIt : inodes) {
            int count_L = 1;
            fout << "[" << count << "] " << infIt.id << " : total influence "
                 << infIt.list.size() << " people\n";
            for (auto listIt : infIt.list)
                fout << "\t(" << count_L++ << ") " << listIt << " ";
            fout << endl << endl;
            count++;
        }

        fout.close();
    }

    return 0;
}

void AdjacencyList::DFS(const string &id, set<string> &v, float valid)
{
    // clear old vector
    v.clear();

    stack<string> stack;

    // add first node
    stack.push(id);
    string nodeID;

    // DFS
    while (!stack.empty()) {
        // current node
        nodeID = stack.top();
        stack.pop();

        // has not visited
        if (v.find(nodeID) == v.end()) {
            int i = indexMapping[nodeID];
            v.insert(nodeID);

            // put all data to vector and queue
            for (auto it : nodes[i].linked) {
                if (v.find(it.id) == v.end() && it.weight >= valid)
                    stack.push(it.id);
            }
        }
    }

    v.erase(v.begin());
}

bool AdjacencyList::task3()
{
    // is task1 not done
    if (nodes.empty()) {
        cout << "Please execute task1 first." << endl;
        return 0;
    }

    // valid float (0,1]
    float valid = floatInput("input valid value:", "must in (0.0, 1.0]");

    // influence data
    vector<INode> inodes;

    // Traversing
    for (auto it : nodes) {
        INode tmp = {it.id, set<string>()}; //
        DFS(tmp.id, tmp.list, valid);       // DFS
        inodes.push_back(tmp);              // push
    }

    // sort influence
    sort(inodes.begin(), inodes.end(), cmpINode);

    // save cnt file
    fout.open("pairs" + fileName + ".inf", ios::out);
    if (fout) {
        int count = 1;
        for (auto infIt : inodes) {
            int count_L = 1;
            fout << "[" << count << "] " << infIt.id << " : total influence "
                 << infIt.list.size() << " people\n";
            for (auto listIt : infIt.list)
                fout << "\t(" << count_L++ << ") " << listIt << " ";
            fout << endl << endl;
            count++;
        }

        fout.close();
    }

    return 0;
}

