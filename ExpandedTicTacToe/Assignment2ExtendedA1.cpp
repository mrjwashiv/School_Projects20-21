// Assignment2ExtendedA1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct player {
	string fullName;
	string fName;
	string lName;
	char marker;
	int stats[3] = { 0, 0, 0 };
};

void outputHeader();
int stringToInt(string);
int intIsValid(string, int, int);
player* getPlayers(int*);
void getNames(int*, player*);
void getBoardDimensions(int*);
char** initializeBoard(int*);
void printBoard(int*, char**);
char isWin(int*, char**, player*, char);
void itsaTie(int*, player*, char**);
string choiceIsValid(string, int*);
void canMove(string, int*, char**, char);
void makeMove(char**, player*, int*, char);
char switchTurn(char, int*, player*);
void outputStats(player*, int*);


int main()
{
	outputHeader();

	int settings[4];
	char** board;
	player* playerInfo = getPlayers(settings);
	char playAgain = 'y';
	char turn = 'a';
	char whoStarted;
	char winner;
	bool isTie = false;
	int count;

    getNames(settings, playerInfo);
	

	while (playAgain == 'y' || playAgain == 'Y')
	{ 	
		getBoardDimensions(settings);
		board = initializeBoard(settings);

		int row = settings[0];
		int col = settings[1];
		count = 1;
		winner = ' ';
		whoStarted = turn;

		cout << "Start game!!!" << endl << endl;

		while (winner == ' ' && !isTie)
		{
			printBoard(settings, board);
			makeMove(board, playerInfo, settings, turn);
			winner = isWin(settings, board, playerInfo, turn);

			if (winner != ' ')
			{
				printBoard(settings, board);
			}

			if (count >= row * col)
			{
				itsaTie(settings, playerInfo, board);
				isTie = true;
			}

			turn = switchTurn(turn, settings, playerInfo);

			count++;
		}

		if (isTie)
		{
			whoStarted = switchTurn(whoStarted, settings, playerInfo);
			turn = whoStarted;
			isTie = false;
		}
		else
		{
			turn = switchTurn(winner, settings, playerInfo);
		}

		outputStats(playerInfo, settings);
		
		cout << "Continue? (y/n) >> ";
		cin >> playAgain;
		cout << endl;
	}

	cout << "Thanks for playing!" << endl;
}

/*************************************************************
*	THIS FUNCTION OUTPUTS A HEADER FOR THE GAME				 *
*															 *
*************************************************************/

void outputHeader()
{
	cout << "/*************************************************************\ " << endl;
	cout << "*                                                             * " << endl;
	cout << "*                     TIC TAC TOE II                          * " << endl;
	cout << "*                                                             * " << endl;
	cout << "\*************************************************************/ " << endl << endl;

	cout << "WELCOME USERS!" << endl << endl;
	cout << "# TO GET STARTED ENTER THE NUMBER OF PLAYERS." << endl;
	cout << "# ENTER YOUR FIRST AND LAST NAMES." << endl;
	cout << "# ONCE YOU FIGURE OUT THE BOARD DIMENSIONS THE GAME WILL START." << endl;
	cout << "# ENTER A LETTER AND A NUMBER TO MAKE YOUR MOVE. " << endl << endl;
	cout << "ENJOY THE GAME!!!" << endl << endl;
}

/*************************************************************
*	   THIS FUNCTION CONVERTS A STRING TO AN INTEGER		 *
*															 *
*************************************************************/

int stringToInt(string str)
{
	int num = 0;
	int decimal;
	int exponent = 0;

	for (int i = str.length() - 1; i >= 0; i--)
	{	
		decimal = 1;

		for (int i = 0; i < exponent; i++)
		{
			decimal *= 10;
		}

		int digit = str[i] - '0';
		num += digit * decimal;
		exponent++;
	}

	return num;
}

/*************************************************************
*	 THIS FUNCTION CHECKS TO SEE IF AN INT USER INPUT IS  	 *
*						   VALID							 *
*************************************************************/

int intIsValid(string check, int min, int max)
{
	bool valid = false;
	string tryAgain;

	int checking = stringToInt(check);

	while (!valid)
	{
		if (checking < min || checking > max)
		{
			cout << "You Should Try a Number Between " << min << " & " << max << " >> ";
			cin >> tryAgain;
			cout << endl;

			check = tryAgain;
			checking = stringToInt(check);
		}
		else
		{
			valid = true;
		}
	}

	cout << endl;

	return checking;
}

/*************************************************************
*	THIS FUNCTION GETS THE NUMBER OF PLAYERS FOR THE GAME	 *
*															 *
*************************************************************/

player* getPlayers(int* gameSettings)
{
	string input;

	cout << "Please enter the number of players for this game >> ";
	cin >> input;
	cout << endl;

	gameSettings[2] = intIsValid(input, 2, 5);
	gameSettings[3] = 0;

	player* playerInfo = new player[gameSettings [2]];

	char peice = 'a';

	for (int i = 0; i < gameSettings[2]; i++)
	{
		playerInfo[i].marker = peice;
		peice++;
	}

	return playerInfo;
}

/*************************************************************
*	   THIS FUNCTION GETS THE NAMES OF ALL THE PLAYERS     	 *
*															 *
*************************************************************/

void getNames(int* gameSettings, player* playerInfo)
{
	for (int i = 0; i < gameSettings[2]; i++)
	{
		cout << "Player " << i + 1 << ", please enter your first and last name >> ";
		cin >> playerInfo[i].fName >> playerInfo[i].lName;
		cout << endl;

		playerInfo[i].fName[0] = toupper(playerInfo[i].fName[0]);
		playerInfo[i].lName[0] = toupper(playerInfo[i].lName[0]);
		playerInfo[i].fullName = playerInfo[i].fName + " " + playerInfo[i].lName;
	}

	cout << endl;
}

/*************************************************************
*	  THIS FUNCTION GETS NUMBER OF ROWS AND COLUMNS FOR		 *
*					      THE BOARD							 *
*************************************************************/

void getBoardDimensions(int* gameSettings)
{
	string input;
	
	cout << "Please enter the number of rows >> ";
	cin >> input;
	cout << endl;
	
	gameSettings[0] = intIsValid(input, 3, 11);
	
	cout << "Please enter the number of columns >> ";
	cin >> input;
	cout << endl;

	gameSettings[1] = intIsValid(input, 3, 16);
}

/*************************************************************
*	     THIS FUNCTION EMPTIES ALL THE BOARD SPACES 		 *
*															 *
*************************************************************/

char** initializeBoard(int* gameSettings)
{
	int row = gameSettings[0];
	int col = gameSettings[1];

	char** board = new char*[row];

	for (int i = 0; i < row; i++)
	{
		board[i] = new char[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}

	return board;
}

/*************************************************************
*	       THIS FUNCTION PRINTS OUT THE GAME BOARD		     *
*															 *
*************************************************************/

void printBoard(int* gameSettings, char** board)
{
	int isRow = 1;
	int size = gameSettings[0] * gameSettings[1];
	int row = gameSettings[0] * 2 + 3; 
	int col = gameSettings[1];
	int rowElement = 0;
	char letter = 'A';

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == 0 || i == row - 1)
			{
				if (j == 0)
				{
					cout << "    " << j + 1;
				}
				else if (j >= 9)
				{
					cout << "  " << j + 1;
				}
				else
				{
					cout << "   " << j + 1;
				}
			}
			else
			{
				if (isRow % 2 == 0)
				{
					if (j == 0)
					{
						cout << letter << " ";
					}

					cout << ": " << board[rowElement][j] << " ";
				}
				else
				{
					if (j == 0)
					{
						cout << "  ";
					}

					cout << " ---";
				}

			}

		}

		if (isRow % 2 == 0 && i != row - 1)
		{
			cout << ": " << letter;

			letter++;
			rowElement++;
		}

		if (i != 0)
		{
			isRow++;
		}
		
		cout << endl;
	}

	cout << endl;
}

/*************************************************************
*	     THIS FUNCTION CHECKS THE BOARD FOR A WIN	     	 *
*															 *
*************************************************************/

char isWin(int* gameSettings, char** board, player* playerInfo, char turn)
{
	for (int i = 0; i < gameSettings[0]; i++)
	{
		for (int j = 0; j < gameSettings[1] - 2; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && turn == board[i][j])
			{
				board[i][j] = board[i][j + 1] = board[i][j + 2] = toupper(turn);

				for (int k = 0; k < *(gameSettings + 2); k++)
				{
					if (playerInfo[k].marker == turn)
					{
						cout << playerInfo[k].fName << " wins!!!" << endl << endl;

						playerInfo[k].stats[0] += 1;
					}
					else
					{
						playerInfo[k].stats[1] += 1;
					}
				}

				gameSettings[3] += 1;

				return turn;
			}
		}
	}

	for (int i = 0; i < *(gameSettings) - 2; i++)
	{
		for (int j = 0; j < *(gameSettings + 1); j++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && turn == board[i][j])
			{
				board[i][j] = board[i + 1][j] = board[i + 2][j] = toupper(turn);

				for (int k = 0; k < *(gameSettings + 2); k++)
				{
					if (playerInfo[k].marker == turn)
					{
						cout << playerInfo[k].fName << " wins!!!" << endl << endl;

						playerInfo[k].stats[0] += 1;
					}
					else
					{
						playerInfo[k].stats[1] += 1;
					}
				}

				gameSettings[3] += 1;

				return turn;
			}
		}
	}

	for (int i = 0; i < *(gameSettings) - 2; i++)
	{
		for (int j = 0; j < *(gameSettings + 1) - 2; j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && turn == board[i][j])
			{
				board[i][j] = board[i + 1][j + 1] = board[i + 2][j + 2] = toupper(turn);

				for (int k = 0; k < *(gameSettings + 2); k++)
				{
					if (playerInfo[k].marker == turn)
					{
						cout << playerInfo[k].fName << " wins!!!" << endl << endl;

						playerInfo[k].stats[0] += 1;
					}
					else
					{
						playerInfo[k].stats[1] += 1;
					}
				}

				gameSettings[3] += 1;

				return turn;
			}
		}
	}

	for (int i = 0; i < *(gameSettings) - 2; i++)
	{
		for (int j = 2; j < *(gameSettings + 1); j++)
		{
			if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2] && turn == board[i][j])
			{
				board[i][j] = board[i + 1][j - 1] = board[i + 2][j - 2] = toupper(turn);

				for (int k = 0; k < *(gameSettings + 2); k++)
				{
					if (playerInfo[k].marker == turn)
					{
						cout << playerInfo[k].fName << " wins!!!" << endl << endl;

						playerInfo[k].stats[0] += 1;
					}
					else
					{
						playerInfo[k].stats[1] += 1;
					}
				}

				gameSettings[3] += 1;

				return turn;
			}
		}
	}

	return ' ';
}

/*************************************************************
*	        THIS FUNCTION DECLARES THE GAME A TIE	    	 *
*															 *
*************************************************************/

void itsaTie(int* gameSettings, player* playerInfo, char** board)
{
	for (int i = 0; i < gameSettings[2]; i++)
	{
		playerInfo[i].stats[2] += 1;
	}

	gameSettings[3] += 1;

	cout << "It's a tie." << endl << endl;

	printBoard(gameSettings, board);
}

/*************************************************************
*	THIS FUNCTION CHECKS THE USER'S INPUT AND MAKE SURE ITS	 *
*					  WITHIN THE BOUNDS						 *
*************************************************************/

string choiceIsValid(string choice, int* gameSettings)
{
	char max = 'A';
	bool valid = false;
	int count = 0;
	string num;
	int col;

	for (int i = 0; i < *(gameSettings) - 1; i++)
	{
		max++;
	}

	while (!valid)
	{
		choice[0] = toupper(choice[0]);
		num = choice.substr(1);
		col = stringToInt(num);

		if (choice[0] > max || choice[0] < 'A' || col > *(gameSettings + 1) || col < 1)
		{
			cout << "Invalid move, please try again >> ";
			cin >> choice;
			cout << endl;
		}
		else
		{
			valid = true;
		}
	}

	cout << endl;

	return choice;
}

/*************************************************************
*	THIS FUNCTION CHECKS TO SEE IF THE SPACE A PLAYER CHOSE  *
*						IS NOT TAKEN						 *
*************************************************************/

void canMove(string move, int* gameSettings, char** board, char turn)
{
	char max = 'A';
	int count = 0;
	bool valid = false;
	string num;
	int row;
	int col;

	for (int i = 0; i < *(gameSettings) - 1; i++)
	{
		max++;
	}

	while (!valid)
	{
		num = move.substr(1);
		col = stringToInt(num) - 1;
		char charRow = 'A';

		while (charRow != move[0])
		{
			count++;
			charRow++;
		}

		row = count;

		if (board[row][col] != ' ')
		{
			cout << "This space is taken, choose another one >> ";
			cin >> move;
			cout << endl;

			move = choiceIsValid(move, gameSettings);
		}
		else
		{
			valid = true;
		}

		count = 0;
	}

	board[row][col] = turn;
}

/*************************************************************
*	THIS FUNCTION ASKS THE USER TO MAKE THEIR MOVE AND   	 *
*			  CHANGES THE BOARD ACCORDINGLY					 *
*************************************************************/

void makeMove(char** board, player* playerInfo, int* gameSettings, char turn)
{
	string choice;
	int count = 0;

	for (char c = 'a'; c <= 'e'; c++)
	{
		if (turn == c)
		{
			cout << (playerInfo + count)->fName << "(" << turn << "), please make your move >> ";
			cin >> choice;
			cout << endl;
		}

		count++;
	}

	choice = choiceIsValid(choice, gameSettings);
	canMove(choice, gameSettings, board, turn);
}

/*************************************************************
*	       THIS FUNCTION SWITCHES WHOSE TURN IT IS		     *
*															 *
*************************************************************/

char switchTurn(char turn, int* gameSettings, player* playerInfo)
{
	if (turn == playerInfo[gameSettings[2] - 1].marker)
	{
		return 'a';
	}
	else
	{	
		turn++;
	}

	return turn;
}

/*************************************************************
*	    THIS FUNCTION OUTPUTS THE STATS FOR EACH PLAYER	     *
*															 *
*************************************************************/

void outputStats(player* playerInfo, int* gameSettings)
{
	int maxSpace = playerInfo[0].fullName.length();
	string tableRow = "  ------ ------ ------";
	string winLoss = " : WINS : LOSS : DRAW :";

	for (int i = 0; i < *(gameSettings + 2); i++)
	{
		if (playerInfo[i].fullName.length() > maxSpace)
		{
			maxSpace = playerInfo[i].fullName.length();
		}
	}

	maxSpace += 1;

	int rowLength = maxSpace + tableRow.length();
	int winLength = maxSpace + winLoss.length();

	cout << "Total game(s) played: " << gameSettings[3] << endl << endl;
	cout << setw(rowLength) << tableRow << endl;
	cout << setw(winLength) << winLoss << endl;
	cout << setw(rowLength) << tableRow << endl;

	for (int i = 0; i < *(gameSettings + 2); i++)
	{
		cout << right << setw(maxSpace) << playerInfo[i].fullName << " :" << right << setw(5)
			 << playerInfo[i].stats[0] << " :" << right << setw(5) << playerInfo[i].stats[1] 
			 << " :" << right << setw(5) << playerInfo[i].stats[2] << " :" << endl;
		cout << setw(rowLength) << tableRow << endl;
	}

	cout << endl;
}