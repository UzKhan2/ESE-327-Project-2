#include"Node.h"


Node::Node() {
	float gini_index = 1.0;
	string value = value;

}


Node::Node(string val) {

	float gini_index = 1.0;
	string value = val;
}

void Node::setGini(float index) {
	gini_index = index;
}


void Node::setThreshold(float index) {
	threshold = index;
};


void Node::setValue(string val) {
	value = val;

}


void Node::setFeature(float feature) {

	feature_index = feature;
}


void Node::addChild(Node* node) {
	this->children.push_back(node);
}

