#pragma once
#include<vector>
#include<string>
#include"Node.h"
#include<queue>
#include<iostream>
#include<map>
#include<cmath>
#include<sstream>

class DecisionTree {

private:

public:
	Node* root;
	DecisionTree();
	DecisionTree(Node* node);
	void setRoot(Node* value);
	//void expandChild(Node* node);
	void buildTree(Node* node, vector < vector<string>> &dataset);
	Node* getRoot();
	void printTree();
	map<string, int> findClasses(vector<vector<string>>& database);
	string findMajority(map<string, int>& table);
	float computeGini(map<string, int> distribution);
	float getWeightedGini(float leftGini, float rightGini, int leftSample, int rightSample);
	map<string, float> findBestSplit(vector<vector<string>>& dataset, int featureNum);
	vector<float> findColumnRange(vector<vector<string>>& dataset, int column_index);
	float findStep(float gap);
	int getSum(map<string, int> distribution);
	bool digitCheck(string str);
	string predict(vector<string> sample);
};
