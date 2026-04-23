#pragma once
#include <vector>
#include <tge/engine.h>
class Node;
class NavMesh;
class GridPathfinder
{
	public:
		GridPathfinder() = default;
		~GridPathfinder() = default;

		std::vector<Tga::Vector2f> GetPath(std::shared_ptr<Node> aStartNode, std::shared_ptr<Node> anEndNode);
		Tga::Vector2f GetNavVertexClosestToPoint(NavMesh& aNavMesh, const Tga::Vector2f& aPoint);
		std::shared_ptr<Node> GetNodeAtPoint(NavMesh& aNavMesh, const Tga::Vector2f& aPoint);

	private:
		bool Contains(std::shared_ptr<Node> aNode, std::vector<std::shared_ptr<Node>>& aList);
		int GetDistance(std::shared_ptr<Node> firstNode, std::shared_ptr<Node> secondNode);
		int GetDistance(std::shared_ptr<Node> firstNode, Tga::Vector2f aPosition);

		void ResetCostsOfAllNodes();
};

