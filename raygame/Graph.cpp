#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "raylib.h"

Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_width = width;
	m_height = height;
	m_nodeSpacing = nodeSpacing;

	createGraph(nodeSize, nodeSpacing);
}

void Graph::draw()
{
	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->draw();
}

void Graph::update(float deltaTime)
{
	m_nodeSpacing += RAYLIB_H::IsKeyDown((KeyboardKey)KEY_UP);
	m_nodeSpacing -= RAYLIB_H::IsKeyDown((KeyboardKey)KEY_DOWN);

	Actor::update(deltaTime);
	
	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->update(deltaTime);
}

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	if (!start || !goal)
		return;

	start->color = ColorToInt(GREEN);
}

Node* Graph::getNode(int xPos, int yPos)
{
	if(xPos < 0 || xPos > m_width || yPos < 0 || yPos > m_height)
		return nullptr;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
			return m_nodes[i];
	}

	return nullptr;
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;
	
	//Loops for the amount of nodes in the graph
	for (int i = 0; i < m_width * m_height; i++)
	{
		//Create a new node with the current graph position and size
		Node* currentNode = new Node(xPos, yPos, nodeSize);

		//Set the local offset for spacing
		MathLibrary::Vector2 nodeLocalPosition = { xPos * m_nodeSpacing, yPos * m_nodeSpacing };
		currentNode->setLocalPosition(nodeLocalPosition);

		//Add the node as a child of the grid and update the list
		addChild(currentNode);
		m_nodes.push_back(currentNode);

		//Connect the node to all nodes in range
		for (int j = 0; j < m_nodes.size(); j++)
		{
			//Find the displacement between the current node being added and the node being evaluated
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;

			//Check if the magnitude of the displacement is farther than the maximum
			if (displacement.getMagnitude() <= 1.42 && displacement.getMagnitude() > 0)
			{
				//Create a new edge that connets the two nodes
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}

		//Increase the graph position on the x
		xPos++;

		//If the position is greater than the width, reset it to 0 and increase the y
		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}
