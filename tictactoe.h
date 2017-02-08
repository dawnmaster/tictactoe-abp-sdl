#pragma once
#include <iostream>

struct Board
{
	int board[3][3];
	int size;
};

struct Move
{
	int row;
	int col;
};

class Tictactoe
{
	enum { EMPTY, NOUGHTS, CROSSES };
	int side;
	int ply;
	int maxPly;
	int positions;
	Move bestMove;
	int maxDepth;
	Board board;

public:
	Tictactoe(void);
	int minimaxAB(int side, Board &board, int alpha, int beta);
	void RunGame();
	void initializeBoard(Board &board);
	void printBoard(Board &board);
	void GetHumanMove(int side, Board &board, int Row, int Col);
	void GetComputerMove(int side, Board &board);
	void setMaxDepth(int depth);
	void setSide(int side);
	int Eval(int side, Board &board);
	int PossibleWinningLines(Board &board, int side);
	int EvalThree(int side, Board &board);
	int EvalThreeAllBoard(int side, Board &board);
	int GameOver(int side, Board board);
	int isEmpty();
	Board &getBoard();
	~Tictactoe(void);
};

