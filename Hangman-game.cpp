#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

const int MAX_TRIES = 5;
int revealLetter(char, string, string&);
void replaceLetter(char, string&, int, string);
void setConsoleFontSize(int);
void displayHangmanFigure(int);

int main()
{
	
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);   // to open the console screen in full size 
	setConsoleFontSize(20);	   // increase font size 

	string name, word;
	char letter;
	int numOfWrongGuesses = 0;
	string words[] =
	{
		"housefull",
		"harry potter",
		"titanic",
		"avengers",
		"avatar",
		"annabelle",
		"bahubali",
		"frozen",
		"minions",
		"tangled",
		"hera pheri",
		"welcome"
	};

	// choose a word from array of words randomly
	srand(time(NULL));
	int n = rand() % 12;
	word = words[n];
	int result;

	// Initialize the secret word with the * character.
	string secretWord(word.length(), '*');
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == ' ')
			secretWord[i] = ' ';
	}

	// welcome message
	cout << "\u001b[36m";
	cout << "\n\t\t\t\t\t-------------------------------";
	cout << endl << "\t\t\t\t\t\tWELCOME TO HANGMAN" << endl;
	cout << "\t\t\t\t\t-------------------------------\n\n";
	cout << "RULES: " << endl << endl;
	cout << "\u001b[37m";
	cout << " \tYou have to guess a movie name.\n\tEach letter is represented by a star.\n\tYou have to type only one letter in one try.\n\tYou have " << MAX_TRIES << " tries to try and guess the word.." << endl;
	cout << "\u001b[36m";
	cout << "\nPress any key to start the game..." << endl;
	cout << "\u001b[37m";
	char g = _getch();	//wait for user to press a key
	system("cls");  //clear the output screen
	cout << "\u001b[33m----------------------------------------------------------------------------------------------------------------------------\u001b[37m" << endl;
	setConsoleFontSize(18);	   // increase font size 

	// Loop until the guesses are used up
	while (numOfWrongGuesses < MAX_TRIES)
	{
		cout << "\n\n" << secretWord;
		cout << "\n\nGuess a letter: ";
		cin >> letter;
		result = revealLetter(tolower(letter), word, secretWord);

		// Fill secret word with letter if the guess is correct, otherwise increment the number of wrong guesses.
		if (result == 0)
		{
			Beep(950, 500); // make a beep sound of 950 hertz for 500 millisecond  
			cin.get(); // wait 
			cout << endl << "\u001b[31m" << "Whoops! That letter isn't in there!\n" << "\u001b[37m" << endl;
			numOfWrongGuesses++;
			displayHangmanFigure(numOfWrongGuesses);
		}
		else if (result == -1)
		{
			Beep(950, 500); // make a beep sound of 950 hertz for 500 milliseconds     
			cin.get(); // wait 
			cout << endl << "\u001b[31m" << "You already guessed that letter!\n" << "\u001b[37m" << endl;
			numOfWrongGuesses++;
			displayHangmanFigure(numOfWrongGuesses);
		}
		else
		{
			cout << endl << "\u001b[32m" << "You found a letter!" << "\u001b[37m" << endl;
		}

		cout << "You have " << MAX_TRIES - numOfWrongGuesses << " guesses left." << endl << endl;
		cout << "\u001b[33m----------------------------------------------------------------------------------------------------------------------------\u001b[37m" << endl;

		// Check if user guessed the word
		if (word == secretWord)
		{
			Sleep(3000);	// wait for 3 seconds
			system("cls");  //clear the output screen
			cout << "\u001b[33m----------------------------------------------------------------------------------------------------------------------------\u001b[37m" << endl << endl;
			cout << "\n\tThe word was : " << "\u001b[35m" << word << endl;
			cout << "\tCONGRATULATIONS! You guessed the word!" << endl<<endl;
			cout << "\u001b[33m----------------------------------------------------------------------------------------------------------------------------\u001b[37m" << endl << endl;
			return 0;
		}
	}

	// if loop has ended, all guesses have been used
	Sleep(3000);	// wait for 3 seconds
	system("cls"); //clear the output screen
	cout << "\u001b[33m----------------------------------------------------------------------------------------------------------------------------\u001b[37m" << endl << endl;
	cout << "\n\tThe word was : " << "\u001b[35m" << word << endl;
	cout << "\t\u001b[35m" << "YOU LOST THE GAME...YOU'VE BEEN HANGED." << endl << endl;
	cout << "\n\u001b[37m";
	displayHangmanFigure(numOfWrongGuesses);
	cout << "\n\u001b[33m----------------------------------------------------------------------------------------------------------------------------\u001b[37m" << endl << endl;
	return 0;
}

/* Fill in the unfinished secret word with the correct letter.
 Return -1 if the character is already guessed.
 Return 0 if character is not in the secret word.*/

int revealLetter(char guess, string word, string& secretword)
{
	int matches = 0;
	int len = word.length();
	for (int i = 0; i < len; i++)
	{
		// Did we already match this letter in a previous guess?
		if (guess == secretword[i])
			return -1;

		// Is the guess in the secret word?
		else if (guess == word[i])
		{
			secretword[i] = guess;

			// replace the next * characters in guessword with the matching letter
			replaceLetter(guess, secretword, i + 1, word);
			matches++;
			break;
		}
	}
	return matches;
}

void replaceLetter(char guess, string& secretword, int i, string word)
{
	int len = word.length();
	for (; i < len; i++)
	{
		if (word[i] == guess)
		{
			secretword[i] = guess;
		}
	}
}

void setConsoleFontSize(int fontSize)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo = { 0 };
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.dwFontSize.Y = fontSize; // height of the font in logical units

	wcscpy_s(fontInfo.FaceName, L"Lucida Console"); // set the font face here

	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

void displayHangmanFigure(int numOfWrongGuesses)
{
	if (numOfWrongGuesses == 1)
	{
		cout << "\t ___________" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl << endl;

	}
	else if (numOfWrongGuesses == 2)
	{
		cout << "\t ___________" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 ( )	    \u001b[37m" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl << endl;
	}
	else if (numOfWrongGuesses == 3)
	{
		cout << "\t ___________" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 ( )	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl << endl;
	}
	else if (numOfWrongGuesses == 4)
	{
		cout << "\t ___________" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 ( )	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 /|\\    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|			" << endl;
		cout << "\t|			" << endl << endl;
	}
	else if (numOfWrongGuesses == 5)
	{
		cout << "\t ___________" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 ( )	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 /|\\    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	  |	    \u001b[37m" << endl;
		cout << "\t|\u001B[31m	 / \\	    \u001b[37m" << endl;
		cout << "\t|			" << endl << endl;
	}
}
