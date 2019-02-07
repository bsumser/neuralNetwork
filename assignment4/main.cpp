#include <iostream>
#include <stdlib.h>
#include <math.h>

class Board
{
	private:
		int size = 0;
		char turn = ' ';
	   	int curRow = 0;
		int curCol = 0;
	public:
		char **boardArray;
		Board(int);

		char getTurn()
		{
			return turn;
		}

		char setTurn(char i)
		{
			turn = i;
		}
		int getSize()
		{
			return size;
		}

		int setSize(int i)
		{
			size = i;
		}
		int getCurCol()
		{
			return curCol;
		}

		int setCurCol(int i)
		{
			curCol = i;
		}
		int getCurRow()
		{
			return curRow;
		}

		int setCurRow(int i)
		{
			curRow = i;
		}

};

Board::Board(int s)
{

	//create dynamic array of pointers
	boardArray = new char* [s];

	size = s;

	//create a row for every pointer
	for(int i = 0; i < s; i++)
	{
		boardArray[i] = new char[s];
	}
}

int startBoard(); //gets the size for class instantiation
void setBoard(Board &othelloBoard); //sets all the spaces to blank
void displayBoard(Board &othelloBoard); //displays current state of board
void getMove(Board &othelloBoard); //receives move from player
bool checkWin(Board &othelloBoard); //checks if board is in win state
bool checkLegal(Board &othelloBoard); //checks if move is legal


int main()
{
	Board othelloBoard(startBoard());
	setBoard(othelloBoard);

	//basic game loop
	do {
	
			//display the board
			displayBoard(othelloBoard);
			
			//get a move for white player
			getMove(othelloBoard);

			//check if move was legal
			checkLegal(othelloBoard);

			//display the board
			displayBoard(othelloBoard);

			//get a move for black player
			getMove(othelloBoard);

			//check if legal
			checkLegal();

			//checking for a win
			checkWin(othelloBoard);
	}while(true);
		
	return 0;
}

int startBoard()
{
	int size;	
	
	std::cout << "welcome to othello, please choose board size " << std::endl;
	std::cin >> size;

	return size;
}

void setBoard(Board &othelloBoard)
{
	int firstPos = ((othelloBoard.getSize() / 2) - 1); //position for starting pieces 
	int secondPos = ((othelloBoard.getSize()) / 2); //position for starting pieces 
	char firstPlayer = 'W'; //sets the first player to go as white
	
	//sets all spaces to blank except starting 4	
	for(int i = 0; i < othelloBoard.getSize(); i++) {
	   for(int j = 0; j < othelloBoard.getSize(); j++) {
			if(i == secondPos && j == secondPos)
	   			othelloBoard.boardArray[i][j] = 'W';
			else if(i == firstPos && j == firstPos) 
				othelloBoard.boardArray[i][j] = 'W';
			else if(i == secondPos && j == firstPos) 
				othelloBoard.boardArray[i][j] = 'B';
			else if(i == firstPos && j == secondPos) 
				othelloBoard.boardArray[i][j] = 'B';
			else
				othelloBoard.boardArray[i][j] = '.';
	   }
	}

	//set white player as current turn
	othelloBoard.setTurn(firstPlayer);
}

void displayBoard(Board &othelloBoard)
{
		std::cout << "displaying the board" << std::endl;

		for(int i = 0; i < othelloBoard.getSize(); i++) {
			for(int j = 0; j < othelloBoard.getSize(); j++) {
					std::cout << othelloBoard.boardArray[i][j];
			}
			std::cout << std::endl;
		}
}

void getMove(Board &othelloBoard)
{
	int userRow;
	int userCol;
	char white = 'W';
	char black = 'B';

	std::cout << "Player " << char(othelloBoard.getTurn()) << " it is your turn" << std::endl;
	std::cout << "Please input your move in format row then column" << std::endl;
	std::cin >> userRow >> userCol;

	//loop until it recieves proper input
	while (userRow < 0 || userRow > 8 || userCol < 0 || userCol > 8)
	{
		std::cout << "please enter integers between 1 and 8" << std::endl;
		std::cout << "Please input your move in format row then column" << std::endl;
		std::cin >> userRow >> userCol;
	}

	//change row and col to array notation
	userRow = userRow - 1;
	userCol = userCol - 1;

	if (othelloBoard.getTurn() == 'W') {
			othelloBoard.boardArray[userRow][userCol] = 'W'; //set space as white
			othelloBoard.setTurn(black); //switch the turn
	}
	else {
			othelloBoard.boardArray[userRow][userCol] = 'B'; //sets the space as black
			othelloBoard.setTurn(white);//switch the turn
	}

}
bool checkWin(Board &othelloBoard)
{
	std::cout << "checking for win" << std::endl;
	return true;
}

bool checkLegal(Board &othelloBoard)
{
	//first check to see if the space is empty

	std::cout << "checking if move is legal" << std::endl;
	return true;
}
