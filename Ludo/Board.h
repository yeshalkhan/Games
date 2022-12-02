#include <iostream>
#include"Player.h"
#include <string>
using namespace std;
#pragma once
#define r 33
#define c 130
class Board
{
private:
	Player* players;
	string** board;
	int playerCount;
public:
	Board()
	{
		//dynamic allocation
		board = new string * [r];
		for (int i = 0; i < r; i++)
			board[i] = new string[c];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				board[i][j] = " ";
			}
		}
		//Pattern for board
		for (int i = 0, j = 0; j < c; j++)
			board[i][j] = "#";
		for (int i = r - 1, j = 0; j < c; j++)
			board[i][j] = "#";
		for (int i = 0, j = 0; i < r; i++)
			board[i][j] = "#";
		for (int i = 0, j = c - 1; i < r; i++)
			board[i][j] = "#";
		for (int j = 56, i = 1; i < 13; i++)
			board[i][j] = "#";
		for (int j = 1, i = 13; j <= 56; j++)
			board[i][j] = "#";
		for (int j = 74, i = 1; i < 13; i++)
			board[i][j] = "#";
		for (int j = 74, i = 13; j < c; j++)
			board[i][j] = "#";
		for (int j = 1, i = 19; j <= 56; j++)
			board[i][j] = "#";
		for (int j = 56, i = 19; i < r; i++)
			board[i][j] = "#";
		for (int j = 74, i = 19; j < c; j++)
			board[i][j] = "#";
		for (int j = 74, i = 19; i < r; i++)
			board[i][j] = "#";
		for (int i = 14; i <= 18; i += 2)
		{
			for (int j = 11; j <= 56; j += 9)
				board[i][j] = "|";
		}
		for (int i = 14; i <= 18; i += 2)
		{
			for (int j = 74; j <= 122; j += 9)
				board[i][j] = "|";
		}
		for (int j = 57; j <= 73; j++)
		{
			for (int i = 3; i <= 30; i += 2)
				board[i][j] = "-";
		}
		for (int j = 62, i = 3; i < r - 3; i++)
			board[i][j] = "#";
		for (int j = 68, i = 3; i < r - 3; i++)
			board[i][j] = "#";
		for (int j = 68, i = 17; j <= 124; j++)
			board[i][j] = "#";
		for (int j = 68, i = 15; j <= 124; j++)
			board[i][j] = "#";
		for (int j = 7, i = 15; j <= 62; j++)
			board[i][j] = "#";
		for (int j = 7, i = 17; j <= 62; j++)
			board[i][j] = "#";
		board[1][62] = board[r - 2][62] = board[1][68] = board[r - 2][68] = board[2][62] = board[r - 3][62] = board[2][68] = board[r - 3][68] = "|";
		for (int j = 1; j <= 10; j++)
		{
			for (int i = 15; i <= 17; i += 2)
				board[i][j] = "-";
		}
		for (int j = c - 10; j <= c - 2; j++)
		{
			for (int i = 15; i <= 17; i += 2)
				board[i][j] = "-";
		}
		//To indicate HOME
		for (int i = 14; i < 19; i++)
		{
			for (int j = 57; j < 74; j++)
				board[i][j] = " ";
		}
		board[16][62] = "H"; board[16][64] = "O"; board[16][66] = "M"; board[16][68] = "E";
		//To indicate safe points
		board[14][11] = board[14][20] = board[14][110] = board[14][101] = board[18][20] = board[18][29] = board[18][119] = board[18][110] = "#";
		for (int j = 69; j < 74; j++)
			board[3][j] = board[27][j] = board[25][j] = board[5][j] = "#";
		for (int j = 57; j < 62; j++)
			board[29][j] = board[27][j] = board[5][j] = board[7][j] = "#";
		//To indicate each player's box
		for (int j = 22; j < 33; j++)
			board[5][j] = board[7][j] = board[9][j] = board[24][j] = board[26][j] = board[28][j] = "-";
		for (int j = 99; j < 110; j++)
			board[5][j] = board[7][j] = board[9][j] = board[24][j] = board[26][j] = board[28][j] = "-";
		board[6][22] = board[6][27] = board[6][32] = board[8][22] = board[8][27] = board[8][32] = board[25][99] = board[25][104] = board[25][109] = board[27][99] = board[27][104] = board[27][109] = "|";
		board[6][99] = board[6][104] = board[6][109] = board[8][99] = board[8][104] = board[8][109] = board[25][22] = board[25][27] = board[25][32] = board[27][22] = board[27][27] = board[27][32] = "|";
		board[4][25] = "Y"; board[4][26] = "E";  board[4][27] = "L"; board[4][28] = "L"; board[4][29] = "O"; board[4][30] = "W";
		board[4][103] = "B"; board[4][104] = "L";  board[4][105] = "U"; board[4][106] = "E";
		board[23][25] = "G"; board[23][26] = "R";  board[23][27] = "E"; board[23][28] = "E"; board[23][29] = "N";
		board[23][103] = "R"; board[23][104] = "E";  board[23][105] = "D";
	}
	void setPlayers(Player* playersMain)
	{
		players = playersMain;
	}
	void setPlayerCount(int n)
	{
		playerCount = n;
	}
	Player* getPlayers()
	{
		return players;
	}
	string& operator()(const int x, const int y)
	{
		return board[x][y];
	}



	void printBoard()
	{
		for (int i = 0; i < r; i++)
		{
			cout << "  ";
			for (int j = 0; j < c; j++)
			{
				if (board[i][j] == "Y1" || board[i][j] == "Y2" || board[i][j] == "Y3" || board[i][j] == "Y4")
					cout << "\u001b[33m" << board[i][j] << "\u001b[37m";
				else if (board[i][j] == "B1" || board[i][j] == "B2" || board[i][j] == "B3" || board[i][j] == "B4")
					cout << "\u001b[34m" << board[i][j] << "\u001b[37m";
				else if (board[i][j] == "R1" || board[i][j] == "R2" || board[i][j] == "R3" || board[i][j] == "R4")
					cout << "\u001b[31m" << board[i][j] << "\u001b[37m";
				else if (board[i][j] == "G1" || board[i][j] == "G2" || board[i][j] == "G3" || board[i][j] == "G4")
					cout << "\u001b[32m" << board[i][j] << "\u001b[37m";
				else if (i == 4 && (j >= 25 && j <= 30))
					cout << "\u001b[33m" << board[i][j] << "\u001b[37m";
				else if (i == 4 && (j >= 103 && j <= 106))
					cout << "\u001b[34m" << board[i][j] << "\u001b[37m";
				else if (i == 23 && (j >= 103 && j <= 105))
					cout << "\u001b[31m" << board[i][j] << "\u001b[37m";
				else if (i == 23 && (j >= 25 && j <= 29))
					cout << "\u001b[32m" << board[i][j] << "\u001b[37m";
				else
					cout << board[i][j];
			}
			cout << endl;
		}
	}
	void printPlayers()
	{
		for (int i = 0; i < 4; i++)
		{
			cout << players[i].getColor() << endl;
			for (int j = 0; j < 4; j++)
			{
				cout << players[i].getPieces()[j].getNum() << " (" << players[i].getPieces()[j].getX() << "," << players[i].getPieces()[j].getY() << ")" << endl;
			}
		}
	}


	bool checkLocation(COORD location)
	{
		if (board[location.X][location.Y] == " ")
			return true;
		else
			return false;
	}
	Piece& getPiece(COORD location)
	{
		for (int i = 0; i < playerCount; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (board[location.X][location.Y] == players[i].pieces[j].getNum())
					return  players[i].pieces[j];
			}
		}
	}
	Player& getPlayer(Piece& p)
	{
		string temp1 = p.getNum();
		for (int i = 0; i < playerCount; i++)
		{
			string temp2 = players[i].getColor();
			if (temp1[0] == temp2[0])
				return players[i];
		}
	}
	void updateBoard(int x, int y)
	{
		for (int i = 0; i < playerCount; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (players[i].pieces[j].getX() == x && players[i].pieces[j].getY() == y)
				{
					board[x][y] = players[i].pieces[j].getNum();
					board[x][y + 1] = "";
					goto here123;
				}
			}
		}
	here123:
		int a = 0;
	}


	void setSpawnAtStart()
	{
		for (int i = 0; i < playerCount; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				COORD temp = players[i].pieces[j].getSpawn();
				board[temp.X][temp.Y] = players[i].pieces[j].getNum();
				board[temp.X][temp.Y + 1] = "";
			}
		}
	}

	~Board()
	{
		if (board)
		{
			for (int i = 0; i < r; i++)
				delete[]board[i];
			delete[]board;
			board = NULL;
		}
	}
};
