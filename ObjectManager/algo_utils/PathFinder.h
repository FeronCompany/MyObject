

#pragma once

#include <vector>

#include "MDArray.h"

enum PositonStatus
{
	PS_FREE = 0,	// 未遍历状态
	PS_CHECK = 1,	// 已遍历但未加入路径
	PS_CONFIRM = 2,	// 已经确认加入路径
};

struct Position2D
{
	Position2D() : x(-1), y(-1) {}
	Position2D(int px, int py) : x(px), y(py) {}
	int x;
	int y;
};

struct PositionNode
{
	PositionNode() : status(PS_FREE), access(1) {}
	Position2D pos;
	int status;
	int access;
	Position2D parent;
};

#define PositionNodeEqual(nodeA, nodeB) \
	(nodeA.pos.x == nodeB.pos.x && nodeA.pos.y == nodeB.pos.y)
#define PositionNodeUnequal(nodeA, nodeB) \
	(nodeA.pos.x != nodeB.pos.x || nodeA.pos.y != nodeB.pos.y)
#define SetParentPosition(nodeA, nodeB) \
	do { if(nodeA.parent.x == -1 && nodeA.parent.y == -1) nodeA.parent = nodeB.pos; }while(0)
#define DIRECTION_SIZE 4

class PathFinder
{
public:
	PathFinder() : map(TwoDArray<PositionNode>(1, 1)), xSize(1), ySize(1) {}
	void setStartPos(int x, int y);
	void setTargetPos(int x, int y);
	void setMapSize(int x, int y);
	void getPath(std::vector<PositionNode>& outputPath);
	TwoDArray<PositionNode>& getMap();

private:
	void initDirection();
	bool findNext(PositionNode& current, int pathSize, PositionNode& next);
	double checkPosition(PositionNode& current, int cX, int cY, int pathSize);
	void checkPath(std::vector<PositionNode>& confirmPostions, std::vector<PositionNode>& outputPath);
	void printMapDebug();

private:
	PositionNode startPostion;
	PositionNode targetPostion;
	TwoDArray<PositionNode> map;
	int xSize;
	int ySize;
	Position2D directionArray[DIRECTION_SIZE];
};
