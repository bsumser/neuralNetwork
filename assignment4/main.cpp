#include <iostream>
#include <stdlib.h>

class Board
{
	char board[8][8] = {(' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' '), 
	                   (' ', ' ', ' ',' ',' ',' ',' ',' ')}; 
					     
	int row = 1;
	int column = 1;

};

void displayBoard();
void getMove();
bool checkWin();
bool checkLegal();


int main()
{
	//basic game loop
	do {
	
			//display the board
			displayBoard();
			
			//get a move
			getMove();

			//check if legal
			checkLegal();

			//checking for a win
			checkWin();
	}while(true);
		
	return 0;
}

void displayBoard()
{
		std::cout << "displaying the board" << std::endl;
}

void getMove()
{
	int userRow;
	int userCol;

	std::cout << "Please input your move in format row then column" << std::endl;
	std::cin >> userRow >> userCol;

	//loop until it recieves proper input

	//change row and col to array notation
	userRow = userRow - 1;
	userCol = userCol - 1;

}
bool checkWin()
{
	std::cout << "checking for win" << std::endl;
	return true;
}

bool checkLegal()
{

	std::cout << "checking if move is legal" << std::endl;
	return true;
}
