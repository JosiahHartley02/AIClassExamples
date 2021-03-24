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

	void Graph::dijkstra(int startX, int startY, int goalX, int goalY)
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
		Node* iterator = nullptr;

		//Create an open list
		std::deque<Node*> openList;
		//Create a closed list
		std::deque<Node*> closedList;

		//Add start to the open list
		openList.push_front(start);

		//Loop while the open list is not empty
		while (openList.size() > 0)
		{
			//Sort the items in the open list by the g score
			openList = sortList(openList);

			//Set the iterator to be the first item in the open list
			iterator = openList[0];

			//Check if the iterator is pointing to the goal node
			if (iterator == goal)
			{
				//Mark the goal as being found by changing its color
				iterator->color = ColorToInt(RED);
				//Return the new path found
				break;
				//end if statement
			}

			//Pop the first item off the open list
			openList.pop_front();

			//Add the first item to the closed list
			closedList.push_front(iterator);

			//Loop through all of the edges for the iterator
			for (int i = 0; i < iterator->edges.size(); i++)
			{
				//Create a node pointer to store the other end of the edge
				Node* nodeEdgeEnd = nullptr;

				//Check if the iterator is on the second end of the node
				if (iterator == iterator->edges[i]->connectedNodeTwo)
				{
					//Set the edge end pointer to be the first end of the node
					nodeEdgeEnd = iterator->edges[i]->connectedNodeOne;
				}
				//Otherwise if the iterator is on the first end of the node...
				else
				{
					//set the edge end pointer to be the second end of the node
					nodeEdgeEnd = iterator->edges[i]->connectedNodeTwo;
					// end if statement
				}

				//Check if node at the end of the edge is in the closed list
				if (!inList(closedList,nodeEdgeEnd))
				{
					//Create an int and set it to be the g score of the iterator plus the cost of the edge
					int costOf = iterator->gScore() + iterator->edges[i]->cost();

					//Check if the node at the end of the edge is in the open list
					if (!inList(openList, nodeEdgeEnd))
					{
						//Mark the node as visited by changing its color
						nodeEdgeEnd->visited = true;
						nodeEdgeEnd->color = ColorToInt(PURPLE);

						//Set the nodes g score to be the g score calculated earlier
						nodeEdgeEnd->gScore(costOf);

						//Set the nodes previous to be the iterator
						nodeEdgeEnd->previous(iterator);

						//Add the node to the open list
						openList.push_front(nodeEdgeEnd);
					}
					//Otherwise if the g score is less than the node at the end of the edge's g score...
					else if (costOf < nodeEdgeEnd->gScore())
					{
						//Mark the node as visited by changing its color
						nodeEdgeEnd->visited = true;
						nodeEdgeEnd->color = ColorToInt(MAGENTA);

						//Set its g score to be the g score calculated earlier
						nodeEdgeEnd->gScore(costOf);

						//Set its previous to be the current node
						nodeEdgeEnd->previous(iterator);
					}
				}
				//end if statement
			}
			//end loop
		}
		//end loop

		// Compiles the path from goal to start using an iterator which
		//	is currently the goal node, using its previous to get to the
		//		start
		std::vector<Node*> path;
		while (iterator)
		{
			path.push_back(iterator);
			iterator = iterator->previous();
		}
		//change the color of the nodes on the path to show the steps taken
		//	ignoring the start and goal nodes colors which are green and red respectively
		for (int i = 1; i < path.size() - 1; i++)
		{
			path[i]->color = ColorToInt(YELLOW);
		}
	}

//std::vector<Node*> Graph::dijkstra(int startX, int startY, int goalX, int goalY)
//{
//	Node* start = getNode(startX, startY);
//	Node* goal = getNode(goalX, goalY);
//
//	std::deque<Node*> openList;
//	std::deque<Node*> closedList;
//
//	start->openList(true);
//	openList.push_front(start);
//
//	while (!openList.empty())
//	{
//		Node* currentNode = openList.front();
//		openList.front()->openList(false);
//		openList.pop_front();
//
//		currentNode->closedList(true);
//		closedList.push_back(currentNode);
//
//		float costOf = currentNode->gScore();
//	}
//}

	void Graph::astar(int startX, int startY, int goalX, int goalY)
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
		//Create a node pointer that will act as an iterator for the graph
		Node* iterator = nullptr;
		//Create an open list
		std::deque<Node*> openList;
		//Create a closed list
		std::deque<Node*> closedList;

		//Add start to the open list
		openList.push_back(start);
		//Loop while the open list is not empty
		while (!openList.empty())
		{
			//Sort the items in the open list by the f score

			//Set the iterator to be the first item in the open list
			iterator = openList.front();
			//Check if the iterator is pointing to the goal node
			if (iterator = goal)
			{
				//Mark the goal as being found by changing its color
				goal->color = ColorToInt(RED);
				//Return the new path found
				return;
				//end if statement
			}
			//Pop the first item off the open list
			openList.pop_front();
			//Add the first item to the closed list
			closedList.push_back(iterator);
			//Loop through all of the edges for the iterator
			for (int i = 0; i < iterator->edges.size(); i++)
			{
				//Create a node pointer to store the other end of the edge
				Node* nodeEdgeEnd = nullptr;
				//Check if the iterator is on the second end of the node
				if (iterator == nodeEdgeEnd->edges[i]->connectedNodeTwo)
				{
					//Set the edge end pointer to be the first end of the node
					nodeEdgeEnd = iterator->edges[i]->connectedNodeOne;
				} //Otherwise if the iterator is on the first end of the node...
				else if (iterator == nodeEdgeEnd->edges[i]->connectedNodeOne)
				{				
					//set the edge end pointer to be the second end of the node
					nodeEdgeEnd = iterator->edges[i]->connectedNodeTwo;
				// end if statement
				}
				//Check if node at the end of the edge is in the closed list
				if (inList(closedList, nodeEdgeEnd))
				{
					//Create a float and set it to be the g score of the iterator plus the cost of the edge
					//Create a float and set it to be the h score of the node at the end of the edge
					//Create a float for the f score and set it to be the g score combined with the h score
					float fScore = 1;

					//Check if the node at the end of the edge is in the open list
					if (inList(openList, nodeEdgeEnd))
					{
						//Mark the node as visited by changing its color
						nodeEdgeEnd->color = ColorToInt(YELLOW);
						//Set the nodes g score to be the g score calculated earlier
						//Set the nodes h score to be the h score calculated earlier
						//Set the nodes f score to be the f score calculated earlier
						//Set the nodes previous to be the iterator
						nodeEdgeEnd->previous(iterator);
						//Add the node to the open list
						openList.push_back(nodeEdgeEnd);
					}
					//Otherwise if the f score is less than the node at the end of the edge's f score...
					else if (fScore < nodeEdgeEnd->gScore())
					{
						//Mark the node as visited by changing its color
						nodeEdgeEnd->color = ColorToInt(BLUE);
						//Set its g score to be the g score calculated earlier
						//Set the nodes h score to be the h score calculated earlier
						//Set its f score to be the f score calculated earlier
						//Set its previous to be the current node
						nodeEdgeEnd->previous(iterator);
					}
				}
				//end if statement
			}
			//end loop
		}
		//end loop
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

std::deque<Node*> Graph::sortList(std::deque<Node*> queue)
{
	for (int i = 0; i < queue.size(); i++)
	{
		for (int j = queue.size(); j > i; j--)
		{
			if (queue[i]->gScore() > queue[j - 1]->gScore())
			{
				Node* temp = queue[i];
				queue[i] = queue[j - 1];
				queue[j - 1] = temp;
			}
		}
	}
	return queue;
}

float Graph::inList(std::deque<Node*> list, Node* node)
{
	for (int i = 0; i < list.size(); i++)
		if (list[i] == node)
		{
			return true;
		}

	return false;
}
