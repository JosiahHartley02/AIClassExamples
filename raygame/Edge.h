#pragma once
#include "Actor.h"

class Node;

class Edge : public Actor
{
public:
	Edge(Node* NodeOne, Node* NodeTwo);
	Node* connectedNodeOne;
	Node* connectedNodeTwo;
	float cost() { return m_cost; }
	void updateCost();
	void draw() override;
	void update(float deltaTime) override;
private:
	float m_cost;
};
