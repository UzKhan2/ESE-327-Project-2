#include "Tree.h"
#include <map>


DecisionTree:: DecisionTree() {
	root = nullptr;
	}

DecisionTree::DecisionTree(Node* node) {
		root = node;
	}

void DecisionTree::setRoot(Node* value) {
	this->root = value;
}

Node* DecisionTree::getRoot() {
	return this->root;
}

void DecisionTree::buildTree(vector<vector<string>>& dataset, string majorityClass) {

}


void DecisionTree::printTree() {
	if (this->root == nullptr)
		cout << "This root does not have an node" << endl;
	//vector<string> temp;
	queue <Node*> q;
	q.push(this->root);
	Node* tempNode = new Node();
	while (!q.empty()) {
		int n = q.size();
		for (int i = 0; i < n; i++) {
			Node* current = q.front();
			cout << "Value: " << q.front()->getValue() << endl;
			q.pop();
			//temp.push_back(current->getValue());
			for (auto u : current->getChildren())
				q.push(u);
		}
		//temp.clear();
	}
}


map<string, int> DecisionTree::findClasses(vector<vector<string>>& database) {
	map<string, int> table;
	//cout << "Database size: " << database.size() << endl;
	for (int i = 0; i < database.size() - 1; i++) {
		//cout << "Class: " << database[i][database[0].size() - 1] << endl;
		if (table.find(database[i][database[0].size() - 1]) == table.end())
			table[database[i][database[0].size() - 1]] = 1;

		else
			table[database[i][database[0].size() - 1]]++;
	}

	return table;
}


string DecisionTree::findMajority(map<string, int>& table) {
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


float DecisionTree::computeGini(map<string, int> distribution) {
	float gini_index = 1.0;
	int totalSample = 0;
	for (auto it = distribution.begin(); it != distribution.end(); ++it)
	{
		totalSample += it->second;
	}

	for (auto it = distribution.begin(); it != distribution.end(); ++it)
	{
		gini_index = gini_index - pow(float(it->second / totalSample), 2);
	}
	return gini_index;
}


float DecisionTree::weightedGini(int totalSample, float leftGini, float rightGini, int leftSample, int rightSample) {
	return float(leftSample / totalSample) * leftGini + float(rightSample / totalSample) * rightGini;
}
