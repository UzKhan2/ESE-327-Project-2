#pragma once
#include<vector>
#include<string>
#include"Node.h"
#include<queue>
#include<iostream>
#include<map>
#include<cmath>

class DecisionTree {

private:

public:
	Node* root;
	DecisionTree();
	DecisionTree(Node* node);
	void setRoot(Node* value);
	//void expandChild(Node* node);
	void buildTree(vector < vector<string>> &dataset, string majorityClass);
	Node* getRoot();
	void printTree();
	map<string, int> findClasses(vector<vector<string>>& database);
	string findMajority(map<string, int>& table);
	float computeGini(map<string, int> distribution);
	float weightedGini(int totalSample, float leftGini, float rightGini, int leftSample, int rightSample);
};
