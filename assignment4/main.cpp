#include <iostream>
#include <stdlib.h>

using namespace std;

class Board
{
	char board[8][8] =((' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ',)); 
					     
	int row = 1;
	int column = 1;

}

void displayBoard()
{
	cout << "checking if the move is legal" << endl;
}

void getMove()
{
		cout << "Please input your move in format row then column" << endl;
		cin << row << col;

		//change row and col to array notation
		row = row - 1;
		col = col - 1;

}
bool checkWin()
{
	cout << "checking for win" << endl;
}

bool checkLegal()
{

	cout << "checking if move is legal" << endl;
}

int main()
{
	//basic game loop
	
	//display the board
	displayBoard();
	
	//get a move
	getMove();

	//check if legal
	checkLegal();
		
	return 0;
}
