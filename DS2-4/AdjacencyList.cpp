// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include "AdjacencyList.h"
#include "Header.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int AdjacencyList::numberInput(string message, string errorMsg)
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

bool operator<(Node const &n, string const id) { return n.id < id; }

// Add node if not exist
vector<node>::iterator AdjacencyList::addNode(string id)
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
    vector<Link> list = putIt->linked;
    auto insertIt = list.begin();
    while (insertIt != list.end() || insertIt->weight >= weight)
        insertIt++;

    // insert
    insertIt = list.insert(insertIt, {B, weight});
}

void AdjacencyList::BFS(ID id, vector<string> &v)
{
    // clear old vector
    v.clear();

    queue<string> bfsQueue;

    // add first node
    string nodeID = id;
    bfsQueue.push(nodeID);

    // BFS
    while (!bfsQueue.empty()) {

        // has not visited
        if (find(v.begin(), v.end(), nodeID) == v.end()) {
            int i = indexMapping[id];

            // put all data to vector and queue
            for (auto it : nodes[i].linked) {
                bfsQueue.push(it.id);
                v.push_back(it.id);
            }
        }

        // next node
        nodeID = bfsQueue.front();
        bfsQueue.pop();
    }
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

int AdjacencyList::fileInput(string message, string prefix)
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
        continue; // input again
    }
}

bool AdjacencyList::task1()
{
    int finmode = fileInput("Input (401, 402, ...[0]Quit): ", "pairs");

    if (finmode != EXIT) {
        // finmode == BINARY
        Column temp;

        // one by one load column
        while (fin.peek() != EOF) {
            fin.read((char *)&temp, sizeof(temp));
            connect(temp.getID, temp.putID, temp.weight);
        }

        buildMapping();
    }
    else
        cout << "switch to menu" << endl;

    fin.close();

    return 0;
}

bool AdjacencyList::task2()
{
    // is task1 done
    if (!nodes.empty()) {
        // influence data

        // Traversing
        for (auto it : nodes) {
        }

        // sort influence

        // save cnt file
    }
    else
        cout << "" << endl;

    return 0;
}

