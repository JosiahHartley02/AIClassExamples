#include "Edge.h"
#include <raylib.h>
#include "Node.h"

Edge::Edge(Node* nodeOne, Node* nodeTwo) : Actor(0,0,0,' ',0)
{
	connectedNodeOne = nodeOne;
	connectedNodeTwo = nodeTwo;
}

void Edge::draw()
{
	//Draw a line to represent each edge on the graph
	DrawLine(getWorldPosition().x * 32, getWorldPosition().y * 32,
		connectedNodeTwo->getWorldPosition().x * 32, connectedNodeTwo->getWorldPosition().y * 32,
		WHITE);
}

void Edge::update(float deltaTime)
{
	Actor::update(deltaTime);
	//Update the position to mathc the position of the first connected node
	setWorldPostion(connectedNodeOne->getWorldPosition());
}
