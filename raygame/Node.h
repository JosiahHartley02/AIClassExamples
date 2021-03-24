#pragma once
#include "Actor.h"
#include <vector>
#include "raylib.h"
#include <deque>

class Edge;

class Node : public Actor
{
public:
	Node(int x, int y, int nodeSize, float GScore = 1);
	std::vector<Edge*> edges;
	MathLibrary::Vector2 graphPosition;
	int color = 0xFFFFFFFF;
	int size = 1;
	void draw() override;
	void update(float deltaTime) override;;
	bool visited;
	void gScore(float value) { m_gScore = value; }
	float gScore() { return m_gScore; }
	void previous(Node* node) { m_previous = node; }
	Node* previous() { return m_previous; }
private:
	float m_gScore;
	Node* m_previous;
};

