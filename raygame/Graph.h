#pragma once
#include "Actor.h"
#include <vector>
#include <deque>

class Node;
class Graph : public Actor
{
public:
	Graph(int width, int height, int nodeSize, int nodeSpacing);
	void draw() override;
	void update(float deltaTime) override;

	void BFS(int startX, int startY, int goalX, int goalY);

	std::vector<Node*> dijkstra(int startX, int startY, int goalX, int goalY);

	void astar(int startX, int startY, int goalX, int goalY);

	Node* getNode(int xPos, int yPos);
private:
	void createGraph(int nodeSize, int nodeSpacing);
	std::deque<Node*> sortQueue(std::deque<Node*> queue);
private:
	int m_height;
	int m_width;
	int m_nodeSpacing;
	std::vector<Node*> m_nodes;
};

