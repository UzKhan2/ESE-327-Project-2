#include<iostream>
#include<vector>
#include<string>
#include <cassert>	
#include <sstream>	//string stream lib	
#include<fstream>
#include <map> // hash table library
#include"Tree.h"


using namespace std;


vector<string> string_split(string str);
vector<string> get_artributes();
vector<vector<string>> scan_database();
void print_database(vector<vector<string>> &database);
bool digitCheck(string str);
vector<vector<string>> testData(vector<vector<string>> dataset);
map<string, int> findClasses(vector<vector<string>>& database);
string findMajority(map<string, int>& table);
void printMap(map<string, int>& table);



int dataset_size = 0;

vector<string> get_artributes() {

	string str;
	vector<string> artributes;

	cout << "Please enter all the artributes of the dataset (Seperate each artribute with a comma): ";
	getline(cin, str);
	artributes = string_split(str);	

	return artributes;

}


vector<string> string_split(string str) {
	
	vector<string> artributes;
	string temp;

	std::istringstream iss(str);
	while (getline(iss, temp, ',')) {
		artributes.push_back(temp);
	}

	return artributes;
}


vector<vector<string>> scan_database() {
	string fileName;
	fstream inFile;
	vector<vector<string>> database;
	cout << "Please enter a database file directory: ";
	cin >> fileName;
	inFile.open(fileName);

	if (!inFile) {
		cerr << "Can not open the file " << fileName << endl;
		exit(1);
	}

	string line, temp;
	while (getline(inFile, line))
	{	
		database.resize(database.size() + 1);
		std::istringstream iss(line);
		while (getline(iss, temp, ',')) {
			database[dataset_size].push_back(temp);
		}
		dataset_size++;
	}
	dataset_size--;

	return database;
}


void print_database(vector<vector<string>> &database) {
	for (int i = 0; i < database.size(); i++)
	{
		for (int j = 0; j < database[i].size(); j++)
		{
			cout << database[i][j] << ' ';
		}
		cout << endl;
	}

}

bool digitCheck(string str) {
	bool digit = true;
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i]) == 0)
			return false;
	}
	return true;
}


vector<vector<string>> testData(vector<vector<string>> dataset) {
	int splitIndex = int (0.7 * (dataset_size - 1));
	vector <vector<string>> testDataset;
	//testDataset.resize(dataset.size() - splitIndex);

	for (int i = splitIndex; i < dataset.size(); i++) {
		testDataset.push_back(dataset[i]);
	}
	return testDataset;
}


map<string, int> findClasses(vector<vector<string>>& database) {
	map<string, int> table;
	//cout << "Database size: " << database.size() << endl;
	for (int i = 0; i < database.size()-1; i++) {
		//cout << "Class: " << database[i][database[0].size() - 1] << endl;
		if (table.find(database[i][database[0].size() -1]) == table.end())
			table[database[i][database[0].size() -1]] = 1;

		else
			table[database[i][database[0].size() -1]]++;
	}

	return table;
}


string findMajority(map<string, int> &table) {
	int max_value = 0;
	string max_artribute;
	for (auto it = table.cbegin(); it != table.cend(); ++it) {
		if (it->second > max_value) {
			max_artribute = it->first;
			max_value = it->second;
		}//if
	}//for

	return max_artribute;
}

void printMap(map<string, int>& table) {
	for (auto it = table.begin(); it != table.end(); ++it)
	{
		cout << "Class: " << it->first << "   Value: " << it->second << endl;
	}
}


int main() {
	vector<string> artributes;
	vector<vector<string>> database, testDataset;
	string majority;
	Node* node = new Node("Root");
	DecisionTree tree(node);
	map<string, int> table;
	tree.setRoot(node);
 
	//artributes = get_artributes(); 
	//database = scan_database();
	//cout << "Dataset" << endl;
	//print_database(database);
	//testDataset = testData(database);
	//cout << "test Dataset" << endl;
	//print_database(testDataset);
	//table = findClasses(database);
	//cout << majority << endl;
	//printMap(table);
	 // tree test
	/*Node* n1 = new Node("1");
	Node* n2 = new Node("2");
	Node* n3 = new Node("3");
	Node* n4 = new Node("4");
	Node* n5 = new Node("5");
	Node* n6 = new Node("6");
	Node* n7 = new Node("7");
	Node* n8 = new Node("8");
	Node* n9 = new Node("9");
	tree.root->addChild(n1);
	tree.root->addChild(n2);
	tree.root->addChild(n3);
	vector<Node*> children;
	children = tree.root->getChildren();
	children[0]->addChild(n4);
	children[1]->addChild(n5);
	children[1]->addChild(n6);
	children[1]->addChild(n7);
	children[2]->addChild(n8);
	children[2]->addChild(n9);
	tree.printTree();*/


	return 0;
}
