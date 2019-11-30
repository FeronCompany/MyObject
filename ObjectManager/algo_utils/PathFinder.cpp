

#include "PathFinder.h"
#include "ComposedLog.h"

#include <cmath>

void PathFinder::setStartPos(int x, int y)
{
	startPostion.pos.x = x;
	startPostion.pos.y = y;
	startPostion.status = PS_CONFIRM;
}

void PathFinder::setTargetPos(int x, int y)
{
	targetPostion.pos.x = x;
	targetPostion.pos.y = y;
	targetPostion.status = PS_FREE;
}

void PathFinder::setMapSize(int x, int y)
{
	map.resize(x, y);
	xSize = x;
	ySize = y;
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			PositionNode& node = map(i, j);
			node.pos.x = i;
			node.pos.y = j;
			node.access = 1;
			node.status = PS_FREE;
			node.parent.x = -1;
			node.parent.y = -1;
		}
	}
}

void PathFinder::getPath(std::vector<PositionNode>& outputPath)
{
	initDirection();
	printMapDebug();

	std::vector<PositionNode> confirmPostions;
	PositionNode position = startPostion;
	confirmPostions.push_back(position);
	while (PositionNodeUnequal(position, targetPostion))
	{
		PositionNode next;
		if (findNext(position, confirmPostions.size(), next))
		{
			PositionNode& nextInMap = map(next.pos.x, next.pos.y);
			nextInMap.status = PS_CONFIRM;
			if (PositionNodeUnequal(nextInMap, startPostion))
			{
				SetParentPosition(nextInMap, position);
			}

			position = nextInMap;
			confirmPostions.push_back(position);
		}
		else
		{
			confirmPostions.pop_back();
			position = confirmPostions.back();
		}
	}
	checkPath(confirmPostions, outputPath);
}

TwoDArray<PositionNode>& PathFinder::getMap()
{
	return map;
}

void PathFinder::initDirection()
{
	// 左
	directionArray[0].x = -1;
	directionArray[0].y = 0;

	// 右
	directionArray[1].x = 1;
	directionArray[1].y = 0;

	// 上
	directionArray[2].x = 0;
	directionArray[2].y = -1;

	// 下
	directionArray[3].x = 0;
	directionArray[3].y = 1;
}

bool PathFinder::findNext(PositionNode& current, int pathSize, PositionNode& next)
{
	bool findNextSucc = false;
	double minLength = 99999999999.0;	// 各顶点的预期路径总长
	// 分别获取上下左右四个顶点
	for (int i = 0; i < DIRECTION_SIZE; ++i)
	{
		int towardX = current.pos.x + directionArray[i].x;
		int towardY = current.pos.y + directionArray[i].y;
		if (towardX >= 0 && towardX < xSize &&
			towardY >= 0 && towardY < ySize &&
			map(towardX, towardY).access != 0)
		{
			double length = checkPosition(current, towardX, towardY, pathSize);
			if (length < minLength && length > 0)
			{
				minLength = length;
				next.pos.x = towardX;
				next.pos.y = towardY;
				findNextSucc = true;
			}
		}
	}
	return findNextSucc;
}

double PathFinder::checkPosition(PositionNode& current, int cX, int cY, int pathSize)
{
	// 节点是否未被遍历
	PositionNode& posNode = map(cX, cY);
	if (posNode.status != PS_CONFIRM)
	{
		if (posNode.status == PS_FREE)
		{
			posNode.status = PS_CHECK;
			if (PositionNodeUnequal(posNode, startPostion))
			{
				SetParentPosition(posNode, current);
			}
		}

		// 计算预期剩余路径
		return pathSize + sqrt((cX - targetPostion.pos.x) * (cX - targetPostion.pos.x) +
			(cY - targetPostion.pos.y) * (cY - targetPostion.pos.y));
	}
	else
	{
		return -1;
	}
}

void PathFinder::checkPath(std::vector<PositionNode>& confirmPostions, std::vector<PositionNode>& outputPath)
{
	PositionNode position = confirmPostions.back();
	outputPath.push_back(position);
	while (PositionNodeUnequal(position, startPostion))
	{
		Position2D& parent2D = position.parent;
		if (parent2D.x == -1 || parent2D.y == -1)
		{
			outputPath.clear();
			return;
		}
		position = map(parent2D.x, parent2D.y);
		outputPath.push_back(position);
	}
}

void PathFinder::printMapDebug()
{
	for (int j = 0; j < xSize; ++j)
	{
		for (int i = 0; i < ySize; ++i)
		{
			APPEND_LOG("%d ", map(i, j).access);
		}
		APPEND_LOG("\n");
	}
}
