#include "Tree.h"


DecisionTree:: DecisionTree() {
	root = nullptr;
	}

DecisionTree::DecisionTree(Node* node) {
		root = node;
	}

void DecisionTree::setRoot(Node* value) {
	this->root = value;
}
