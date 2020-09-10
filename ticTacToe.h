#include <iostream>
#include <string>
using namespace std;


class ticTacToe
{
private:
	string p1Name;
	string p2Name;
	string fName1;
	string fName2;
	string lName1;
	string lName2;
	string p1;
	string p2;
	string board[9];
	int p1Stats[3];
	int p2Stats[3];
	bool turn;
public:
	ticTacToe();

	void setp1Name(string);
	void setp2Name(string);
	void setfName1(string);
	void setfName2(string);
	void setlName1(string);
	void setlName2(string);
	void setp1(string);
	void setp2(string);
	void setboard(string*);
	void setp1Stats(int*);
	void setp2Stats(int*);
	void setturn(bool);

	string getp1Name();
	string getp2Name();
	string getfName1();
	string getfName2();
	string getlName1();
	string getlName2();
	string getp1();
	string getp2();
	string* getboard();
	int* getp1Stats();
	int* getp2Stats();
	bool getturn();

	void outputHeader();
	void getNames();
	bool whoseFirst();
	void outputBoard();
	string isWin();
	void makeMove(bool);
	void switchTurn();
	void clearBoard();
	void outputStats();
	void startGame();

};

