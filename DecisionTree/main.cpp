#include<iostream>
#include<vector>
#include<string>
#include <cassert>	
#include <sstream>	//string stream lib	
#include<fstream>
#include <map> // hash table library
#include<random> // random library to test the accuracy of the decision tree model
#include"Tree.h"


using namespace std;

time_t start, end;
vector<string> string_split(string str);
vector<string> get_artributes();
vector<vector<string>> scan_database();
void print_database(vector<vector<string>> &database);
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
	time(&start);
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
	for (int i = 0; i < database.size(); i++) {
		//cout << "Class: " << database[i][database[0].size() - 1] << endl;
		if (table.find(database[i][database[0].size() -1]) == table.end())
			table[database[i][database[0].size() -1]] = 1;

		else
			table[database[i][database[0].size() -1]]++;
	}//for

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

void printMap(map<string, float>& table) {
	for (auto it = table.begin(); it != table.end(); ++it)
	{
		cout << "Class: " << it->first << "   Value: " << it->second << endl;
	}
}

int main() {
	time_t end;
	vector<string> artributes;
	vector<float> range;
	vector<vector<string>> database, testDataset;
	string majority;
	Node* node = new Node("Root");
	DecisionTree tree(node);
	map<string, int> table;
	map<string, float> bestSplit;
	tree.setRoot(node);
	//artributes = get_artributes(); 
	database = scan_database();
	//cout << "Dataset" << endl;
	//print_database(database);
	//testDataset = testData(database);
	//cout << "test Dataset" << endl;
	//print_database(testDataset);
	//table = findClasses(database);
	tree.buildTree(tree.getRoot(), database);
	tree.printTree();
	int totalSample = database.size(), correctPredict = 0;
	int classIndex = database[0].size() - 1;
	string result = " ";
	float accuracy = 0.0;
	for (int m = 0; m < database.size(); m++) {
		result = tree.predict(database[m]);
		if (!result.compare(database[m][classIndex])) {
			correctPredict++;
			//cout << "Correct Predict: " << correctPredict << endl;
		}
		//cout << "Expected: " << database[m][classIndex] << "		" << "Predicted: " << result << endl;
	}//for
	accuracy = static_cast<float>(correctPredict) / totalSample;
	cout << "Accuracy: " << accuracy << endl;

	time(&end);
	double time_taken = double(end - start);
	cout << "Time taken by program is : " << fixed
		<< time_taken;
	cout << " sec " << endl;
	return 0;
}
