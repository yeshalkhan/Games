#include <iostream>
#include <stdlib.h>
using namespace std;
bool flag = false;
int computerChoice();
int userChoice();
void winner(int, int);
int main()
{
    int user = userChoice();
    int computer = computerChoice();
    while (user == computer)
    {
        cout << "Both players have entered the same choice\nStarting the game again" << endl;
        int uCh = userChoice();
        int cCh = computerChoice();
    }
    winner(computer, user);
}
int computerChoice()
{
    srand(time(0));
    int randomNumber = rand() % 3 + 1;
    if (randomNumber == 1) cout << "Computer has chosen Rock" << endl;
    if (randomNumber == 2) cout << "Computer has chosen Paper" << endl;
    if (randomNumber == 3) cout << "Computer has chosen Scissors" << endl;
    return randomNumber;
}
int userChoice()
{
    int choice;
    cout << "Enter 1 for Rock, 2 for Paper, 3 for Scissors:" << endl;
    cin >> choice;
    while (!(choice >= 1 && choice <= 3))
    {
        cout<<"Wrong choice! Enter 1 for Rock, 2 for Paper, 3 for Scissors:" << endl;
        cin >> choice;
    }
    if (choice == 1) cout << "You have chosen Rock" << endl;
    if (choice == 2) cout << "You have chosen Paper" << endl;
    if (choice == 3) cout << "You have chosen Scissors" << endl;
    return choice;
}
void winner(int computer, int user)
{
    if (computer == 1 && user == 3) cout << "Computer is the winner" << endl;
    if (computer == 3 && user == 2) cout << "You are the winner" << endl;
    if (computer == 2 && user == 1) cout << "Computer is the winner" << endl;
    if (computer == 3 && user == 1) cout << "You are the winner" << endl;
    if (computer == 2 && user == 3) cout << "Computer is the winner" << endl;
    if (computer == 1 && user == 2) cout << "You are the winner" << endl;
}
