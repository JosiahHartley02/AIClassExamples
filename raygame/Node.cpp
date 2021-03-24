#include "Node.h"
#include "Edge.h"
#include <raylib.h>

Node::Node(int x, int y, int nodeSize, float GScore)
{
	graphPosition.x = x;
	graphPosition.y = y;
	size = nodeSize;
	gScore(graphPosition.x + graphPosition.y);
	previous(nullptr);
}

void Node::draw()
{
	//Draw a circle that represents the node
	DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, size, GetColor(color));
	//Draw the gScore
	int size = gScore();
	char dispsize[3];
	sprintf_s(dispsize, "%d", size);
	DrawTextEx(GetFontDefault(), dispsize, { getWorldPosition().x * 32 - 2,getWorldPosition().y* 32 - 8 }, 18, 2, RED);

	//Draw all edges connected to this node
	for (int i = 0; i < edges.size(); i++)
	{
		//Checks if the node is the first connected node to prevent the edge from drawing twice
		if (edges[i]->connectedNodeOne->graphPosition == graphPosition)
			edges[i]->draw();
	}
}

void Node::update(float deltaTime)
{
	Actor::update(deltaTime);

	//Update all edges connected to this node
	for (int i = 0; i < edges.size(); i++)
	{
		//Checks if the node is the first connected node to prevent the edge from updating twice
		if (edges[i]->connectedNodeOne->graphPosition == graphPosition)
			edges[i]->update(deltaTime);
	}
}
