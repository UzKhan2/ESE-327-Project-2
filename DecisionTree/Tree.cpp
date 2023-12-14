#include "Tree.h"
#include <map>
#include<limits>

void printMap(map<string, int>& table) {
	for (auto it = table.begin(); it != table.end(); ++it)
	{
		cout << "Class: " << it->first << "   Value: " << it->second << endl;
	}
}


bool DecisionTree::digitCheck(string str) {
	bool digit = true;
	int dot_count = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '.') {
			dot_count++;
			continue;
		}

		if (isdigit(str[i]) == 0)
			return false;
	}

	if (dot_count > 1)
		return false;
	else 
		return true;
}


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

void DecisionTree::buildTree(Node* node, vector<vector<string>>& dataset) {
	vector<vector<string>> leftDataset, rightDataset;
	map<string, float> bestSplit;
	map<string, int> table;
	string majorityClass;
	int size = dataset.size();
	float temp;

	if (dataset.empty())
		return;
	table = findClasses(dataset);
	majorityClass = findMajority(table);
	bestSplit = findBestSplit(dataset, dataset[0].size());
	int featureIndex = bestSplit["featureIndex"];
	float threshold = bestSplit["threshold"];
	node->setGini(bestSplit["weightedGini"]);
	node->setThreshold(bestSplit["threshold"]);
	node->setFeature(bestSplit["featureIndex"]);
	node->setValue(majorityClass);

	if (bestSplit["weightedGini"] == 0) {
		cout << "Weighted Gini == 0" << endl;
		return;
	}

	for (int i = 0; i < size; i++) {

		temp = stof(dataset[i][featureIndex]);
		if (temp <= threshold) {
			leftDataset.push_back(dataset[i]);
		}//if

		else {
			rightDataset.push_back(dataset[i]);
		}//else
	}//for

	Node* leftChild = new Node(), *rightChild = new Node();
	node->addChild(leftChild);
	node->addChild(rightChild);
	buildTree(node->children[0], leftDataset);
	buildTree(node->children[1], rightDataset);

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
			cout << "Feature: " << q.front()->GetFeature() << endl;
			cout << "Threshold: " << q.front()->getThreshold() << endl;
			cout << "Class: " << q.front()->getValue() << endl;
			cout << "Gini Index: " << q.front()->getGini() << endl << endl;
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
	float total_prob = 0.0;
	int totalSample = 0;
	for (auto it = distribution.begin(); it != distribution.end(); ++it)
	{
		totalSample += it->second;
	}

	for (auto it = distribution.begin(); it != distribution.end(); ++it)
	{
		total_prob = total_prob + pow(float(it->second / static_cast<float>(totalSample)), 2);
	}
	return 1 - total_prob;
}


float DecisionTree::getWeightedGini(float leftGini, float rightGini, int leftSample, int rightSample) {
	int totalSample = leftSample + rightSample;
	float weightedLeft = static_cast<float>(leftSample) / totalSample * leftGini;
	float weightedRight = static_cast<float>(rightSample) / totalSample * rightGini;
	return weightedLeft + weightedRight;
}


map<string, float> DecisionTree::findBestSplit(vector<vector<string>>& dataset, int featureNum) {
	float bestThreshold = 0;  
	int bestFeature_index = 0, leftSample = 0, rightSample = 0;
	float bestGini = 1.0;
	int featureIndex = 0, rowIndex, size = dataset.size(), featureSize = dataset[0].size()-1;
	float currentThreshold = 0.0, step = 0.05, minValue = 0.0, maxValue = 0.0;
	string currentCat = " ";
	vector <float> range;
	float temp = 0.0, leftGini = 0.0, rightGini = 0.0, weightedGini = 0.0, gap = 0.0;
	map<string, int> leftSplit, rightSplit;
	map<string, float> output_table;
	map<string, map<string, int>> splitVector;
	for (featureIndex = 0; featureIndex < featureNum-1; featureIndex++) {
		for (rowIndex = 0; rowIndex < size; rowIndex++) {
			if (digitCheck(dataset[rowIndex][featureIndex])) {
				range = findColumnRange(dataset, featureIndex);
				minValue = range[0];
				maxValue = range[1];
				gap = range[1] - range[0];
				step = findStep(gap);
				currentThreshold = minValue + rowIndex * step;
				for (int i = 0; i < size; i++) {
				
					temp = stof(dataset[i][featureIndex]);
					if (temp <= currentThreshold) {
						if (leftSplit.find((dataset[i][featureSize])) == leftSplit.end())
							leftSplit[dataset[i][featureSize]] = 1;
						else
							leftSplit[dataset[i][featureSize]]++;
					}//if

					else {
						if (rightSplit.find((dataset[i][featureSize])) == rightSplit.end())
							rightSplit[dataset[i][featureSize]] = 1;

						else
							rightSplit[dataset[i][featureSize]]++;
					}//else
					
				}//for
				//cout << "Threshold: " << currentThreshold << endl;
				//cout << "Left Split: " << endl;
				//printMap(leftSplit);
				//cout << "Right Split: " << endl;
				//printMap(rightSplit);
				leftGini = computeGini(leftSplit);
				//cout << "Left Gini: " << leftGini << endl;
				rightGini = computeGini(rightSplit);
				//cout << "Right Gini: " << rightGini << endl;
				leftSample = getSum(leftSplit);
				rightSample = getSum(rightSplit);
				weightedGini = getWeightedGini(leftGini, rightGini, leftSample, rightSample);
				//cout << "Weighted Gini: " << weightedGini << endl << endl;
				if (weightedGini < bestGini) {
					output_table["threshold"] = currentThreshold;
					output_table["featureIndex"] = featureIndex;
					output_table["leftGini"] = leftGini;
					output_table["rightGini"] = rightGini;
					output_table["splitType"] = 0;
					output_table["weightedGini"] = weightedGini;
					bestGini = weightedGini;
				}
				leftSplit.clear();
				rightSplit.clear();
			}//if

		}//for

	}//for

	return output_table;
}



vector<float> DecisionTree::findColumnRange(vector<vector<string>>& dataset, int column_index) {
	int size = dataset.size();
	float maxValue = -1.0 * numeric_limits<float>::max();
	float minValue = numeric_limits<float>::max();
	float value = 0.0;
	vector<float> range;
	for (int i = 0; i < size; i++) {
		value = stof(dataset[i][column_index]);
		if (value > maxValue) {
			maxValue = value;
		}//if
		
		if (value < minValue) {
			minValue = value;
		}//if

	}//for
	range.push_back(minValue);
	range.push_back(maxValue);

	return range;
} //findColumnRange


float DecisionTree::findStep(float gap) {
	stringstream s;
	s << gap; // appending the float value to the streamclass 
	string result = s.str(); //converting the float value to string 
	bool count_flag = false;
	int count = 0;
	for (int i = 0; i < result.size(); i++) {
		if (count_flag == true) 
			count++;
		else {
			if (result[i] == '.')
				count_flag = true;
			else
				continue;		
		}//else
	}//for
	switch(count){
	case 0:
		return 0.5;
		break;
	case 1: 
		return 0.05;
		break;
	case 2: 
		return 0.005;
		break;
	default:
		return 1;
		break;
	}//switch
} // findStep


int DecisionTree::getSum(map<string, int> distribution) {
	int sum = 0;
	for (auto it = distribution.begin(); it != distribution.end(); ++it)
	{
		sum += it->second;
	}
	return sum;
}
