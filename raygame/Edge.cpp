#include "Edge.h"
#include <raylib.h>
#include "Node.h"

Edge::Edge(Node* nodeOne, Node* nodeTwo) : Actor(0,0,0,' ',0)
{
	connectedNodeOne = nodeOne;
	connectedNodeTwo = nodeTwo;
	updateCost();
}

void Edge::updateCost()
{
	//m_cost = (connectedNodeTwo->graphPosition - connectedNodeOne->graphPosition).getMagnitude();
	m_cost = rand() % 10 + 1;
}

void Edge::draw()
{
	int size = cost();
	char dispsize[3];
	sprintf_s(dispsize, "%d", size);
	//Draw a line to represent each edge on the graph
	DrawLine(getWorldPosition().x * 32, getWorldPosition().y * 32,
		connectedNodeTwo->getWorldPosition().x * 32, connectedNodeTwo->getWorldPosition().y * 32,
		GetColor(connectedNodeTwo->color));
	DrawText(dispsize, (getWorldPosition().x +
		connectedNodeTwo->getWorldPosition().x) / 2 * 32, (getWorldPosition().y +
			connectedNodeTwo->getWorldPosition().y) / 2 * 32, 16, PURPLE);
}

void Edge::update(float deltaTime)
{
	Actor::update(deltaTime);
	//Update the position to mathc the position of the first connected node
	setWorldPostion(connectedNodeOne->getWorldPosition());
}
