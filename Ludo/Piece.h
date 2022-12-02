#include <iostream>
#include <string>
using namespace std;
#pragma once
class Player;
class Board;

class Piece
{
	string num;
	COORD location;
	COORD spawn;
	bool isAlive = false;
	bool isWon = false;
public:
	friend class Player;
	friend class Board;
	friend void updateBoard(Piece&, int, int);
	Piece()
	{
		num = " ";
		location.X = 0;
		location.Y = 0;
	}
	Piece(string num, int x, int y)
	{
		this->num = num;
		location.X = x;
		location.Y = y;
		spawn.X = x;
		spawn.Y = y;
	}
	void setLocation(int x, int y)
	{
		location.X = x;
		location.Y = y;
	}
	void setLocation(COORD l)
	{
		location = l;
	}
	void setNum(string num)
	{
		this->num = num;
	}
	void setX(int x)
	{
		location.X = x;
	}
	void setY(int y)
	{
		location.Y = y;
	}
	void setSpawn(int x, int y)
	{
		spawn.X = x;
		spawn.Y = y;
	}
	string getNum()
	{
		return num;
	}
	COORD getLocation()
	{
		return location;
	}
	COORD getSpawn()
	{
		return spawn;
	}
	int getX()
	{
		return location.X;
	}
	int getY()
	{
		return location.Y;
	}
	const Piece& operator=(const Piece& p)
	{
		num = p.num;
		location.X = p.location.X;
		location.Y = p.location.Y;
		spawn = p.spawn;
		return *this;
	}

};