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
void print_database(vector<vector<string>> database);
bool digitCheck(string str);
vector<vector<string>> testData(vector<vector<string>> dataset);
string findMajority(vector<vector<string>>& database);



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
		cout << "Database size: " << database[dataset_size].size() << endl;
		dataset_size++;
	}
	dataset_size--;

	return database;
}


void print_database(vector<vector<string>> database) {
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


string findMajorityClass(vector<vector<string>>& database) {
	map<string, int> table;
	int max_value = 0;
	string max_artribute;
	for (int i = 0; i < database.size()-1; i++) {
		if (table.find(database[i][database[0].size() -1]) == table.end())
			table[database[i][database[0].size() -1]] = 1;

		else
			table[database[i][database[0].size() -1]]++;
	}

	for (auto it = table.cbegin(); it != table.cend(); ++it){
		if (it->second > max_value) {
			max_artribute = it->first;
			max_value = it->second;
				}//if
		}//for
	return max_artribute;
}


int main() {
	vector<string> artributes;
	vector<vector<string>> database, testDataset;
	DecisionTree tree;
	string majority;
	Node* node = new Node();
	tree.setRoot(node);
 
	//artributes = get_artributes();
	database = scan_database();
	//cout << "Dataset" << endl;
	//print_database(database);
	testDataset = testData(database);
	//cout << "test Dataset" << endl;
	print_database(testDataset);
	majority = findMajorityClass(testDataset);
	cout << majority << endl;

	



	return 0;
}

