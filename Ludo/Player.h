#include <iostream>
#include "Piece.h"
#include <string>
#include <windows.h>
#include <conio.h>
#pragma once
bool checkLocation(COORD);
void updateBoard(Piece&, int, int);
void updateBoard(int, int);
Piece& getPiece(COORD);
Player& getPlayer(Piece&);
void gotoxy(const short int x, const short int y);

int seed = time(0);
using namespace std;
#pragma once
class Player
{
	string name;
	string color;
	Piece* pieces;
	int count; //no of pieces available
	int score; 
	int position;
	int wonPieces;
	COORD defaultLocation;
	COORD winningLocation;
	bool isInGame = true;
	static int winCount;
public:
	friend class Board;
	Player()
	{
		color = name = " ";
		wonPieces = position = count = score = 0;
		score = 1;
		/*wonPieces = 3;
		count = 4;*/

	}
	Player(string name, string color, Piece pieces[]) :count(0), score(0)
	{

		this->color = color;
		this->name = name;
		for (int i = 0; i < 4; i++)
		{
			this->pieces[i] = pieces[i];
		}
	}
	int getCount()

	{
		return count;
	}
	int getWonPieces()
	{
		return wonPieces;
	}
	void setPosition(int p)
	{
		position = p;
	}
	int getPosition()
	{
		return position;
	}
	void setDefaultLocation(int x, int y)
	{
		defaultLocation.X = x;
		defaultLocation.Y = y;
	}
	void setWinningLocation(int x, int y)
	{
		winningLocation.X = x;
		winningLocation.Y = y;
	}
	static int getWinCount()
	{
		return winCount;
	}
	COORD getWinningLocation()
	{
		return winningLocation;
	}
	int rollDice(int x, int y)
	{
		for (int i = 1; i < 35; i++)
		{
			gotoxy(145, i);
			cout << "|  " << endl;
		}
		gotoxy(x, y);  cout << " Roll the dice! " << endl;
		gotoxy(x + 15, y);
		_getch();
		int a[12] = { 1,2,3,4,5,6,1,2,3,4,5,6 };
		srand(seed);
		seed = seed + time(0);
		int dice = a[rand() % 12];
		gotoxy(x + 4, y + 2); 
		cout << " ---------" << endl;
		if (dice == 1)
		{
			gotoxy(x + 4, y + 3); cout << " |       |" << endl;
			gotoxy(x + 4, y + 4); cout << " |   *   |" << endl;
			gotoxy(x + 4, y + 5); cout << " |       |" << endl;
		}
		else if (dice == 2)
		{
			gotoxy(x + 4, y + 3); cout << " |     * |" << endl;
			gotoxy(x + 4, y + 4); cout << " |       |" << endl;
			gotoxy(x + 4, y + 5); cout << " | *     |" << endl;
		}
		else if (dice == 3)
		{
			gotoxy(x + 4, y + 3); cout << " |     * |" << endl;
			gotoxy(x + 4, y + 4); cout << " |   *   |" << endl;
			gotoxy(x + 4, y + 5); cout << " | *     |" << endl;
		}
		else if (dice == 4)
		{
			gotoxy(x + 4, y + 3); cout << " | *   * |" << endl;
			gotoxy(x + 4, y + 4); cout << " |       |" << endl;
			gotoxy(x + 4, y + 5); cout << " | *   * |" << endl;
		}
		else if (dice == 5)
		{
			gotoxy(x + 4, y + 3); cout << " | *   * |" << endl;
			gotoxy(x + 4, y + 4); cout << " |   *   |" << endl;
			gotoxy(x + 4, y + 5); cout << " | *   * |" << endl;
		}
		else if (dice == 6)
		{
			gotoxy(x + 4, y + 3); cout << " | *   * |" << endl;
			gotoxy(x + 4, y + 4); cout << " | *   * |" << endl;
			gotoxy(x + 4, y + 5); cout << " | *   * |" << endl;
		}
		gotoxy(x + 4, y + 6); cout << " ---------" << endl;
		return dice;
	}
	void kill(Piece& p1, Piece& p2)
	{
		getPlayer(p2).count--;
		p2.setLocation(p2.getSpawn());
		updateBoard(p2, p1.getX(), p1.getY());
		score++;
		p2.isAlive = false;
	}
	void move(Piece& p, int n)
	{
		short int& x = p.location.X;
		short int& y = p.location.Y;
		int initialX = x;
		int initialY = y;
		for (int i = 0; i < n; i++)
		{
			if (color == "Yellow" && x == 16 && (y >= 6 && y <= 51) && score > 0) // winning rows & coloumns
			{
				if (((n * 9) + y > 60) && i == 0)
					break;
				if (y == 51)
					y = y + 7;
				else
					y = y + 9;
			}
			else if (color == "Blue" && y == 64 && (x >= 2 && x <= 12) && score > 0)
			{
				if (((n * 2) + x > 14) && i == 0)
					break;
				x = x + 2;
			}
			else if (color == "Red" && x == 16 && (y <= 123 && y >= 78) && score > 0)
			{
				if (((y - (n * 9)) < 69) && i == 0)
					break;
				if (y == 78)
					y = y - 7;
				else
					y = y - 9;
			}
			else if (color == "Green" && y == 64 && (x <= 30 && x >= 20) && score > 0)
			{
				if (((x - (n * 2)) < 16) && i == 0)
					break;
				x = x - 2;
			}

			if (x == 14 && y == 51)		//4 corners
			{
				p.setLocation(12, 58);
				continue;
			}
			else if (x == 12 && y == 70)
			{
				p.setLocation(14, 78);
				continue;
			}
			else if (x == 18 && y == 78)
			{
				p.setLocation(20, 70);
				continue;
			}
			else if (x == 20 && y == 58)
			{
				p.setLocation(18, 51);
				continue;
			}

			if (x == 14 && ((y > 0 && y <= 45) || (y >= 78 && y <= 116)))		//2nd row
				y = y + 9;
			else if (y == 58 && ((x >= 4 && x <= 12) || (x >= 20 && x < 32)))	//2nd coloumn	
				x = x - 2;
			else if (x == 2 && (y >= 58 && y <= 66))							//1st Row
				y = y + 6;
			else if (y == 70 && ((x >= 2 && x <= 10) || (x >= 20 && x <= 28)))	//3rd coloumn
				x = x + 2;
			else if (y == 123 && (x >= 14 && x <= 16))							//4th coloumn
				x = x + 2;
			else if (x == 18 && ((y >= 83 && y <= 123) || (y <= 51 && y >= 14)))	//3rd row
				y = y - 9;
			else if (x == 30 && (y <= 70 && y >= 64))							//4th row
				y = y - 6;
			else if (y == 6 && (x <= 18 && x >= 16))							//1st coloumn
				x = x - 2;
		}
		if (checkLocation(p.location))
			updateBoard(p, initialX, initialY);
		else
		{
			Piece& p2 = getPiece(p.location);
			string temp1 = p.getNum();
			string temp2 = p2.getNum();
			if ((x == 14 && y == 15) || (x == 16 && y == 58) || (x == 4 && y == 70) || (x == 14 && y == 105) || (x == 18 && y == 114) || (x == 26 && y == 70) || (x == 28 && y == 58) || (x == 18 && y == 24))
			{
				updateBoard(p, initialX, initialY);
			}
			else if (temp1[0] == temp2[0])
				updateBoard(p, initialX, initialY);
			else
			{
				kill(p, p2);
				updateBoard(p, initialX, initialY);
			}
		}
		COORD initialLocation = { initialX,initialY };
		if (checkLocation(initialLocation))
			updateBoard(initialX, initialY);
		if (p.getX() == winningLocation.X && p.getY() == winningLocation.Y)
		{
			p.isWon = true;
			wonPieces++;
		}
	}
	void setName(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return name;
	}
	void setColor(string color)
	{
		this->color = color;
	}
	string getColor()
	{
		return color;
	}
	void setPieces(Piece* piecesMain)
	{
		pieces = piecesMain;
	}
	Piece* getPieces()
	{
		return pieces;
	}
	void turn()
	{
		if (!(isInGame))  //if player has already won i.e., sent all his pieces HOME
		{
			return;
		}
		else
		{
			string default_console = "\033[37m";
			string Color;
			if (color == "Yellow") Color = "\033[33m";
			else if (color == "Green") Color = "\033[32m";
			else if (color == "Blue") Color = "\033[34m";
			else if (color == "Red") Color = "\033[31m";
			cout << "\n " << Color << name << " (" << color << ")" << "'s turn : " << endl;
			cout << default_console << endl;
			int dice = rollDice(147, 2);
			int bonus, bonus2;
			bool secondSix = false;     //to indicate 2 consecutive SIXES 
			if (count == 0 && dice != 6)   //if player has no unlocked pieces, he needs a SIX to continue
			{
				gotoxy(0, 37);
				cout << "You have no available pieces" << endl;
				return;
			}
			else if (count == wonPieces && dice != 6)
			{
				gotoxy(0, 37);
				cout << "You have no available pieces" << endl;
				return;
			}
			else if (dice == 6)
			{
				gotoxy(147, 10); cout << "   BONUS TURN! ";   //Extra turn on getting a SIX				
				bonus = rollDice(147, 11);
				if (bonus == 6)
				{
					secondSix = true;
					gotoxy(147, 19); cout << "   ANOTHER BONUS TURN! ";
					bonus2 = rollDice(147, 20);
					if (bonus2 == 6)  //Triple 6 in a row discards the player's turn
					{
						gotoxy(147, 28); cout << "   OOPS! Your turn's been discarded" << endl;
						return;
					}
				}
				gotoxy(0, 37);
				if (count == 0 || count == wonPieces)   //if there are no unlocked pieces
				{

					unlockPiece();  //unlocking 1st piece
					if (!(secondSix))
					{
						Piece* p;
						p = NULL;
						for (int i = 0; i < 4; i++)
						{
							if (pieces[i].isAlive)
								p = &pieces[i];
						}
						move(*p, bonus);
					}
					else  //if player had 2 SIXES
					{
						int choice;
						cout << "Do you want to move a piece (PRESS 0) or unlock a piece (PRESS 1) : ";
						while (!(cin >> choice))
						{
							// Explain error
							cout << "ERROR: a number must be entered: ";
							// Clear input stream
							cin.clear();
							// Discard previous input
							cin.ignore(132, '\n');
						}
						while (choice != 0 && choice != 1)   //input validation
						{
							cout << "Enter valid choice...!" << endl;
							while (!(cin >> choice))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
						}
						if (choice == 0)  //Player wants to move piece
						{
							int choice2;
							cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus2 << " (PRESS 2) ? ";
							while (!(cin >> choice2))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
							while (choice2 != 0 && choice2 != 1)   //input validation
							{
								cout << "Enter valid choice...!" << endl;
								while (!(cin >> choice2))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
							}
							//one SIX was used in unlocking 1st piece so now player has one SIX & one BONUS to move
							if (choice2 == 1)   //1st moving SIX
							{
								Piece* p;
								p = NULL;
								for (int i = 0; i < 4; i++)
								{
									if (pieces[i].isAlive)
										p = &pieces[i];
								}
								move(*p, bonus);
								move(*p, bonus2);
							}
							else   //1st moving BONUS number
							{
								Piece* p;
								p = NULL;
								for (int i = 0; i < 4; i++)
								{
									if (pieces[i].isAlive)
										p = &pieces[i];
								}
								move(*p, bonus2);
								move(*p, bonus);
							}
						}
						else   //Player wants to unlock Piece
						{
							unlockPiece();   //unlocking the next piece in turn
							//one SIX was used in unlocking 1st piece & one in unlocking 2nd piece so player has only BONUS to move
							cout << "Whiich piece do you want to move with the " << bonus2 << " : ";
							decidePiece(bonus2);   //Now player has 2 available pieces so he has to decide
							//which one to move with the number stored in bonus2 
						}
					}
				}
				else if (count == 4)  //if all 4 pieces are available
				{
					if (!(secondSix))   //if player had only one SIX
					{
						int choice2;
						cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus << " (PRESS 2) ? ";
						while (!(cin >> choice2))
						{
							// Explain error
							cout << "ERROR: a number must be entered: ";
							// Clear input stream
							cin.clear();
							// Discard previous input
							cin.ignore(132, '\n');
						}
						while (choice2 != 0 && choice2 != 1)   //input validation
						{
							cout << "Enter valid choice...!" << endl;
							while (!(cin >> choice2))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
						}
						//Player has one SIX & one BONUS to move
						if (choice2 == 1)  //moving SIX then BONUS
						{
							cout << "Which piece do you want to move with the 6 : ";
							decidePiece(dice);
							cout << "Which piece do you want to move with the " << bonus << " : ";
							decidePiece(bonus);
						}
						else   //moving BONUS then SIX
						{
							cout << "Which piece do you want to move with the " << bonus << " : ";
							decidePiece(bonus);
							cout << "Which piece do you want to move with the 6 : ";
							decidePiece(dice);
						}
					}
					else  //if player had two SIXES
					{
						int choice2;
						cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus2 << " (PRESS 2) ? ";
						while (!(cin >> choice2))
						{
							// Explain error
							cout << "ERROR: a number must be entered: ";
							// Clear input stream
							cin.clear();
							// Discard previous input
							cin.ignore(132, '\n');
						}
						while (choice2 != 1 && choice2 != 2)  //input validation
						{
							cout << "Enter valid choice...!" << endl;
							while (!(cin >> choice2))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
						}
						//Player has 2 SIXES and one BONUS to move
						if (choice2 == 1)  //1st moving SIX or SIX's then BONUS
						{
							cout << "Which piece do you want to move with the 6 : ";   //moving SIX # 1
							decidePiece(dice);
							int choice3;
							cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus2 << " (PRESS 2) ? ";
							while (!(cin >> choice3))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
							while (choice3 != 1 && choice3 != 2)  //input validation
							{
								cout << "Enter valid choice...!" << endl;
								while (!(cin >> choice3))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
							}
							//now player has one SIX & one BONUS to move
							if (choice3 == 1)  //moving SIX # 2 then BONUS
							{
								cout << "Which piece do you want to move with the 6 : ";
								decidePiece(bonus);
								cout << "Which piece do you want to move with the " << bonus2 << " : ";
								decidePiece(bonus2);
							}
							else  //moving BONUS then SIX # 2
							{
								cout << "Which piece do you want to move with the " << bonus2 << " : ";
								decidePiece(bonus2);
								cout << "Which piece do you want to move with the 6 : ";
								decidePiece(bonus);
							}
						}
						else  //1st moving BONUS then SIXES
						{
							cout << "Which piece do you want to move with the " << bonus2 << " : ";
							decidePiece(bonus2);
							cout << "Which piece do you want to move with the 6 : ";
							decidePiece(dice);
							cout << "Which piece do you want to move with the 6 : ";
							decidePiece(bonus);
						}
					}
				}
				else if (count == 1 || count == 2 || count == 3)   //if player has more than one pieces available
				{
					int choice;
					cout << "Do you want to move a piece (PRESS 0) or unlock a piece (PRESS 1) : ";
					while (!(cin >> choice))
					{
						// Explain error
						cout << "ERROR: a number must be entered: ";
						// Clear input stream
						cin.clear();
						// Discard previous input
						cin.ignore(132, '\n');
					}
					while (choice != 0 && choice != 1)  //input validation
					{
						cout << "Enter valid choice...!" << endl;
						while (!(cin >> choice))
						{
							// Explain error
							cout << "ERROR: a number must be entered: ";
							// Clear input stream
							cin.clear();
							// Discard previous input
							cin.ignore(132, '\n');
						}
					}
					if (choice == 0)  //Player wants to move a piece
					{
						if (!(secondSix))   //if player had only one SIX
						{
							int choice2;
							cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus << " (PRESS 2) ? ";
							while (!(cin >> choice2))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
							while (choice2 != 1 && choice2 != 2)  //input validation
							{
								cout << "Enter valid choice...!" << endl;
								while (!(cin >> choice2))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
							}
							//Player has one SIX & one BONUS to move
							if (choice2 == 1)  //moving SIX then BONUS
							{
								if (count == 1)
								{
									for (int i = 0; i < 4; i++)
									{
										if (pieces[i].isAlive)
										{
											move(pieces[i], dice);
											move(pieces[i], bonus);
											break;
										}
									}
								}
								else
								{
									cout << "Which piece do you want to move with the 6 : ";
									decidePiece(dice);
									cout << "Which piece do you want to move with the " << bonus << " : ";
									decidePiece(bonus);
								}
							}
							else   //moving BONUS then SIX
							{
								if (count == 1)
								{
									for (int i = 0; i < 4; i++)
									{
										if (pieces[i].isAlive)
										{
											move(pieces[i], bonus);
											move(pieces[i], dice);
											break;
										}
									}
								}
								else
								{
									cout << "Which piece do you want to move with the " << bonus << " : ";
									decidePiece(bonus);
									cout << "Which piece do you want to move with the 6 : ";
									decidePiece(dice);
								}
							}
						}
						else  //if player had 2 SIXES
						{
							int choice2, choice3;
							cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus2 << " (PRESS 2) ? ";
							while (!(cin >> choice2))
							{
								// Explain error
								cout << "ERROR: a number must be entered: ";
								// Clear input stream
								cin.clear();
								// Discard previous input
								cin.ignore(132, '\n');
							}
							while (choice2 != 1 && choice2 != 2)  //input validation
							{
								cout << "Enter valid choice...!" << endl;
								while (!(cin >> choice2))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
							}
							//Player has 2 SIXES and one BONUS to move
							if (choice2 == 1)  //1st moving SIX or SIX's then BONUS
							{
								if (count != 1)
								{
									cout << "Which piece do you want to move with the 6 : ";   //moving SIX # 1
									decidePiece(dice);
								}
								cout << "What do you want to move next: 6 (PRESS 1) or " << bonus2 << " (PRESS 2) ? ";
								while (!(cin >> choice3))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
								while (choice3 != 1 && choice3 != 2)  //input validation
								{
									cout << "Enter valid choice...!" << endl;
									while (!(cin >> choice3))
									{
										// Explain error
										cout << "ERROR: a number must be entered: ";
										// Clear input stream
										cin.clear();
										// Discard previous input
										cin.ignore(132, '\n');
									}
								}
								//now player has one SIX & one BONUS to move
								if (choice3 == 1)  //moving SIX # 2 then BONUS
								{
									if (count == 1)
									{
										for (int i = 0; i < 4; i++)
										{
											if (pieces[i].isAlive)
											{
												move(pieces[i], dice);
												move(pieces[i], bonus);
												move(pieces[i], bonus2);
												break;
											}
										}
									}
									else
									{
										cout << "Which piece do you want to move with the 6 : ";
										decidePiece(bonus);
										cout << "Which piece do you want to move with the " << bonus2 << " : ";
										decidePiece(bonus2);
									}
								}
								else  //moving BONUS then SIX # 2
								{
									if (count == 1)
									{
										for (int i = 0; i < 4; i++)
										{
											if (pieces[i].isAlive)
											{
												move(pieces[i], dice);
												move(pieces[i], bonus2);
												move(pieces[i], bonus);
												break;
											}
										}
									}
									else
									{
										cout << "Which piece do you want to move with the " << bonus2 << " : ";
										decidePiece(bonus2);
										cout << "Which piece do you want to move with the 6 : ";
										decidePiece(bonus);
									}
								}
							}
							else  //1st moving BONUS then SIXES
							{
								if (count == 1)
								{
									for (int i = 0; i < 4; i++)
									{
										if (pieces[i].isAlive)
										{
											move(pieces[i], bonus2);
											move(pieces[i], dice);
											move(pieces[i], bonus);
											break;
										}
									}
								}
								else
								{
									cout << "Which piece do you want to move with the " << bonus2 << " : ";
									decidePiece(bonus2);
									cout << "Which piece do you want to move with the 6 : ";
									decidePiece(dice);
									cout << "Which piece do you want to move with the 6 : ";
									decidePiece(bonus);
								}
							}
						}
					}
					else   //Player wants to unlock a piece
					{
						unlockPiece();
						if (!(secondSix))  //if player had only one SIX
						{
							//one SIX was used in unlocking now player has only BONUS to move
							if (count == 1)
							{
								for (int i = 0; i < 4; i++)
								{
									if (pieces[i].isAlive)
									{
										move(pieces[i], bonus);
										break;
									}
								}
							}
							else
							{
								cout << "Which piece do you want to move with the " << bonus << " : ";
								decidePiece(bonus);
							}
						}
						else //if player had two SIXES
						{
							int choice2;
							int choice3 = -1;
							//one SIX was used in unlocking now player has one SIX & one BONUS left
							if (count != 4)  //if all four pieces are unlocked then another unlocking option won't be provided
							{
								cout << "Do you want to move a piece (PRESS 0) or unlock a piece (PRESS 1) : ";
								while (!(cin >> choice3))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
								while (choice3 != 0 && choice3 != 1)  //input validation
								{
									cout << "Enter valid choice...!" << endl;
									while (!(cin >> choice3))
									{
										// Explain error
										cout << "ERROR: a number must be entered: ";
										// Clear input stream
										cin.clear();
										// Discard previous input
										cin.ignore(132, '\n');
									}
								}
							}
							if (choice3 == 1 && count != 4)   //Player wants to unlock a piece
							{
								unlockPiece();
								//one more SIX is used for unlocking now player has only BONUS to move
								if (count == 1)
								{
									for (int i = 0; i < 4; i++)
									{
										if (pieces[i].isAlive)
										{
											move(pieces[i], bonus);
											break;
										}
									}
								}
								else
								{
									cout << "Which piece do you want to move with the " << bonus2 << ": ";
									decidePiece(bonus2);
								}
							}
							if (count <= 4 && choice3 == 0)  //Player wants to move a piece
							{
								cout << "What do you want to move 1st: 6 (PRESS 1) or " << bonus2 << " (PRESS 2) ? ";
								while (!(cin >> choice2))
								{
									// Explain error
									cout << "ERROR: a number must be entered: ";
									// Clear input stream
									cin.clear();
									// Discard previous input
									cin.ignore(132, '\n');
								}
								while (choice2 != 1 && choice2 != 2)  //input validation
								{
									
									cout << "Enter valid choice...!" << endl;
									while (!(cin >> choice2))
									{
										// Explain error
										cout << "ERROR: a number must be entered: ";
										// Clear input stream
										cin.clear();
										// Discard previous input
										cin.ignore(132, '\n');
									}

								}
								//Player has one SIX & one BONUS to move
								if (choice2 == 1)  //moving SIX then BONUS
								{
									if (count == 1)
									{
										for (int i = 0; i < 4; i++)
										{
											if (pieces[i].isAlive)
											{
												move(pieces[i], bonus);
												move(pieces[i], bonus2);
												break;
											}
										}
									}
									else
									{
										cout << "Which piece do you want to move with the 6 : ";
										decidePiece(bonus);
										cout << "Which piece do you want to move with the " << bonus2 << " : ";
										decidePiece(bonus2);
									}
								}
								else   //moving BONUS then SIX
								{
									if (count == 1)
									{
										for (int i = 0; i < 4; i++)
										{
											if (pieces[i].isAlive)
											{
												move(pieces[i], bonus2);
												move(pieces[i], bonus);
												break;
											}
										}
									}
									else
									{
										cout << "Which piece do you want to move with the " << bonus2 << " : ";
										decidePiece(bonus2);
										cout << "Which piece do you want to move with the 6 : ";
										decidePiece(bonus);
									}
								}
							}
						}
					}
				}
				
			}
			else //if number on dice is not SIX
			{
				gotoxy(1, 37);
				if (count > 1)  //if player has more than one pieces available
				{
					cout << "Which piece do you want to move : ";
					decidePiece(dice);
				}
				else  //if only one piece is available
				{
					for (int i = 0; i < 4; i++)
					{
						if (pieces[i].isAlive)
						{
							move(pieces[i], dice);
							break;
						}
					}
				}
			}

		}
		bool flag = true;
		for (int i = 0; i < 4; i++)
		{
			if (!(pieces[i].getX() == winningLocation.X && pieces[i].getY() == winningLocation.Y))
				flag = false;
		}
		if (flag)
		{
			isInGame = false;
			position = ++winCount;
		}
	}
	void decidePiece(const int number)
	{
		int choice2;
		for (int i = 0; i < 4; i++)
		{
			if (pieces[i].isAlive && !pieces[i].isWon)
				cout << pieces[i].num << ",";
		}
		cout << "\b ? ";
		while (!(cin >> choice2))
		{
			// Explain error
			cout << "ERROR: a number must be entered: ";
			// Clear input stream
			cin.clear();
			// Discard previous input
			cin.ignore(132, '\n');
		}
		while (choice2 < 1 || choice2>4)
		{
			cout << "Enter valid choice...!" << endl;
			while (!(cin >> choice2))
			{
				// Explain error
				cout << "ERROR: a number must be entered: ";
				// Clear input stream
				cin.clear();
				// Discard previous input
				cin.ignore(132, '\n');
			}
		}
		while (!(pieces[choice2 - 1].isAlive) || pieces[choice2 - 1].isWon)   //input validation
		{
			cout << "Enter valid choice...!" << endl;
			while (!(cin >> choice2))
			{
				// Explain error
				cout << "ERROR: a number must be entered: ";
				// Clear input stream
				cin.clear();
				// Discard previous input
				cin.ignore(132, '\n');
			}
		}
		move(pieces[choice2 - 1], number);
	}
	void unlockPiece()
	{
		int choice2;
		cout << "Which piece do you want to unlock : ";
		for (int i = 0; i < 4; i++)
		{
			if (!pieces[i].isAlive)
				cout << pieces[i].num << ",";
		}
		cout << "\b ? ";
		while (!(cin >> choice2))
		{
			// Explain error
			cout << "ERROR: a number must be entered: ";
			// Clear input stream
			cin.clear();
			// Discard previous input
			cin.ignore(132, '\n');
		}

		while ((pieces[choice2 - 1].isAlive))   //input validation
		{
			cout << "Enter valid choice...!" << endl;
			while (!(cin >> choice2))
			{
				// Explain error
				cout << "ERROR: a number must be entered: ";
				// Clear input stream
				cin.clear();
				// Discard previous input
				cin.ignore(132, '\n');
			}
		}

		pieces[choice2 - 1].setLocation(defaultLocation);
		COORD temp = pieces[choice2 - 1].getSpawn();
		updateBoard(pieces[choice2 - 1], temp.X, temp.Y);
		pieces[choice2 - 1].isAlive = true;
		count++;
	}


};

int Player::winCount = 0;
