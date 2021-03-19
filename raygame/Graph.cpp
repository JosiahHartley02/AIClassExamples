#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "raylib.h"
#include <deque>

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
		// Get a reference to the start and end nodes
		Node* start = getNode(startX, startY);
		Node* goal = getNode(goalX, goalY);

		// If either is null, return
		if (!start || !goal)
			return;

		// Set the color to start and mark it as visited
		start->color = ColorToInt(GREEN);
		start->visited = true;

		// Set an iterator to start
		Node* currentNode = start;

		// Create a queue and add start to it
		std::deque<Node*> queue;
		queue.push_front(start);

		// So long as there is something in the queue, search for the goal
		while (!queue.empty())
		{
			// Set the iterator to the first thing in the queue and then pop it
			currentNode = queue[0];
			queue.pop_front();

			// If we've reached the goal, set its color and return
			if (currentNode == goal)
			{
				currentNode->color = ColorToInt(YELLOW);
				return;
			}

			// If we haven't reached the goal, get all neighbors
			for (int i = 0; i < currentNode->edges.size(); i++)
			{
				// Store the node at the other end of the edge
				Node* currentEdgeEnd = nullptr;

				// Set the node to be the opposite end of the edge
				if (currentNode == currentNode->edges[i]->connectedNodeTwo)
					currentEdgeEnd = currentNode->edges[i]->connectedNodeOne;
				else
					currentEdgeEnd = currentNode->edges[i]->connectedNodeTwo;

				// If the opposite node hasn't been visited, mark it and add it to the queue	
				if (!currentEdgeEnd->visited)
				{
					currentEdgeEnd->color = ColorToInt(RED);
					currentEdgeEnd->visited = true;
					queue.push_back(currentEdgeEnd);
				}
			}
		}
	}

	void Graph::dijkstrap(int startX, int startY, int goalX, int goalY)
	{
		//Create a node pointer that points to the start node
		Node* start = getNode(startX, startY);
		//Create a node pointer that points to the goal node
		Node* goal = getNode(goalX, goalY);

		//Check if the start or the goal pointer is null
		if (!start || !goal)
		{
			//return an empty list
			return;
			//end if statement
		}
		//Set the start nodes color to be green
		start->color = ColorToInt(GREEN);
		//Create a node pointer that will be act as an iterator for the graph
		Node* currentNode = start;
		//Create an open list
		std::deque<Node*> openList;
		//Create a closed list
		std::deque<Node*> closedList;
		//Add start to the open list
		openList.push_front(start);

		//Loop while the open list is not empty
		while (!openList.empty())
		{
			//Sort the items in the open list by the g score

			//Set the iterator to be the first item in the open list
			currentNode = openList.front();
			//Check if the iterator is pointing to the goal node
			if (currentNode == goal)
			{
				//Mark the goal as being found by changing its color
				goal->color = ColorToInt(YELLOW);
				//Return the new path found
				return;
				//end if statement
			}
			//Pop the first item off the open list
			openList.pop_front();
			//Add the first item to the closed list
			closedList.push_back(currentNode);
			//Loop through all of the edges for the iterator
			for (int i = 0; i < currentNode->edges.size(); i++)
			{
				//Create a node pointer to store the other end of the edge
				Node* currentEdgeEnd = nullptr;
				//Check if the iterator is on the second end of the node
				if (currentEdgeEnd == currentNode->edges[i]->connectedNodeTwo)
				{
					//Set the edge end pointer to be the first end of the node
					currentEdgeEnd = currentNode->edges[i]->connectedNodeOne;
				}
				//Otherwise if the iterator is on the first end of the node...
				else
				{
					//set the edge end pointer to be the second end of the node
					currentEdgeEnd = currentNode->edges[i]->connectedNodeTwo;
				// end if statement
				}
				//Check if node at the end of the edge is in the closed list
				if (currentEdgeEnd)
				{
					//Create a float and set it to be the g score of the iterator plus the cost of the edge
					int costOf = 1;

					//Check if the node at the end of the edge is in the open list

						//Mark the node as visited by changing its color
						//Set the nodes g score to be the g score calculated earlier
						//Set the nodes previous to be the iterator
						//Add the node to the open list

					//Otherwise if the g score is less than the node at the end of the edge's g score...

						//Mark the node as visited by changing its color
						//Set its g score to be the g score calculated earlier
						//Set its previous to be the current node

					//end if statement
				}
			//end loop
			}
			//end loop
		}
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
