#include<iostream>
using namespace std;
#define r 3
#define c 3
bool Xrows(char[][c], int);
bool Xcols(char[][c], int);
bool Xdiag1(char ar[][c]);
bool Xdiag2(char ar[][c]);
bool Ocols(char[][c], int);
bool Orows(char[][c], int);
bool Odiag1(char ar[][c]);
bool Odiag2(char ar[][c]);
int main()
{
	char ar[r][c];
	int rowX, columnX, rowO, columnO;

	//Initialization with asterisks
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			ar[i][j] = '*';
		}
	}

	int l;
	for (l = 1; l <= 5; l++)
	{
		//Display Game Board 
		cout << "Board array:" << endl;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				cout << ar[i][j] << " ";
			}
			cout << endl;
		}

		//Input from User 1 (X's)
		cout << "Where does player 1 want to place X?" << endl;
		cout << "Enter row number:"; cin >> rowX;
		cout << "Enter column number:"; cin >> columnX;
		ar[rowX][columnX] = 'X';

		//Input from User 2 (O's)
		if (l < 5)  //2nd user can only have 4 entries
		{
			cout << "Where does player 2 want to place O?" << endl;
			cout << "Enter row number:"; cin >> rowO;
			cout << "Enter column number:"; cin >> columnO;
			ar[rowO][columnO] = 'O';
		}

		//Checking for X's
		if (Xrows(ar, 0) || Xrows(ar, 1) || Xrows(ar, 2) || Xcols(ar, 0) || Xcols(ar, 1) || Xcols(ar, 2) || Xdiag1(ar) || Xdiag2(ar))
		{
			cout << endl << "Player 1 won" << endl;
			break;
		}

		//Checking for O's
		else if (Orows(ar, 0) || Orows(ar, 1) || Orows(ar, 2) || Ocols(ar, 0) || Ocols(ar, 1) || Ocols(ar, 2) || Odiag1(ar) || Odiag2(ar))
		{
			cout << endl << "Player 2 won" << endl;
			break;
		}

	}

	cout << endl << "Final Board array:" << endl;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << ar[i][j] << " ";
		}
		cout << endl;
	}

	if (l > 5)  //If break statement didn't execute i.e. no body won during the loop
	{
		cout << endl << "It's a tie!" << endl;
	}

}
bool Xrows(char ar[][c], int i)
{
	bool flag = false;
	int j;
	for (j = 0; j < 3; j++)
	{
		if (ar[i][j] != 'X')
			break;
	}
	if (j == 3)
		flag = true;
	return flag;
}
bool Xcols(char ar[][c], int i)
{
	bool flag = false;
	int j;
	for (j = 0; j < 3; j++)
	{
		if (ar[j][i] != 'X')
			break;
	}
	if (j == 3)
		flag = true;
	return flag;
}
bool Xdiag1(char ar[][c])
{
	bool flag = false;
	int i, j;
	for (i = 0, j = 0; j < 3; i++, j++)
	{
		if (ar[i][j] != 'X')
			break;
	}
	if (i == 3) flag = true;
	return flag;
}
bool Xdiag2(char ar[][c])
{
	bool flag = false;
	int i, j;
	for (i = 0, j = 2; j >= 0; i++, j--)
	{
		if (ar[i][j] != 'X')
			break;
	}
	if (i == 3) flag = true;
	return flag;
}
bool Orows(char ar[][c], int i)
{
	bool flag = false;
	int j;
	for (j = 0; j < 3; j++)
	{
		if (ar[i][j] != 'O')
			break;
	}
	if (j == 3)
		flag = true;
	return flag;
}
bool Ocols(char ar[][c], int i)
{
	bool flag = false;
	int j;
	for (j = 0; j < 3; j++)
	{
		if (ar[j][i] != 'O')
			break;
	}
	if (j == 3)
		flag = true;
	return flag;
}
bool Odiag1(char ar[][c])
{
	bool flag = false;
	int i, j;
	for (i = 0, j = 0; j < 3; i++, j++)
	{
		if (ar[i][j] != 'O')
			break;
	}
	if (i == 3) flag = true;
	return flag;
}
bool Odiag2(char ar[][c])
{
	bool flag = false;
	int i, j;
	for (i = 0, j = 2; j >= 0; i++, j--)
	{
		if (ar[i][j] != 'O')
			break;
	}
	if (i == 3) flag = true;
	return flag;
}
