#pragma once
#include<vector>
#include<string>
#include"Node.h"

class DecisionTree {

private:
	Node *root;

public:
	DecisionTree();
	DecisionTree(Node* node);
	void setRoot(Node* value);
	//void expandChild(Node* node);
	void buildTree(vector < vector<string>> dataset, int atributeSize);


};
