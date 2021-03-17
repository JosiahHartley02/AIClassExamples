#pragma once
#include "Actor.h"

class Node;

class Edge : public Actor
{
public:
	Edge(Node* NodeOne, Node* NodeTwo);
	Node* connectedNodeOne;
	Node* connectedNodeTwo;
	float cost;
	void draw() override;
	void update(float deltaTime) override;
};
