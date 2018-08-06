/*Matheus Bigarelli Dantas da Costa*/
/*Computer engineering student at UTFPR - Brazil*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEIGHT 10
#define WIDTH 10

#define BOMB -1

#define DATA 0
#define STATUS 1


int time ();
void fillBoard (int board[2][HEIGHT][WIDTH], int bombs);
void printBoard (int board[2][HEIGHT][WIDTH]);
void revealBombs (int board[2][HEIGHT][WIDTH]);
bool existAdjacentZeros(int board[2][HEIGHT][WIDTH], int x_guess, int y_guess);
int guessPosition (int board[2][HEIGHT][WIDTH]);
void revealPosition (int board[2][HEIGHT][WIDTH], int x_guess, int y_guess);
void printResult(int end);

int main ()
{
	int bombs = 10, end = 0, row, column;
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
	int row, row_around, column, column_around;

	for (row = 0; row < HEIGHT; row++) {
		for (column = 0; column < WIDTH; column++)
		{
			/*Nothing currently on that position*/
			/*Initializing position at board*/
			board[DATA][row][column] = 0;

			/*Not showed untill guessed*/
			board[STATUS][row][column] = 0;
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
			if (!board[STATUS][row][column])
				printf (" - |");

			/*Guessed positions*/
			else
			{
				/*Show how many bombs are around*/
				if (board[DATA][row][column] > 0)
					printf (" %d |", board[DATA][row][column]);
				/*No bombs around. Print a blank space*/
				else if (board[DATA][row][column] == 0)
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
	int end = 0, x_guess, y_guess;

	printf ("Please guess a position(x,y): ");
	scanf ("%d,%d", &x_guess, &y_guess);

	/*Makes positions be from 1 to LIMIT instead of 0 to LIMIT -1*/
	y_guess--;
	x_guess--;

	/*Found a bomb*//*GAME OVER*/
	//Made by Matheus Bigarelli
	if (board[DATA][y_guess][x_guess] == BOMB)
	{
		revealBombs (board);
		end = 1;
	}

	/*Found nothing*/
	else
		revealPosition (board, x_guess, y_guess);

	return end;
}


/*Reveals all bombs*/
/*Executed only if the player lost the game*/
void revealBombs (int board[2][HEIGHT][WIDTH])
{
	int row, column;

	for (row = 0; row < HEIGHT; row++)
		for (column = 0; column < WIDTH; column++)
			if (board[DATA][row][column] == BOMB)
				board[STATUS][row][column] = 1;
}



void revealPosition (int board[2][HEIGHT][WIDTH], int x_guess, int y_guess)
{
	int row, column;

	/*Reveals the particular position guessed*/
	board[STATUS][y_guess][x_guess] = 1;

	if (existAdjacentZeros(board, x_guess, y_guess))
		revealPosition (board, column, row);
}

bool existAdjacentZeros(int board[2][HEIGHT][WIDTH], int x_guess, int y_guess)
{
	int row, column;
	if (board[DATA][y_guess][x_guess] == 0)
		for (row = -1 + y_guess; row < 2 + y_guess; row++)
			for (column = -1 + x_guess; column < 2 + x_guess; column++)
				if (0 <= row && row < HEIGHT && 0 <= column && column < WIDTH)
					if (board[DATA][row][column] == 0 && board[STATUS][row][column] == 0)
						return true;
	return false;
}

void printResult(int end)
{
	if (!end)
		printf ("Congratulations!! You win!! :D\n\n");
	else
		printf ("Sorry, you lose! :(\n\n");

}

//Made by Matheus Bigarelli
