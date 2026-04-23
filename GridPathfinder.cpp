#include "GridPathfinder.h"
#include "Navmesh/Node.h"
#include "Navmesh/NavMesh.h"
#include "SingeltonHandler.h"

std::vector<Tga::Vector2f> GridPathfinder::GetPath(std::shared_ptr<Node> aStartNode, std::shared_ptr<Node> anEndNode)
{
	constexpr int MAX_ALLOCATED_LIST_SIZE = 500;
	ResetCostsOfAllNodes();
	std::vector<std::shared_ptr<Node>> openList;
	std::vector< std::shared_ptr<Node>> closedList;

	openList.reserve(MAX_ALLOCATED_LIST_SIZE);
	closedList.reserve(MAX_ALLOCATED_LIST_SIZE);

	openList.push_back(aStartNode);
	std::shared_ptr<Node> currentTile;

	while (openList.size() != 0)
	{
		currentTile = openList[0];
		int removeIndex = 0;
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i] == currentTile) { continue; }
			else
			{
				if (openList[i]->GetFNodeValue() < currentTile->GetFNodeValue())
				{
					currentTile = openList[i];
					removeIndex = i;
				}
			}
		}

		closedList.push_back(currentTile);
		openList.erase(openList.begin() + removeIndex);

		if (currentTile == anEndNode)
		{
			std::vector<Tga::Vector2f> returnList;
			returnList.reserve(MAX_ALLOCATED_LIST_SIZE);
			std::shared_ptr<Node> newBackwardsTile = currentTile;
			returnList.push_back(newBackwardsTile->GetPosition());
			while (newBackwardsTile != aStartNode)
			{
				newBackwardsTile = newBackwardsTile->GetParent();
				returnList.push_back(newBackwardsTile->GetPosition());
			}
			std::reverse(returnList.begin(), returnList.end());
			return returnList;
		}
		else
		{
			for (int i = 0; i < currentTile->GetNeighbours().size(); i++)
			{
				std::shared_ptr<Node> currentNeighbour = currentTile->GetNeighbours().at(i).lock();
				if (Contains((currentNeighbour), closedList))
				{
					continue;
				}

				const int newWeight = currentTile->GetGNodeValue() + GetDistance(currentTile, currentNeighbour);
				if (newWeight < currentNeighbour->GetGNodeValue() || !Contains(currentNeighbour, openList))
				{
					currentNeighbour->SetGNodeValue(newWeight);
					currentNeighbour->SetHNodeValue(GetDistance(currentNeighbour,anEndNode));
					currentNeighbour->SetParent(currentTile);
					if (!Contains(currentNeighbour, openList))
					{
						openList.push_back(currentNeighbour);
					}
				}
			}
		}
	}

	return std::vector<Tga::Vector2f>();
}

Tga::Vector2f GridPathfinder::GetNavVertexClosestToPoint(NavMesh& aNavMesh, const Tga::Vector2f& aPoint)
{
	Tga::Vector2f closestPoint;
	float closestPointDist = FLT_MAX;
	for (int i = 0; i < aNavMesh.GetNodes().size(); i++)
	{
		std::shared_ptr<Node> curNode = aNavMesh.GetNodes().at(i);
		float dist = (curNode->GetPosition() - aPoint).Length();
		if (dist < closestPointDist)
		{
			closestPointDist = dist;
			closestPoint = curNode->GetPosition();
		}
	}

	return closestPoint;
}

std::shared_ptr<Node> GridPathfinder::GetNodeAtPoint(NavMesh& aNavMesh, const Tga::Vector2f& aPoint)
{
	for (int i = 0; i < aNavMesh.GetNodes().size(); i++)
	{
		std::shared_ptr<Node> curNode = aNavMesh.GetNodes().at(i);
		if (aNavMesh.IsTargetInsideNode(curNode, aPoint))
		{
			return curNode;
		}
	}
	return nullptr;
}

bool GridPathfinder::Contains(std::shared_ptr<Node> aNode, std::vector<std::shared_ptr<Node>>& aList)
{
	for (int i = 0; i < aList.size(); i++)
	{
		if (aList[i] == aNode)
		{
			return true;
		}
	}
	return false;
}

int GridPathfinder::GetDistance(std::shared_ptr<Node> firstNode, std::shared_ptr<Node> secondNode)
{
	//Manhattan distance.
	int distX = static_cast<int>(std::abs(firstNode->GetPosition().x - secondNode->GetPosition().x));
	int distY = static_cast<int>(std::abs(firstNode->GetPosition().y - secondNode->GetPosition().y));
	if (distX > distY)
	{
		return 14 * distY + 10 * (distX - distY);
	}
	else
	{
		return 14 * distX + 10 * (distY - distX);
	}
}

int GridPathfinder::GetDistance(std::shared_ptr<Node> firstNode, Tga::Vector2f aPosition)
{
	//Manhattan distance.
	int distX = static_cast<int>(std::abs(firstNode->GetPosition().x - aPosition.x));
	int distY = static_cast<int>(std::abs(firstNode->GetPosition().y - aPosition.y));
	if (distX > distY)
	{
		return 14 * distY + 10 * (distX - distY);
	}
	else
	{
		return 14 * distX + 10 * (distY - distX);
	}
}

void GridPathfinder::ResetCostsOfAllNodes()
{
	std::vector<std::shared_ptr<Node>> navMeshNodes = SingeltonHandler::GetInstance().GetGameWorld().GetNavMesh().lock()->GetNodes();
	for (int i = 0; i < navMeshNodes.size(); i++)
	{
		std::shared_ptr<Node> curNode = navMeshNodes[i];
		curNode->SetGNodeValue(INT_MAX);
		curNode->SetHNodeValue(0);
	}
}