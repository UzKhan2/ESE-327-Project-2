#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

class Node
{
public:
    string data;
    Node *left;
    Node *right;
    friend class DecisionTree;
};

class DecisionTree
{
public:
    DecisionTree();
    void addSplit(Node *parent);
    void display();
    void addData(Node *current, string in);
    void addData(Node *current, int val);
    double calculateEntropy(vector<vector<string>> database, Node *current);
    void extractClass(vector<vector<string>> database);
    void classNums(vector<vector<string>> database);
    vector<vector<string>> databaseResize(vector<vector<string>> database, float see, int j);
    vector<vector<string>> dataleftResize(vector<vector<string>> database, float see, int j);

    Node *root;
    vector<string> classes;
    vector<int> cNum;
};

DecisionTree::DecisionTree()
{
    root = new Node;
    root->data = "";
    root->left = nullptr;
    root->right = nullptr;
}

void DecisionTree::addSplit(Node *parent)
{
    if (parent == nullptr)
    {
        return;
    }

    // Create left branch
    Node *leftChild = new Node;
    leftChild->data = "";
    leftChild->left = nullptr;
    leftChild->right = nullptr;

    // Create right branch
    Node *rightChild = new Node;
    rightChild->data = "";
    rightChild->left = nullptr;
    rightChild->right = nullptr;

    // Connect to parent
    parent->left = leftChild;
    parent->right = rightChild;
}

void DecisionTree::display()
{
    if (root == nullptr)
    {
        cout << "The Tree is empty." << endl;
        return;
    }

    queue<Node *> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        Node *current = nodeQueue.front();
        nodeQueue.pop();

        cout << current->data << " ";

        if (current->left != nullptr)
        {
            nodeQueue.push(current->left);
        }

        if (current->right != nullptr)
        {
            nodeQueue.push(current->right);
        }
    }
    cout << endl;
}

void DecisionTree::addData(Node *current, string in)
{
    current->data = in;
}

void DecisionTree::addData(Node *current, int val)
{
    current->data = val;
}

double DecisionTree::calculateEntropy(vector<vector<string>> database, Node *current)
{
    vector<vector<string>> right;
    vector<vector<string>> left;
    vector<double> ent;
    double gain = 10;
    double entropy = 0.0;
    vector<int> pos;
    for (int i = 0; i < database.size(); i++)
    {
        for (int j = 0; j < database[i].size() - 1; j++)
        {
            right = databaseResize(database, stof(database[i][j]), j);
            left = dataleftResize(database, stof(database[i][j]), j);
            classNums(right);
            int total = 0;
            for (int k = 0; k < classes.size(); k++)
            {
                total += cNum[k];
            }

            entropy = 0.0;
            for (int k = 0; k < classes.size(); k++)
            {
                if (cNum[k] > 0)
                {
                    double probability = static_cast<double>(cNum[k]) / total;
                    entropy -= probability * log2(probability);
                    if (gain > entropy)
                    {
                        gain = entropy;
                        pos.push_back(i);
                        pos.push_back(j);
                        pos.push_back(k);
                    }
                    cout << entropy << " ";
                    ent.push_back(entropy);
                }
            }
        }
        cout << "gain " << gain;
        for (int i = 0; i < ent.size(); i++)
        {
            if (gain > ent[i])
            {
                gain = ent[i];
            }
        }
    }

    for (int i = 0; i < database.size(); ++i)
    {
        for (int j = 0; j < database[i].size() - 1; ++j)
        {
            database[i].erase(database[i].begin() + j);
        }
    }
    classNums(left);

    return entropy;
}

void DecisionTree::extractClass(vector<vector<string>> database)
{
    for (int i = 0; i < database.size(); i++)
    {
        bool flag = false;
        int j = database[i].size();

        string temp = database[i][j - 1];
        for (int j = 0; j < classes.size(); j++)
        {
            if (classes[j] == temp)
            {
                flag = true;
            }
        }
        if (!flag)
        {
            classes.push_back(temp);
        }
    }
}

void DecisionTree::classNums(vector<vector<string>> database)
{
    extractClass(database);
    cNum.resize(classes.size(), 0);
    for (int i = 0; i < classes.size(); i++)
    {
        cNum[i] = 0;
        for (int j = 0; j < database.size(); j++)
        {
            int k = database[j].size();

            string temp = database[j][k - 1];
            if (classes[i] == temp)
            {
                cNum[i]++;
            }
        }
    }
}

vector<vector<string>> DecisionTree::databaseResize(vector<vector<string>> database, float see, int j)
{
    vector<vector<string>> newDatabase;
    newDatabase = database;
    for (int i = 0; i < database.size(); i++)
    {

        if (stof(database[i][j]) > see)
        {
            newDatabase.push_back(database[i]);
        }
    }
    return newDatabase;
}

vector<vector<string>> DecisionTree::dataleftResize(vector<vector<string>> database, float see, int j)
{
    vector<vector<string>> newDatabase;
    newDatabase = database;
    for (int i = 0; i < database.size(); i++)
    {

        if (stof(database[i][j]) < see)
        {
            newDatabase.push_back(database[i]);
        }
    }
    return newDatabase;
}

int main()
{
    string file = "iris.data";
    ifstream infile(file);
    vector<string> tempV;
    vector<vector<string>> database;
    DecisionTree Tree;

    if (!infile.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    else
    {
        string line;
        string temp;
        while (getline(infile, line))
        {
            istringstream iss(line);
            while (getline(iss, temp, ','))
            {
                tempV.push_back(temp);
            }
            database.push_back(tempV);
            tempV.clear();
        }
    }

    Node *currentNode = Tree.root;
    for (int i = 0; i < database.size(); i++)
    {

        Tree.addData(currentNode, database[i][database[i].size() - 1]);
        if (currentNode->left == nullptr)
        {
            Tree.addSplit(currentNode);
            currentNode = currentNode->left;
        }

        else
        {
            if (currentNode->right == nullptr)
            {
                Tree.addSplit(currentNode);
            }
            currentNode = currentNode->right;
        }

        // Add the instance class to the current node
    }
    // Tree.display();
    //  Tree.classNums(database);
    Tree.calculateEntropy(database, Tree.root);

    infile.close();
    return 0;
}