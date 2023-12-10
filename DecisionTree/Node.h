#pragma once
#include<string>
#include<vector>

using namespace std;


class Node {

private:
	float gini_index;
	float threshold;
	string value;
	vector<Node*> children;
	float feature_index;
	vector<vector<string>> dataset;

public:
	Node();
	Node(string val);
	void setGini(float index);
	void setThreshold(float index);
	void setValue(string val);
	void setFeature(float feature);
	void addChild(Node* node);

};
