#include "map.h"

void Map::init()
{
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			for (int direct = UP; direct <= RIGHT; direct++)
			{
				units[x][y].isWall[direct] = true;
			}
			units[x][y].isVisit = false;
		}
	}
}

bool Map::isInRange(int x, int y)
{
	if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
	{
		return true;
	}
	return false;
}

NearList Map::getNearList(Unit& nowUnit)
{
	NearList nearList;

	int nowX = nowUnit.x();
	int nowY = nowUnit.y();

	if (isInRange(nowX + 1, nowY) && !units[nowX + 1][nowY].isVisit)
	{
		nearList.append(Unit(nowX + 1, nowY));
	}
	if (isInRange(nowX - 1, nowY) && !units[nowX - 1][nowY].isVisit)
	{
		nearList.append(Unit(nowX - 1, nowY));
	}
	if (isInRange(nowX, nowY + 1) && !units[nowX][nowY + 1].isVisit)
	{
		nearList.append(Unit(nowX, nowY + 1));
	}
	if (isInRange(nowX, nowY - 1) && !units[nowX][nowY - 1].isVisit)
	{
		nearList.append(Unit(nowX, nowY - 1));
	}
	return nearList;
}

void Map::setVisit(Unit& unit, int& visitCount)
{
	int x = unit.x();
	int y = unit.y();

	units[x][y].isVisit = true;
	visitCount += 1;
}

bool Map::isHaveWall(Unit& nowUnit, Unit& nearUnit)
{
	int nowX = nowUnit.x();
	int nowY = nowUnit.y();
	int nearX = nearUnit.x();
	int nearY = nearUnit.y();

	if (nearX == nowX && nearY < nowY)
	{
		return units[nowX][nowY].isWall[UP];
	}
	else if (nearX == nowX && nearY > nowY)
	{
		return units[nowX][nowY].isWall[DOWN];
	}
	else if (nearX < nowX && nearY == nowY)
	{
		return units[nowX][nowY].isWall[LEFT];
	}
	else if (nearX > nowX && nearY == nowY)
	{
		return units[nowX][nowY].isWall[RIGHT];
	}
	return true;
}

void Map::removeWall(Unit& nowUnit, Unit& nearUnit)
{
	int nowX = nowUnit.x();
	int nowY = nowUnit.y();
	int nearX = nearUnit.x();
	int nearY = nearUnit.y();

	if (nearX == nowX && nearY < nowY)
	{
		units[nowX][nowY].isWall[UP] = false;
		units[nearX][nearY].isWall[DOWN] = false;
	}
	else if (nearX == nowX && nearY > nowY)
	{
		units[nowX][nowY].isWall[DOWN] = false;
		units[nearX][nearY].isWall[UP] = false;
	}
	else if (nearX < nowX && nearY == nowY)
	{
		units[nowX][nowY].isWall[LEFT] = false;
		units[nearX][nearY].isWall[RIGHT] = false;
	}
	else if (nearX > nowX && nearY == nowY)
	{
		units[nowX][nowY].isWall[RIGHT] = false;
		units[nearX][nearY].isWall[LEFT] = false;
	}
}

void Map::setLastUnit(Unit& nowUnit, Unit& nearUnit)
{
	int nowX = nowUnit.x();
	int nowY = nowUnit.y();
	int nearX = nearUnit.x();
	int nearY = nearUnit.y();

	units[nearX][nearY].stepCount = units[nowX][nowY].stepCount + 1;
	units[nearX][nearY].lastUnit = nowUnit;
}

int Map::getStepCount(Unit& unit)
{
	return units[unit.x()][unit.y()].stepCount;
}

Unit Map::getLastUnit(Unit& unit)
{
	return units[unit.x()][unit.y()].lastUnit;
}

void Map::generate()
{
	UnitStack unitStack;
	NearList nearList;
	Unit nowUnit;
	Unit nearUnit;
	int visitCount = 0;

	nowUnit.setX(rand() % ROWS);
	nowUnit.setY(rand() % COLS);
	setVisit(nowUnit, visitCount);

	while (visitCount < ROWS * COLS)
	{
		nearList = getNearList(nowUnit);

		if (!nearList.isEmpty())
		{
			nearUnit = nearList[rand() % nearList.length()];
			unitStack.push(nowUnit);
			removeWall(nowUnit, nearUnit);
			setVisit(nearUnit, visitCount);
			nowUnit = nearUnit;
		}
		else if (!unitStack.isEmpty())
		{
			nowUnit = unitStack.pop();
		}
	}
}

bool Map::isHaveWall(int x, int y, Direct direct)
{
	return units[x][y].isWall[direct];
}

WayData Map::getWayData(int initX, int initY)
{
	WayData wayData;
	UnitQueue unitQueue;
	NearList nearList;
	Unit nowUnit;
	int visitCount = 0;

	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			units[x][y].isVisit = false;
			units[x][y].stepCount = 0;
		}
	}
	nowUnit.setX(initX);
	nowUnit.setY(initY);
	setVisit(nowUnit, visitCount);
	unitQueue.enqueue(nowUnit);

	while (!unitQueue.isEmpty())
	{
		nowUnit = unitQueue.front();

		if (nowUnit.x() == ROWS - 1 && nowUnit.y() == COLS - 1)
		{
			break;
		}
		nearList = getNearList(nowUnit);

		for (int i = 0; i < nearList.length(); i++)
		{
			if (!isHaveWall(nowUnit, nearList[i]))
			{
				unitQueue.enqueue(nearList[i]);
				setLastUnit(nowUnit, nearList[i]);
				setVisit(nearList[i], visitCount);
			}
		}
		unitQueue.dequeue();
	}
	for (int stepCount = getStepCount(nowUnit); stepCount >= 0; stepCount--)
	{
		wayData.append(nowUnit);
		nowUnit = getLastUnit(nowUnit);
	}
	return wayData;
}