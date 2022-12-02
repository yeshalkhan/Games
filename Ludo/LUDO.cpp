#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "Board.h"
#include "Player.h"
#include "Piece.h"

#define r 33
#define c 130
using namespace std;
Board b;

bool checkLocation(COORD location)
{
	if (b(location.X, location.Y) == " ")
		return true;
	else
		return false;
}

Piece& getPiece(COORD location)
{
	return b.getPiece(location);
}

Player& getPlayer(Piece& p)
{
	return b.getPlayer(p);
}

void updateBoard(Piece& p, int x, int y)
{
	b(x, y) = " ";
	b(x, y + 1) = " ";
	b(p.location.X, p.location.Y) = p.getNum();
	b(p.location.X, p.location.Y + 1) = "";
}

void updateBoard(int x, int y)
{
	b.updateBoard(x, y);
}

void gotoxy(const short int x, const short int y)
{
	COORD location = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location);
}

int winCount = 0;

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);   //to open the console screen in full size 
	cout << "\u001b[36m";
	cout << "\n\t\t\t\t\t-------------------------------";
	cout << endl << "\t\t\t\t\t\tWELCOME TO LUDO++" << endl;
	cout << "\t\t\t\t\t-------------------------------\n\n";
	cout << endl << "   RULES: " << endl << endl;
	cout << "\u001b[37m";
	cout << " \tEach player has 4 pieces.\n\tThe player to send all of his pieces HOME will win.\n\tPlayer can't enter his HOME lane without killing at least one piece.\n\tA player can have a JOTA of 2 or more pieces but those pieces can still be killed." << endl;

	cout << "\u001b[36m";
	cout << "\n\n  Enter how many players will play the game (2 or 4) : ";
	cout << "\u001b[37m";

	string color1[4] = { "YELLOW COLOR","BLUE COLOR","GREEN COLOR","RED COLOR" };
	string color2[2] = { "YELLOW COLOR","RED COLOR" };
	int playerCount = 2;
here:
	while (!(cin >> playerCount))
	{
		// Explain error
		cout << "ERROR: a number must be entered: ";
		// Clear input stream
		cin.clear();
		// Discard previous input
		cin.ignore(1000, '\n');
	}
	cout << endl;
	cin.ignore();
	if (playerCount == 2)
	{
		b.setPlayerCount(2);
		Player players[2];
		string name;
		for (int i = 0; i < 2; i++)
		{
			if (color2[i] == "YELLOW COLOR") cout << "\u001b[33m";
			else if (color2[i] == "RED COLOR") cout << "\u001b[31m";
			cout << "  " << color2[i] << endl;
			cout << "\u001b[37m";
			cout << "\t Enter Name of Player: ";
			getline(cin, name);
			while (name == "")
			{
				cout << "ERROR: a name must be entered: ";
				getline(cin, name);
			}
			players[i].setName(name);
			cout << endl;
		}
		cout << endl;

		players[0].setColor("Yellow");
		players[1].setColor("Red");

		Piece pieces1[4]{ {"Y1",6,24},{"Y2",6,29},{"Y3",8,24},{"Y4",8,29} };
		players[0].setPieces(pieces1);
		Piece pieces2[4]{ {"R1",25,101},{"R2",25,106},{"R3",27,101},{"R4",27,106} };
		players[1].setPieces(pieces2);




		players[0].setDefaultLocation(14, 15);		players[0].setWinningLocation(16, 58);
		players[1].setDefaultLocation(18, 114);		players[1].setWinningLocation(16, 71);


		b.setPlayers(players);
		b.setSpawnAtStart();

		cout << "\u001b[36m";
		cout << "  Press any key to start the game..." << endl;
		cout << "\u001b[37m";
		_getch();
		while (Player::getWinCount() != 1)
		{
			for (int i = 0; i < 2; i++)
			{
				system("CLS");
				cout << endl << endl;
				b.printBoard();
				players[i].turn();
				_getch();
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (players[i].getPosition() == 0)
				players[i].setPosition(2);
		}
		system("CLS");
		cout << "\u001b[36m";
		cout << "\n\t\t\t-----------" << endl;
		cout << "\t\t\t  RESULTS" << endl;
		cout << "\t\t\t-----------" << endl;
		cout << "\u001b[37m";
		cout << endl << endl;
		for (int i = 0; i < 2; i++)
		{
			if (players[i].getposition() == 1)
				cout << "\u001b[36m" << "\twinner : " << "\u001b[37m" << players[i].getname() << endl;
			else if (players[i].getposition() == 2)
				cout << "\u001b[36m" << "\tloser : " << "\u001b[37m" << players[i].getname() << endl;
		}
		
				
		
	}
	else if (playerCount == 4)
	{
		b.setPlayerCount(playerCount);
		Player players[4];
		string name;
		for (int i = 0; i < 4; i++)
		{
	
			if (color1[i] == "YELLOW COLOR") cout << "\u001b[33m";
			else if (color1[i] == "RED COLOR") cout << "\u001b[31m";
			else if (color1[i] == "GREEN COLOR") cout << "\u001b[32m";
			else if (color1[i] == "BLUE COLOR") cout << "\u001b[34m";
			cout << "  " << color1[i] << endl;
			cout << "\u001b[37m";
			cout << "\tEnter Name of Player: ";
			getline(cin, name);
			while (name == "")
			{
				cout << "ERROR: a name must be entered: ";
				getline(cin, name);
			}
			players[i].setName(name);
			cout << endl;
		}
		cout << endl;

		players[0].setColor("Yellow");
		players[1].setColor("Blue");
		players[2].setColor("Green");
		players[3].setColor("Red");

		Piece pieces1[4] = { {"Y1",6,24},{"Y2",6,29},{"Y3",8,24},{"Y4",8,29} };
		players[0].setPieces(pieces1);
		Piece pieces2[4]{ {"B1",6,101},{"B2",6,106},{"B3",8,101},{"B4",8,106} };
		players[1].setPieces(pieces2);
		Piece pieces3[4]{ {"G1",25,24},{"G2",25,29},{"G3",27,24},{"G4",27,29} };
		players[2].setPieces(pieces3);
		Piece pieces4[4]{ {"R1",25,101},{"R2",25,106},{"R3",27,101},{"R4",27,106} };
		players[3].setPieces(pieces4);


		players[0].setDefaultLocation(14, 15);		players[0].setWinningLocation(16, 58);
		players[1].setDefaultLocation(4, 70);		players[1].setWinningLocation(14, 64);
		players[2].setDefaultLocation(28, 58);		players[2].setWinningLocation(18, 64);
		players[3].setDefaultLocation(18, 114);		players[3].setWinningLocation(16, 71);


		b.setPlayers(players);
		b.setSpawnAtStart();

		cout << "\u001b[36m";
		cout << "  Press any key to start the game..." << endl;
		cout << "\u001b[37m";
		_getch();
		while (Player::getWinCount() != 3)
		{
			for (int i = 0; i < 4; i++)
			{
				system("CLS");
				cout << endl << endl;
				b.printBoard();
				players[i].turn();
				_getch();
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (players[i].getPosition() == 0)
				players[i].setPosition(4);
		}
		system("CLS");
		cout << "\u001b[36m";
		cout << "\n\t\t\t-----------" << endl;
		cout << "\t\t\t  RESULTS" << endl;
		cout << "\t\t\t-----------" << endl;
		cout << "\u001b[37m";
		cout << endl << endl;
		for (int i = 0; i < 4; i++)
		{
			if (players[i].getPosition() == 1)
				cout << "\u001b[36m" << "\tWINNER : " << "\u001b[37m" << players[i].getName() << endl;
			else if (players[i].getPosition() == 2)
				cout << "\u001b[36m" << "\tRUNNER UP : " << "\u001b[37m" << players[i].getName() << endl;
			else if (players[i].getPosition() == 3)
				cout << "\u001b[36m" << "\t2ND RUNNER UP : " << "\u001b[37m" << players[i].getName() << endl;
			else if (players[i].getPosition() == 4)
				cout << "\u001b[36m" << "\tLOSER : " << "\u001b[37m" << players[i].getName() << endl;
		}

	}
	else
	{
		cout << "Enter Valid Choice : ";
		goto here;
	}




}



