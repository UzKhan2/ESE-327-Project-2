#pragma once
#include <string>
#include <vector>

using namespace std;

class Node
{
private:
	float gini_index;
	float threshold;
	string value;
	float feature_index;

public:
	vector<vector<string>> dataset;
	vector<Node *> children;
	Node();
	Node(string val);
	void setGini(float index);
	void setThreshold(float index);
	void setValue(string val);
	void setFeature(float feature);
	void addChild(Node *node);
	void setDataset(vector<vector<string>> &data);
	float getGini();
	float getThreshold();
	float GetFeature();
	string getValue();
	vector<Node *> getChildren();
	vector<vector<string>> getDataset();
};
