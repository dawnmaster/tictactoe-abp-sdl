#include "Tictactoe.h"

Tictactoe::Tictactoe(void)
{
	this->ply = 0;
	this->maxPly = 0;
	this->positions = 0;

	this->maxDepth = 9;
}

void Tictactoe::setMaxDepth(int depth)
{
	this->maxDepth = depth;
}

void Tictactoe::setSide(int side)
{
	this->side = side;
}

int Tictactoe::EvalThree(int side, Board &board)
{
	//row wise
	int count;
	for (int row = 0; row < board.size; row++)
	{
		count = 0;
		for (int col = 0; col < board.size; col++)
		{
			if (board.board[row][col] == side)
			{
				count++;
			}
		}
		if (count == 3) return count;
	}

	//col wise
	for (int col = 0; col < board.size; col++)
	{
		count = 0;
		for (int row = 0; row < board.size; row++)
		{
			if (board.board[row][col] == side)
			{
				count++;
			}
		}
		if (count == 3) return count;
	}

	//left-right diagonal
	count = 0;
	for (int i = 0; i < board.size; i++)
	{

		if (board.board[i][i] == side)
		{
			count++;
		}
	}
	if (count == 3) return count;

	//right to left diagonal
	count = 0;
	for (int i = 0; i < board.size; i++)
	{

		if (board.board[i][(board.size - 1) - i] == side)
		{
			count++;
		}
	}
	if (count == 3) return count;
	return 0;
}

int Tictactoe::EvalThreeAllBoard(int side, Board &board)
{
	if (EvalThree(CROSSES, board) == 3)
	{
		return 1;
	}
	if (EvalThree(NOUGHTS, board) == 3)
	{
		return -1;
	}
	return 0;
}

int Tictactoe::minimaxAB(int side, Board &board, int alpha, int beta)
{
	int moveCount = 0;
	Move moveList[9];
	Move move;
	int bestScore = -2;
	int Score = -2;
	Move bestMove;
	if (ply > maxPly) maxPly = ply;
	positions++;

	if (side == CROSSES)
		bestScore = alpha;
	//computer's turn
	else
		bestScore = beta;
	//human's turn

	if (ply > 0)
	{
		Score = EvalThreeAllBoard(side, board);
		if (Score != 0)
		{
			return Score;
		}
		if (ply == maxDepth)
		{
			Score = Eval(side, board);
			return Score;
		}
	}

	//generate moveList and count moves
	for (int row = 0; row < board.size; row++)
	{
		for (int col = 0; col < board.size; col++)
		{
			if (board.board[row][col] == EMPTY)
			{
				moveList[moveCount].row = row;
				moveList[moveCount].col = col;
				moveCount++;
			}
		}
	}

	//generate tree
	for (int index = 0; index < moveCount; index++)
	{
		move = moveList[index];
		board.board[move.row][move.col] = side;
		//printBoard(board);
		ply++;
		if (side == NOUGHTS)
			Score = minimaxAB(CROSSES, board, alpha, beta);
		else
			Score = minimaxAB(NOUGHTS, board, alpha, beta);
		board.board[move.row][move.col] = EMPTY;
		ply--;
		if (Score > bestScore && side == CROSSES)
		{
			alpha = bestScore = Score;
			bestMove = move;
		}
		else if (Score < bestScore && side == NOUGHTS)
		{
			beta = bestScore = Score;
			bestMove = move;
		}
		if (alpha >= beta)
		{
			//std::cout<<"pruned\n";
			return bestScore;
		}
	}

	if (moveCount == 0)
	{
		bestScore = EvalThreeAllBoard(side, board);
	}
	//std::cout<<"\nalpha = "<<alpha<<" "<<"beta = "<<beta<<" ";

	if (ply != 0)
	{
		return bestScore;
	}
	else
	{
		this->bestMove = bestMove;
	}
	return 0;
}

int Tictactoe::Eval(int side, Board &board)
{
	int Not_side = CROSSES;
	if (side == CROSSES)
		Not_side = NOUGHTS;
	return (PossibleWinningLines(board, side) - PossibleWinningLines(board, Not_side));
}

int Tictactoe::PossibleWinningLines(Board &board, int side)
{
	int winningLines = 0;
	bool checkForSideorEmpty;
	//count row wise
	for (int row = 0; row < board.size; row++)
	{
		checkForSideorEmpty = 1;
		for (int col = 0; col < board.size; col++)
		{
			if (board.board[row][col] != side && board.board[row][col] != EMPTY)
			{
				checkForSideorEmpty = 0;
			}
		}
		if (checkForSideorEmpty) winningLines++;
	}

	//count col wise
	for (int col = 0; col < board.size; col++)
	{
		checkForSideorEmpty = 1;
		for (int row = 0; row < board.size; row++)
		{
			if (board.board[row][col] != side && board.board[row][col] != EMPTY)
			{
				checkForSideorEmpty = 0;
			}
		}
		if (checkForSideorEmpty) winningLines++;
	}

	//check diagonally
	//left-right diagonal
	checkForSideorEmpty = 1;
	for (int index = 0; index < board.size; index++)
	{
		if (board.board[index][index] != side && board.board[index][index] != EMPTY)
		{
			checkForSideorEmpty = 0;
		}
	}
	if (checkForSideorEmpty) winningLines++;

	//right-left diagonal
	checkForSideorEmpty = 1;
	for (int index = 0; index < board.size; index++)
	{

		if (board.board[index][(board.size - 1) - index] != side && board.board[index][(board.size - 1) - index] != EMPTY)
		{
			checkForSideorEmpty = 0;
		}
	}
	if (checkForSideorEmpty) winningLines++;
	return winningLines;
}

void Tictactoe::RunGame()
{
	board.size = 3;
	int GameOver = 0;
	initializeBoard(board);

	side = NOUGHTS;
	printBoard(board);
}

void Tictactoe::GetHumanMove(int side, Board &board, int Row, int Col)
{
	int row = Row;
	int col = Col;
	board.board[row][col] = side;
	std::cout << "\n";
	printBoard(board);
	std::cout << "\n";
}

Board &Tictactoe::getBoard()
{
	return board;
}

void Tictactoe::GetComputerMove(int side, Board &board)
{
	this->bestMove.row = this->bestMove.col = -1;
	this->maxPly = 0;
	this->positions = 0;
	int alpha = -4;
	int beta = +4;
	minimaxAB(side, board, alpha, beta);
	board.board[bestMove.row][bestMove.col] = side;
	//std::cout<<bestMove.row<<" "<<bestMove.col;
	printBoard(board);
}

int Tictactoe::GameOver(int side, Board board)
{
	if (EvalThreeAllBoard(side, board) == 1)
	{
		std::cout << "computer wins";
		return 1;
	}
	if (EvalThreeAllBoard(side, board) == -1)
	{
		std::cout << "human wins";
		return -1;
	}
	if (!isEmpty())
	{
		std::cout << "its a draw";
		return 2;
	}
	return 0;
}

int Tictactoe::isEmpty()
{
	for (int row = 0; row < board.size; row++)
	{
		for (int col = 0; col < board.size; col++)
		{
			if (board.board[row][col] == EMPTY)
			{
				return 1;
			}
		}
	}
	return 0;
}

void Tictactoe::initializeBoard(Board &board)
{
	for (int rows = 0; rows < board.size; rows++)
	{
		for (int cols = 0; cols < board.size; cols++)
		{
			board.board[rows][cols] = EMPTY;
		}
	}
}

void Tictactoe::printBoard(Board &board)
{
	std::cout << "\ndepth= " << maxPly << " positions= " << positions;
	std::cout << "\n";
	for (int rows = 0; rows < board.size; rows++)
	{
		for (int cols = 0; cols < board.size; cols++)
		{
			if (board.board[rows][cols] == EMPTY)
			{
				std::cout << "_ ";
				continue;
			}
			if (board.board[rows][cols] == NOUGHTS)
			{
				std::cout << "O ";
				continue;
			}
			if (board.board[rows][cols] == CROSSES)
			{
				std::cout << "X ";
				continue;
			}
		}
		std::cout << "\n";
	}
}

Tictactoe::~Tictactoe(void)
{

}