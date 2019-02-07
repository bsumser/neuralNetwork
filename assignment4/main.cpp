#include <iostream>
#include <stdlib.h>

class Board
{
	private:
		int size = 0;
	public:
		char **boardArray; 
		Board(int);

		int getSize()
		{
			return size;
		}

		int setSize(int i)
		{
			size = i;
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
void clearBoard(Board &othelloBoard); //sets all the spaces to blank
void displayBoard(Board &othelloBoard); //displays current state of board
void getMove(); //receives move from player
bool checkWin(); //checks if board is in win state
bool checkLegal(); //checks if move is legal


int main()
{
	Board othelloBoard(startBoard());
	clearBoard(othelloBoard);

	//basic game loop
	do {
	
			//display the board
			displayBoard(othelloBoard);
			
			//get a move
			getMove();

			//check if legal
			checkLegal();

			//checking for a win
			checkWin();
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

void clearBoard(Board &othelloBoard)
{
	for(int i = 0; i < othelloBoard.getSize(); i++) {
	   for(int j = 0; j < othelloBoard.getSize(); j++) {
	   		othelloBoard.boardArray[i][j] = '.';
	   }
	}
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

void getMove()
{
	int userRow;
	int userCol;

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
