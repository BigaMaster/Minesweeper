/*Matheus Bigarelli Dantas da Costa*/
/*Computer engineering student at UTFPR - Brazil*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEIGHT 10
#define WIDTH 10


#define DATA 0
#define STATUS 1

#define SHOWING_SLOT 1
#define NOT_SHOWING_SLOT 0

#define BOMB -1
#define NO_BOMB 0

typedef struct
{
	int x;
	int y;
} Point;


int time ();
void fillBoard (int board[2][HEIGHT][WIDTH], int bombs);
void printBoard (int board[2][HEIGHT][WIDTH]);
void revealBombs (int board[2][HEIGHT][WIDTH]);
int guessPosition (int board[2][HEIGHT][WIDTH]);
void revealPosition (int board[2][HEIGHT][WIDTH], Point guessedPosition);
bool isAdjacentZeroWithinBoundaries(int board[2][HEIGHT][WIDTH], int row, int column);
Point createNewPoint(int x, int y);
void printResult(int end);

int main ()
{
	int bombs = 5, end = 0, row, column;
	/*Two matrixes, one with whether the "content" of the position may be showed or not and the other
	with the bombs and the amount of bombs around a certain position*/
	int board[2][HEIGHT][WIDTH];

	srand(time(NULL));

	fillBoard (board, bombs);

	while (!end)
	{
		printBoard (board);
		end = guessPosition (board);
	}

	printBoard (board);

	printResult(end);

	return 0;
}


void fillBoard (int board[2][HEIGHT][WIDTH], int bombs)
{
	Point point, adjacentPoint;

	int row, row_around, column, column_around;

	for (row = 0; row < HEIGHT; row++) {
		for (column = 0; column < WIDTH; column++)
		{
			/*Nothing currently on that position*/
			/*Initializing position at board*/
			board[DATA][row][column] = NO_BOMB;

			/*Not showed untill guessed*/
			board[STATUS][row][column] = NOT_SHOWING_SLOT;
		}
	}

	while (bombs)
	{
		do
		{
			row = rand () % HEIGHT;
			column = rand () % WIDTH;
		} while (board[DATA][row][column] == BOMB);

		board[DATA][row][column] = BOMB;

		for (row_around = -1 + row; row_around < 2 + row; row_around++)
			for (column_around = -1 + column; column_around < 2 + column; column_around++)
				if (0 <= row_around && row_around < HEIGHT && 0 <= column_around && column_around < WIDTH)
					if (board[DATA][row_around][column_around] != BOMB)
						board[DATA][row_around][column_around]++;

		bombs--;
	}
}


void printBoard (int board[2][HEIGHT][WIDTH])
{
	int row, column;

	system ("clear");

	for (row = 0; row < HEIGHT; row++)
	{
		for (column = 0; column < WIDTH; column++)
			printf ("====");
		printf ("=\n|");

		for (column = 0; column < WIDTH; column++)
		{
			/*Position not guessed*/
			if (board[STATUS][row][column] == NOT_SHOWING_SLOT)
				printf (" - |");

			/*Guessed positions*/
			else
			{
				/*Show how many bombs are around*/
				if (board[DATA][row][column] > NO_BOMB)
					printf (" %d |", board[DATA][row][column]);
				/*No bombs around. Print a blank space*/
				else if (board[DATA][row][column] == NO_BOMB)
					printf ("   |");
				/*Guessed a bomb. Lost the game. Prints all bombs*/
				else
					printf(" X |");
			}
		}

		printf ("\n");
	}

	for (column = 0; column < WIDTH; column++)
		printf ("====");
	printf ("=\n");
}


int guessPosition (int board[2][HEIGHT][WIDTH])
{
	int end = 0;

	Point guessedPosition;

	printf ("Please guess a position (x,y): ");
	scanf ("%d,%d", &guessedPosition.x, &guessedPosition.y);

	/*Makes positions be from 1 to LIMIT instead of 0 to LIMIT -1*/
	guessedPosition.y--;
	guessedPosition.x--;

	/*Found a bomb*/
	/*GAME OVER*/
	//Made by Matheus Bigarelli
	if (board[DATA][guessedPosition.y][guessedPosition.x] == BOMB)
	{
		revealBombs (board);
		end = 1;
	}

	/*Found nothing*/
	else
		revealPosition (board, guessedPosition);

	return end;
}


/*Executed only if the player lost the game*/
void revealBombs (int board[2][HEIGHT][WIDTH])
{
	int row, column;

	for (row = 0; row < HEIGHT; row++)
		for (column = 0; column < WIDTH; column++)
			if (board[DATA][row][column] == BOMB)
				board[STATUS][row][column] = SHOWING_SLOT;
}



void revealPosition (int board[2][HEIGHT][WIDTH], Point guessedPosition)
{
	int row, column;

	/*Reveals the particular position guessed*/
	board[STATUS][guessedPosition.y][guessedPosition.x] = SHOWING_SLOT;


	if (board[DATA][guessedPosition.y][guessedPosition.x] == NO_BOMB)
		for (row = -1 + guessedPosition.y; row < 2 + guessedPosition.y; row++)
			for (column = -1 + guessedPosition.x; column < 2 + guessedPosition.x; column++)
				if (isAdjacentZeroWithinBoundaries(board, row, column))
				{
					Point newRevealedPosition = createNewPoint(column, row);
					revealPosition (board, newRevealedPosition);
				}
}

bool isAdjacentZeroWithinBoundaries(int board[2][HEIGHT][WIDTH], int row, int column)
{
	if (0 <= row && row < HEIGHT && 0 <= column && column < WIDTH)
		if (board[DATA][row][column] == NO_BOMB && board[STATUS][row][column] == NOT_SHOWING_SLOT)
			return true;
	return false;
}

Point createNewPoint(int x, int y)
{
	Point newPoint;
	newPoint.x = x;
	newPoint.y = y;
	return newPoint;
}

void printResult(int end)
{
	if (!end)
		printf ("Congratulations!! You win!! :D\n\n");
	else
		printf ("Sorry, you lose! :(\n\n");

}

//Made by Matheus Bigarelli
