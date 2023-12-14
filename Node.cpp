#include "Node.h"

Node::Node() : value(" "), gini_index(1.0), threshold(0.0), feature_index(0.0)
{
	this->gini_index = 1.0;
	this->value = " ";
	this->threshold = 0.0;
	this->feature_index = 0.0;
}

Node::Node(string val) : value(val), gini_index(1.0), threshold(0.0), feature_index(0.0)
{
	this->gini_index = 1.0;
	this->value = val;
	this->threshold = 0.0;
	this->feature_index = 0.0;
}

void Node::setGini(float index)
{
	gini_index = index;
}

void Node::setThreshold(float index)
{
	threshold = index;
};

void Node::setValue(string val)
{
	value = val;
}

void Node::setFeature(float feature)
{

	feature_index = feature;
}

void Node::addChild(Node *node)
{
	this->children.push_back(node);
}

void Node::setDataset(vector<vector<string>> &data)
{
	this->dataset = data;
}

float Node::getGini()
{
	return this->gini_index;
}

float Node::getThreshold()
{
	return this->threshold;
}

float Node::GetFeature()
{
	return this->feature_index;
}

vector<vector<string>> Node::getDataset()
{
	return this->dataset;
}

string Node::getValue()
{
	return this->value;
}

vector<Node *> Node::getChildren()
{
	return this->children;
}
