#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <thread>
using namespace std;
//3x3 is the least squares needed for a game.
const int LOWER_LIMIT = 3;
//The screen fits a board of up to 43x43 squares.
const int UPPER_LIMIT = 43;

int MainMenu(int boardSize);
int SafelyInputInteger(int lowerBound, int upperBound, string enterWhat);
void DisplayBoard(char* board[], int boardSize);
bool KingsAreAdjacent(int friendlyRow, int friendlyColumn, int enemyRow, int enemyColumn);
bool RookIsCheckingEnemyKing(int rookRow, int rookColumn, int enemyRow, int enemyColumn, char** board);
bool PiecesOnSameSquare(int rookRow, int rookColumn, int kingRow, int kingColumn);
char ChoosePiece(int boardSize, bool rookOneOnBoard, bool rookTwoOnBoard);

int main()
{
	//Default size.
	int boardSize = 8;
start:
	
	int playerChoice = MainMenu(boardSize);
	//If the player chose to play right away, start the game with the default size.
	if (playerChoice == 1)
	{
		goto newGame;
	}
	else
		//Exit.
		if(playerChoice == 3)
		{
			return 0;
		}
	//Option two means first choose board and then back to the menu.
		else
		
	 boardSize = SafelyInputInteger(LOWER_LIMIT, UPPER_LIMIT, "board size");
	goto start;

newGame:

	//Dynamically initialize 2D array.
	char** board = new char* [boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		board[i] = new char[boardSize];
	}
	// Generate an empty board.
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = '_';
		}
	}

	int enemyKingRow = 0, enemyKingColumn = 0;
	srand(time(0));

	// Populate it with the pieces.
	while (true) {
		enemyKingRow = rand() % boardSize;
		enemyKingColumn = rand() % boardSize;
		//There is no space for the player's king if the board is 3x3 and the enemy king is in the middle.
		if (boardSize == 3 && enemyKingRow == 1 && enemyKingColumn == 1) {
			continue;
		}
		board[enemyKingRow][enemyKingColumn] = 'P';
		break;
	}

	int friendlyKingRow = 0, friendlyKingColumn = 0;

	while (true) {

		friendlyKingRow = rand() % boardSize;
		friendlyKingColumn = rand() % boardSize;

		if (!KingsAreAdjacent(friendlyKingRow, friendlyKingColumn, enemyKingRow, enemyKingColumn))
		{

			board[friendlyKingRow][friendlyKingColumn] = 'K';
			break;

		}

	}

	
	int rookOneRow = 0, rookOneColumn = 0, rookTwoRow = 0, rookTwoColumn = 0;
	while (true) {

		rookOneRow = rand() % boardSize;
		rookOneColumn = rand() % boardSize;

		if ((!RookIsCheckingEnemyKing(rookOneRow, rookOneColumn, enemyKingRow, enemyKingColumn,board))
			&& (!PiecesOnSameSquare(rookOneRow, rookOneColumn, enemyKingRow, enemyKingColumn))
			&& (!PiecesOnSameSquare(rookOneRow, rookOneColumn, friendlyKingRow, friendlyKingColumn)))
		{
			board[rookOneRow][rookOneColumn] = '1';
			break;
		}

	}
	while (true) {
		rookTwoRow = rand() % boardSize;
		rookTwoColumn = rand() % boardSize;

		if ((!RookIsCheckingEnemyKing(rookTwoRow, rookTwoColumn, enemyKingRow, enemyKingColumn,board))
			&& (!PiecesOnSameSquare(rookTwoRow, rookTwoColumn, enemyKingRow, enemyKingColumn))
			&& (!PiecesOnSameSquare(rookTwoRow, rookTwoColumn, friendlyKingRow, friendlyKingColumn))
			&& (!PiecesOnSameSquare(rookTwoRow, rookTwoColumn, rookOneRow, rookOneColumn)))
		{
			board[rookTwoRow][rookTwoColumn] = '2';
			break;
		}

	}


	int moveCounter = 0;
	char pieceToMove;
	int newRow, newColumn;
	bool rookOneOnBoard = true, rookTwoOnBoard = true;
	bool enemyIsChecked = false, enemyCanMove = true;
	int newEnemyRow, newEnemyColumn;
	vector<int> possibleEnemyRows;
	vector<int> possibleEnemyColumns;
	int randomMove = NULL;
	while (true) {
		
		//Check if the game has ended.
		check:
		DisplayBoard(board, boardSize);
		if (enemyIsChecked == true && enemyCanMove == false)
		{
			cout << "You have mated the enemy king in " << moveCounter<< " moves!" << endl;
			
			for (int i = 0; i < boardSize; ++i)
			{
				delete[] board[i];
			}
			delete[] board;

			this_thread::sleep_for(chrono::seconds(5));
			goto start;
		}
		if (enemyIsChecked == false && enemyCanMove == false)
		{
			cout << "Draw by stalemate. " << "You made " << moveCounter << " moves." << endl;
			
			for (int i = 0; i < boardSize; ++i)
			{
				delete[] board[i];
			}
			delete[] board;

			this_thread::sleep_for(chrono::seconds(5));
			goto start;
		}
		if (!rookOneOnBoard && !rookTwoOnBoard)
		{
			cout << "Draw by insufficient material. " << "You made " << moveCounter << " moves." << endl;
			
			for (int i = 0; i < boardSize; ++i)
			{
				delete[] board[i];
			}
			delete[] board;

			this_thread::sleep_for(chrono::seconds(5));
			goto start;
		}

		while (true) 
		{
			// Player move.
			// The upper limit is boardSize-1, because we start counting rows and columns from 0.

			
			 pieceToMove = ChoosePiece(boardSize, rookOneOnBoard, rookTwoOnBoard);
			 newRow = SafelyInputInteger(0, boardSize - 1, "row");
			 newColumn = SafelyInputInteger(0, boardSize - 1, "column");
			//Only go on if the new square is empty, since the player can't capture anything.
			if (board[newRow][newColumn] == '_')
			{
				//King move. Valid if it's not adjacent to the enemy king and if it's adjacent to its old position.
				if (pieceToMove == 'K')
				{
					if (!KingsAreAdjacent(newRow, newColumn, enemyKingRow, enemyKingColumn) 
						&& KingsAreAdjacent(newRow, newColumn, friendlyKingRow, friendlyKingColumn))
					{
						board[newRow][newColumn] = 'K';
						board[friendlyKingRow][friendlyKingColumn] = '_';
						friendlyKingRow = newRow; friendlyKingColumn = newColumn;
						moveCounter++;
						break;
					}
					
				}
				
				// Rook move. Valid if the rook stays either on its row or its column.
				else
				{
					// Rook one.
					if (pieceToMove == '1') 
					{
						if(newRow == rookOneRow || newColumn == rookOneColumn)
						{
							board[newRow][newColumn] = '1';
							board[rookOneRow][rookOneColumn] = '_';
							rookOneRow = newRow; rookOneColumn = newColumn;
							moveCounter++;
							break;
						}
							
						else
						{
							cout << "Invalid move." << endl;
							continue;
						}
					}
					// Rook two.
					else
					{
						if (newRow == rookTwoRow || newColumn == rookTwoColumn)
						{
							board[newRow][newColumn] = '2';
							board[rookTwoRow][rookTwoColumn] = '_';
							rookTwoRow = newRow; rookTwoColumn = newColumn;
							moveCounter++;
							break;
						}
						else
						{
							cout << "Invalid move." << endl;
							continue;
						}
					}
				}
			}
			else
			{
				cout << "Invalid move." << endl;
				continue;
			}
		}

		
		DisplayBoard(board, boardSize);
		// Allow the player to see their move before the computer makes theirs.
		this_thread::sleep_for(chrono::seconds(3));
		//Computer's move.
		while (true)
		{

			if((RookIsCheckingEnemyKing(rookOneRow, rookOneColumn, enemyKingRow, enemyKingColumn,board) && rookOneOnBoard) 
				|| (RookIsCheckingEnemyKing(rookTwoRow, rookTwoColumn, enemyKingRow, enemyKingColumn,board) && rookTwoOnBoard))
			{
				enemyIsChecked = true;
			}
			else
			{
				enemyIsChecked = false;
			}
			// Go through all the squares around the enemy king and check if he can move there.
			for (newEnemyRow = enemyKingRow - 1; newEnemyRow <= enemyKingRow + 1; newEnemyRow++)
			{
				for (newEnemyColumn = enemyKingColumn - 1; newEnemyColumn <= enemyKingColumn + 1 ; newEnemyColumn++)
				{
					//Skip the square he is currently on.
					if (newEnemyRow == enemyKingRow && newEnemyColumn == enemyKingColumn)
					{
						continue;
					}

					//Check if new square is on the board.
					if (newEnemyRow >= 0 && newEnemyRow < boardSize && newEnemyColumn >= 0 && newEnemyColumn < boardSize )
					{	//All other conditions for the square to be valid.
					if (!KingsAreAdjacent(friendlyKingRow, friendlyKingColumn, newEnemyRow, newEnemyColumn)
						&& (!RookIsCheckingEnemyKing(rookOneRow, rookOneColumn, newEnemyRow, newEnemyColumn,board) || !rookOneOnBoard)
						&& (!RookIsCheckingEnemyKing(rookTwoRow, rookTwoColumn, newEnemyRow, newEnemyColumn,board) || !rookTwoOnBoard))
					{
						// Moves where the enemy king can capture a rook are prioritized, as they can lead to a draw.
						if (board[newEnemyRow][newEnemyColumn] != '_')
						{
							if (board[newEnemyRow][newEnemyColumn] == '1')
							{
								rookOneOnBoard = false;
							}
							if (board[newEnemyRow][newEnemyColumn] == '2')
							{
								rookTwoOnBoard = false;
							}
							board[newEnemyRow][newEnemyColumn] = 'P';
							board[enemyKingRow][enemyKingColumn] = '_';
							enemyKingRow = newEnemyRow;
							enemyKingColumn = newEnemyColumn;
							possibleEnemyRows.clear();
							possibleEnemyColumns.clear();
							enemyIsChecked = false;
							//If such a move has been found, it is done directly and the program jumps back to checking the state of the game.
							goto check;

						}
						possibleEnemyRows.push_back(newEnemyRow);
						possibleEnemyColumns.push_back(newEnemyColumn);
					}
					}
				}
			}
			//If there are any available moves that don't involve capturing a rook, the enemy king makes one of them at random.
			if (!possibleEnemyRows.empty() && !possibleEnemyColumns.empty())
			{
				randomMove = rand() % possibleEnemyRows.size();
				board[possibleEnemyRows[randomMove]][possibleEnemyColumns[randomMove]] = 'P';
				board[enemyKingRow][enemyKingColumn] = '_';
				enemyKingRow = possibleEnemyRows[randomMove];
				enemyKingColumn = possibleEnemyColumns[randomMove];
				possibleEnemyRows.clear();
				possibleEnemyColumns.clear();
				break;
			}

			//If no possible moves were saved, that means the enemy king doesn't have any available squares.
			else
			{
				enemyCanMove = false;
				break;
			}
		}

	}
	
	return 0;
}
int MainMenu(int boardSize)
{
	system("cls");
	cout << "Current board size: " << boardSize << endl;
	cout << "1. Start game" << endl;
	cout << "2. Change board size" << endl;
	cout << "3. Exit" << endl;
	int playerChoice = SafelyInputInteger(1, 3, "choice");
	return playerChoice;

}
int SafelyInputInteger(int lowerBound, int upperBound, string enterWhat) {

	int num;
	while (true) {
		cout << "Enter a " << enterWhat << " betwen " << lowerBound << " and " << upperBound << ": ";
		cin >> num;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if ((num >= lowerBound) && (num <= upperBound)) break;
	}
	return num;
}
bool KingsAreAdjacent(int friendlyRow, int friendlyColumn, int enemyRow, int enemyColumn) {

	if (((friendlyRow == enemyRow - 1) || (friendlyRow == enemyRow) || (friendlyRow == enemyRow + 1))
		&& ((friendlyColumn == enemyColumn - 1) || (friendlyColumn == enemyColumn) || (friendlyColumn == enemyColumn + 1)))
	{

		return true;
	}

	return false;
}

bool RookIsCheckingEnemyKing(int rookRow, int rookColumn, int enemyRow, int enemyColumn, char** board) {

	bool row = (rookRow == enemyRow);
	bool column = (rookColumn == enemyColumn);
	int biggerRow, smallerRow, biggerColumn, smallerColumn;
	if (rookRow > enemyRow)
	{
		biggerRow = rookRow;
		smallerRow = enemyRow;
	}
	else
	{
		biggerRow = enemyRow;
		smallerRow = rookRow;
	}
	if (rookColumn > enemyColumn)
	{
		biggerColumn = rookColumn;
		smallerColumn = enemyColumn;
	}
	else
	{
		biggerColumn = enemyColumn;
		smallerColumn = rookColumn;
	}
	//XOR
	if (row ^ column)
	{
		//These two checks are in case the player's king is between a rook and the enemy king.
		if (row)
		{
			for (int i = smallerColumn; i < biggerColumn; i++)
			{
				if (board[rookRow][i] == 'K')
				{
					return false;
				}
			}
			
		}
		if (column)
		{
			for (int i = smallerRow + 1; i < biggerRow; i++)
			{
				if (board[i][rookColumn] == 'K')
				{
					return false;
				}
			}
		}
		return true;
	}
	
		return false;
	
	
}
bool PiecesOnSameSquare(int rookRow, int rookColumn, int kingRow, int kingColumn)
{
	if (rookRow == kingRow && rookColumn == kingColumn)
	{
		return true;
	}
	
	return false;
}
void DisplayBoard(char* board[],int boardSize)
{
	system("cls");
	cout << "K: your king" << endl;
	cout << "P: the enemy king" << endl;
	cout << "1 and 2: your rooks" << endl << endl;

	//Alignment if there are row\column numbers with two digits.
	string whitespace = " ";
	if (boardSize > 10)
	{
		whitespace = "   ";
	}
	
	
	cout << ' ' << whitespace;
	//Column numbers.
	for (int i = 0; i < boardSize; i++)
	{
		cout << i << whitespace;

	}
	cout << endl;
	for (int i = 0; i < boardSize; i++) {
		
		cout << i;
		//Here whitespace is one whitespace longer than "  ", because single digit numbers need more offset.
		if (i <= 9)
		{
			cout << whitespace;
		}
		else
		{
			cout << "  ";
		} 
		
		for (int j = 0; j < boardSize; j++) {
			cout << board[i][j] << whitespace;
			if (j > 9)
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
	cout << endl;
	return;
} 
char ChoosePiece(int boardSize, bool rookOneOnBoard, bool rookTwoOnBoard) {
	string piece = "";
	
	while (true) {
		cout << "Enter the piece you want to move: ";
		cin >> piece;
		if (piece.length() > 1) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (piece[0] == 'k') piece[0] = 'K';
		if (piece[0] == 'K') break;
		if ((piece[0] == '1' && !rookOneOnBoard) ^ (piece[0] == '2' && !rookTwoOnBoard)) 
		{
			cout << "That piece is not on the board anymore." << endl; 
			continue; 
		}
		if (piece[0] == '1' && rookOneOnBoard) break;
		if (piece[0] == '2' && rookTwoOnBoard) break;
		
	}
	return piece[0];
}
