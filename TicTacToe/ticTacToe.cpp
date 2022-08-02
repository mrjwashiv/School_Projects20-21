#include "ticTacToe.h"

/*************************************************************
*	THIS METHOD IS A CONSTRUCTOR THAT SETS VARIABLES TO      *
*				    THEIR DEFAULT VALUE					     *
*************************************************************/

ticTacToe::ticTacToe()
{
	board[0] = "1";
	board[1] = "2";
	board[2] = "3";
	board[3] = "4";
	board[4] = "5";
	board[5] = "6";
	board[6] = "7";
	board[7] = "8";
	board[8] = "9";

	for (int i = 0; i < 3; i++)
	{
		p1Stats[i] = 0;
		p2Stats[i] = 0;
	}

	turn = true;

	p1 = "x";
	p2 = "o";
}

/*************************************************************
*	THESE FUNCTIONS SET PRIVATE METHODS 					 *
*															 *
*************************************************************/

void ticTacToe::setp1Name(string name)
{
	p1Name = name;
}

void ticTacToe::setp2Name(string name)
{
	p2Name = name;
}

void ticTacToe::setfName1(string name)
{
	fName1 = name;
}

void ticTacToe::setfName2(string name)
{
	fName2 = name;
}

void ticTacToe::setlName1(string name)
{
	lName1 = name;
}

void ticTacToe::setlName2(string name)
{
	lName2 = name;
}

void ticTacToe::setp1(string marker)
{
	p1 = marker;
}

void ticTacToe::setp2(string marker)
{
	p2 = marker;
}

void ticTacToe::setboard(string* gameBoard)
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = *(gameBoard + i);
	}
}

void ticTacToe::setp1Stats(int* stats)
{
	for (int i = 0; i < 3; i++)
	{
		p1Stats[i] = *(stats + i);
	}
}

void ticTacToe::setp2Stats(int* stats)
{
	for (int i = 0; i < 3; i++)
	{
		p2Stats[i] = *(stats + i);
	}
}

void ticTacToe::setturn(bool Turn)
{
	turn = Turn;
}

/*************************************************************
*	THESE FUNCTIONS GET PRIVATE METHODS 					 *
*															 *
*************************************************************/

string ticTacToe::getp1Name()
{
	return p1Name;
}

string ticTacToe::getp2Name()
{
	return p2Name;
}

string ticTacToe::getfName1()
{
	return fName1;
}

string ticTacToe::getfName2()
{
	return fName2;
}

string ticTacToe::getlName1()
{
	return lName1;
}

string ticTacToe::getlName2()
{
	return lName2;
}

string ticTacToe::getp1()
{
	return p1;
}

string ticTacToe::getp2()
{
	return p2;
}

string* ticTacToe::getboard()
{
	return board;
}

int* ticTacToe::getp1Stats()
{
	return p1Stats;
}

int* ticTacToe::getp2Stats()
{
	return p2Stats;
}

bool ticTacToe::getturn()
{
	return turn;
}

/*************************************************************
*	THIS FUNCTION OUTPUTS A HEADER FOR THE GAME				 *
*															 *
*************************************************************/

void ticTacToe::outputHeader()
{
	cout << " /*************************************************************\ " << endl;
	cout << " *                                                             * " << endl;
	cout << " *                       TIC TAC TOE                           * " << endl;
	cout << " *                                                             * " << endl;
	cout << " \*************************************************************/ " << endl << endl;

	cout << " WELCOME USERS!" << endl << endl;
	cout << " # TO GET STARTED ENTER YOUR FIRST AND LAST NAMES." << endl;
	cout << " # ONCE YOU FIGURE OUT WHO GOES FIRST THE GAME WILL START." << endl;
	cout << " # ENTER A NUMBER TO MAKE YOUR MOVE. " << endl << endl;
	cout << " ENJOY THE GAME!!!" << endl << endl;
}

/*************************************************************
*	THIS FUNCTION GETS THE PLAYERS' NAMES					 *
*															 *
*************************************************************/

void ticTacToe::getNames()
{
	cout << " Player 1, Enter your first and last name >> ";
	cin >> fName1 >> lName1;


	cout << " Player 2, Enter your first and last name  >> ";
	cin >> fName2 >> lName2;
	cout << endl;

	p1Name = fName1 + " " + lName1;
	p2Name = fName2 + " " + lName2;
}

/*************************************************************
*	    THIS FUNCTION GETS THE PLAYER THAT GOES FIRST        *
*			      (ONLY FOR THE FIRST GAME)				     *
*************************************************************/

bool ticTacToe::whoseFirst()
{
	cout << " " << fName1 << ", you will be " << p1 << " in the game!" << endl;
	cout << " This means " << fName2 << " will be " << p2 << "." << endl << endl;
	
	string first;
	cout << " Choose who will go first (1 or 2) >> ";
	cin >> first;
	cout << endl;

	if (first == "1")
	{
		turn = true;
		
		cout << " " << fName1 << " goes first!" << endl << endl;
	}

	else
	{
		turn = false;

		cout << " " << fName2 << " goes first!" << endl << endl;
	}
	return turn;
}

/*************************************************************
*	THIS FUNCTION OUTPUTS THE GAME BOARD                     *
*															 *
*************************************************************/

void ticTacToe::outputBoard()
{
	cout << " +---+---+---+" << endl;
	cout << " | " << board[0] << " | " << board[1] << " | " << board[2] << " |" << endl;
	cout << " +---+---+---+" << endl;
	cout << " | " << board[3] << " | " << board[4] << " | " << board[5] << " |" << endl;
	cout << " +---+---+---+" << endl;
	cout << " | " << board[6] << " | " << board[7] << " | " << board[8] << " |" << endl;
	cout << " +---+---+---+" << endl;
	cout << endl;
}

/*************************************************************
*	THIS FUNCTION CHECKS FOR A WIN AND UPDATES STATS         *
*															 *
*************************************************************/

string ticTacToe::isWin()
{
	if (board[0] == board[1] && board[1] == board[2])
	{
		if (board[0] == p1)
		{
			board[0] = board[1] = board[2] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[0] == p2)
		{
			board[0] = board[1] = board[2] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}

	else if (board[3] == board[4] && board[4] == board[5])
	{
		if (board[3] == p1)
		{
			board[3] = board[4] = board[5] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[3] == p2)
		{
			board[3] = board[4] = board[5] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}

	else if (board[6] == board[7] && board[7] == board[8])
	{
		if (board[6] == p1)
		{
			board[6] = board[7] = board[8] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[6] == p2)
		{
			board[6] = board[7] = board[8] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p1;
		}
	}

	else if (board[0] == board[3] && board[3] == board[6])
	{
		if (board[0] == p1)
		{
			board[0] = board[3] = board[6] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[0] == p2)
		{
			board[0] = board[3] = board[6] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}

	else if (board[1] == board[4] && board[4] == board[7])
	{
		if (board[1] == p1)
		{
			board[1] = board[4] = board[7] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[1] == p2)
		{
			board[1] = board[4] = board[7] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}

	else if (board[2] == board[5] && board[5] == board[8])
	{
		if (board[2] == p1)
		{
			board[2] = board[5] = board[8] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[2] == p2)
		{
			board[2] = board[5] = board[8] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}

	else if (board[0] == board[4] && board[4] == board[8])
	{
		if (board[0] == p1)
		{
			board[0] = board[4] = board[8] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[0] == p2)
		{
			board[0] = board[4] = board[8] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}

	else if (board[2] == board[4] && board[4] == board[6])
	{
		if (board[2] == p1)
		{
			board[2] = board[4] = board[6] = "X";
			p1Stats[0] += 1;
			p2Stats[1] += 1;
			return p1;
		}
		else if (board[2] == p2)
		{
			board[2] = board[4] = board[6] = "O";
			p1Stats[1] += 1;
			p2Stats[0] += 1;
			return p2;
		}
	}
	
	return " ";
}

/*************************************************************
*	THIS FUNCTION PROMPTS THE USER TO TAKE THIER TURN        *
*															 *
*************************************************************/

void ticTacToe::makeMove(bool turn)
{
	int choice;
	if (turn)
	{
		cout << " " << fName1 << "(x), Make Your Move >> ";
		cin >> choice;

		board[choice - 1] = p1;
	}

	else
	{
		cout << " " << fName2 << "(o), Make Your Move >> ";
		cin >> choice;

		board[choice - 1] = p2;
	}
	cout << endl;
}

/*************************************************************
*	THIS FUNCTION SWITCHES THE TURN OF THE PLAYER            *
*															 *
*************************************************************/

void ticTacToe::switchTurn()
{
	if (turn == true) { turn = false; }
	else { turn = true; }
}

/*************************************************************
*	THIS FUNCTION RESETS THE BOARD FOR A NEW GAME TO START   *
*															 *
*************************************************************/

void ticTacToe::clearBoard()
{
	board[0] = "1";
	board[1] = "2";
	board[2] = "3";
	board[3] = "4";
	board[4] = "5";
	board[5] = "6";
	board[6] = "7";
	board[7] = "8";
	board[8] = "9";
}

/*************************************************************
*	THIS FUNCTION OUTPUTS THE PLAYER STATS					 *
*															 *
*************************************************************/

void ticTacToe::outputStats()
{
	cout << " ******Player Stats******" << endl << endl;
	cout << " " << p1Name << endl;
	cout << " | Wins: " << p1Stats[0] << " | Losses: " << p1Stats[1] << " | Draws: " << p1Stats[2] << " |" << endl << endl;
	cout << " " << p2Name << endl;
	cout << " | Wins: " << p2Stats[0] << " | Losses: " << p2Stats[1] << " | Draws: " << p2Stats[2] << " |" << endl << endl;
}

/*************************************************************
*	THIS FUNCTION PLAYS THE TICTACTOE GAME                   *
*															 *
*************************************************************/

void ticTacToe::startGame()
{
	char playAgain = 'y';
	string winner;
	string loser;
	bool isTie = false;
	bool whoStarts;

	outputHeader();
	getNames();
	whoStarts = !whoseFirst();

	while (playAgain == 'y')
	{
		loser = " ";
		cout << " GAME START!" << endl;
		outputBoard();
		for(int i = 0; i < 9; i++)
		{
			makeMove(turn);
			outputBoard();
			winner = isWin();
			
			if (winner != " ") 
			{ 
				if (winner == p1) 
				{ 
					loser = p2; 
					cout << " " << fName1 << " Wins!" << endl;
				}

				else
				{ 
					loser = p1; 
					cout << " " << fName2 << " Wins!" << endl;
				}

				outputBoard();
				break; 
			}

			if (i == 8)
			{
				p1Stats[2] += 1;
				p2Stats[2] += 1;
				cout << " IT'S A TIE!" << endl << endl;
				outputBoard();
				isTie = true;
			}

			switchTurn();
		}
		
		clearBoard();

		if (isTie)
		{
			turn = !whoStarts;
			whoStarts = turn;
			isTie = false;
		}

		if (loser == p1) { turn = true; }
		else if (loser == p2) { turn = false; }

		outputStats();
		cout << " CONTINUE? (y/n) >> ";
		cin >> playAgain;
		cout << endl;
	}
	
	cout << " THANK YOU FOR PLAYING!" << endl;
}