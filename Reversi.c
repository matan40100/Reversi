#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include<conio.h>
#define ROW 8
#define COLUMN 8

#define PLAYER_ONE 'X' // white
#define PLAYER_TWO '0' //black
#define FREE_SPACE 254
#define AVAILABLE_SPACE 249


/*Last update : 11.1.19 18:45*/
void create_board(char board[ROW + 2][COLUMN + 2]); //Create Board;
void print_board(char board[ROW + 2][COLUMN + 2]); //Print Board
int is_board_full(char board[ROW + 2][COLUMN + 2]); //Check if the board is full(1) or not(0)
int count_X(char board[ROW + 2][COLUMN + 2]); // Return how much time X appers in the board
int count_0(char board[ROW + 2][COLUMN + 2]); //Return how much times 0 appears in the board

void player_one_turn(char board[ROW + 2][COLUMN + 2]); //Player one turn
void player_two_turn(char board[ROW + 2][COLUMN + 2]);//Player two turn

int legal_move(char board[ROW + 2][COLUMN + 2], int row, int column); //Return 1 if the move is legal else return 0

void clear_all_mark(char board[ROW + 2][COLUMN + 2]); //Clear all mark from the board

void mark_player_one(char board[ROW + 2][COLUMN + 2]); // Mark all the spcae player one can use
int row_x(char board[ROW + 2][COLUMN + 2], int row);
int column_x(char board[ROW + 2][COLUMN + 2], int column);
void slant_left_right_x(char board[ROW + 2][COLUMN + 2]);
void slant_right_left_x(char board[ROW + 2][COLUMN + 2]);


void mark_player_two(char board[ROW + 2][COLUMN + 2]);// Mark all the spaces player two can use
int row_0(char board[ROW + 2][COLUMN + 2], int row);
int column_0(char board[ROW + 2][COLUMN + 2], int column);
void slant_left_right_0(char board[ROW + 2][COLUMN + 2]);
void slant_right_left_0(char board[ROW + 2][COLUMN + 2]);

void update_board(char board[ROW + 2][COLUMN + 2], int current_row, int current_column, char symbol);

void red_color();
void player_one_color_magenta();
void player_two_color_cyan();
void available_space_color_yellow();
void reset_color();

int main()
{
	int start_game = 0, test = 0;
	char board[ROW + 2][COLUMN + 2];
	printf("Press 1 to start the game or 0 to exit.\n");
	scanf("%d", &start_game);
	if (start_game)
	{
		player_one_color_magenta();
		printf("Player one symbol: %c\n", PLAYER_ONE);
		reset_color();

		player_two_color_cyan();
		printf("Player two symbol: %c\n", PLAYER_TWO);
		reset_color();

		available_space_color_yellow();
		printf("Available space symbol: %c\n", (char)AVAILABLE_SPACE);
		reset_color();

		create_board(board);
		
		while (is_board_full(board) == 0)
		{
			player_one_turn(board);
			player_two_turn(board);
		}
		
	}
	else
	{
		printf("You choose to exit the game");
	}

	return 0;
}

/*Colors*/
void red_color()
{
	printf("\033[1;31m");
}
void player_one_color_magenta()
{
	printf("\033[0;35m");
}
void player_two_color_cyan()
{
	printf("\033[1;36m");
}
void available_space_color_yellow()
{
	printf("\033[0;33m");
}
void reset_color()
{
	printf("\033[0m");
}


void create_board(char board[ROW+2][COLUMN+2])
{
	  int row = 0, column = 0, counter = 49;
	  for (row = 0; row < ROW + 2; row++) //Fill the matrix with '.'
	  {
		  for (column = 0; column < COLUMN + 2; column++)
		  {
			  board[row][column] = FREE_SPACE;
		  }
	  }

	  for (row = 1; row < ROW + 2; row++) //Fill the row and column with space
	  {
		  board[row][1] = ' ';
		  board[1][row] = ' ';
	  }
 
	  for (column = 2; column < COLUMN + 2; column++) //Numbering the matrix row and column
	  {
		  board[0][column] = counter;
		  board[column][0] = counter;
		  counter++;
	  }

	  board[0][0] = ' ';
	  board[1][0] = ' ';
	  board[0][1] = ' ';
	  
	  board[5][5] = PLAYER_ONE;
	  board[6][6] = PLAYER_ONE;
	  board[5][6] = PLAYER_TWO;
	  board[6][5] = PLAYER_TWO;
}
void print_board(char board[ROW + 2][COLUMN + 2])
{
	printf("\n");
	printf("-------------------------------\n");
	int row = 0, column = 0;
	for (row = 0; row < ROW + 2; row++)
	{
		for (column = 0; column < COLUMN + 2; column++)
		{
			
			if (board[row][column] == (char)PLAYER_ONE)
			{
				player_one_color_magenta();
				printf("%c ", board[row][column]);
				reset_color();
				continue;
			}

			if (board[row][column] == (char)PLAYER_TWO)
			{
				player_two_color_cyan();
				printf("%c ", board[row][column]);
				reset_color();
				continue;
			}
			if (board[row][column] == (char)AVAILABLE_SPACE)
			{
				available_space_color_yellow();
				printf("%c ", board[row][column]);
				reset_color();
				continue;
			}

			printf("%c ", board[row][column]);
			
		}
		printf("\n");
	}

	printf("\n");
	printf(" Score:  X %c %d    0 %c %d\n",175 ,count_X(board), 175, count_0(board));
	printf("-------------------------------\n");
}
int is_board_full(char board[ROW + 2][COLUMN + 2])
{
	int row, column;
	for (row = 2; row < COLUMN+2; row++)
	{
		for (column = 2; column < COLUMN + 2; column++)
		{
			if (board[row][column] == (char)FREE_SPACE)
			{
				return 0; // 0 if the board dont full	
			}
		}
	}
	return 1; // 1 if the board full

}
int count_X(char board[ROW + 2][COLUMN + 2])
{
	int row, column,counter = 0;
	for (row = 2; row < COLUMN + 2; row++)
	{
		for (column = 2; column < COLUMN + 2; column++)
		{
			if (board[row][column] == PLAYER_ONE)
			{
				counter++;
			}
		}
	}
	return counter;

}
int count_0(char board[ROW + 2][COLUMN + 2])
{
	int row, column, counter = 0;
	for (row = 2; row < COLUMN + 2; row++)
	{
		for (column = 2; column < COLUMN + 2; column++)
		{
			if (board[row][column] == PLAYER_TWO)
			{
				counter++;
			}
		}
	}
	return counter;

}


void player_one_turn(char board[ROW + 2][COLUMN + 2])
{
	mark_player_one(board);
	print_board(board);
	int row_number = 0, column_number = 0;
	player_one_color_magenta();
	printf("Player 1(X): enter row number:\n");
	scanf("%d", &row_number);
	printf("Player 1(X): enter colunm number:\n");
	scanf("%d", &column_number);
	reset_color();

	if (legal_move(board, row_number, column_number) == 1)
	{
		board[row_number + 1][column_number + 1] = PLAYER_ONE;
		clear_all_mark(board);
		update_board(board, row_number + 1, column_number + 1, PLAYER_ONE);
		mark_player_two(board);
		print_board(board);
	}
	else
	{
		red_color();
		printf("\n");
		printf("Invalid move !\n");
		printf("Try again\n");
		reset_color();
		player_one_turn(board);
	}

	
	
	
}
void player_two_turn(char board[ROW + 2][COLUMN + 2])
{
	int row_number = 0, column_number = 0;
	player_two_color_cyan();
	printf("Player 2(0): enter row number:\n");
	scanf("%d", &row_number);
	printf("Player 2(0): enter colunm number:\n");
	scanf("%d", &column_number);
	reset_color();


	if (legal_move(board, row_number, column_number) == 1)
	{
		board[row_number + 1][column_number + 1] = PLAYER_TWO;
		update_board(board, row_number + 1, column_number + 1, PLAYER_TWO);
		print_board(board);
		clear_all_mark(board);;
	}
	else
	{
		red_color();
		printf("\n");
		printf("Invalid move !\n");
		printf("Try again\n");
		printf("\n");
		reset_color();
		player_two_turn(board);
	}
	

}
int legal_move(char board[ROW + 2][COLUMN + 2], int row, int column)
{
	if (board[row + 1][column + 1] == (char)AVAILABLE_SPACE)
	{
		return 1;
	}
	return 0;
}

void clear_all_mark(char board[ROW + 2][COLUMN + 2])
{
	int row, column;
	for (row = 2; row < ROW + 2; row++) 
	{
		for (column = 2; column < COLUMN + 2; column++)
		{
			if(board[row][column] == (char)AVAILABLE_SPACE)
			{
				board[row][column] = FREE_SPACE;
			}
		}
	}
}

/*Marks available space for player two*/
void mark_player_one(char board[ROW + 2][COLUMN + 2])
{
	int row_number, column_number, currect_row;

	for (column_number = 2; column_number < COLUMN + 2; column_number++)
	{
		
		if (column_x(board, column_number))
		{	
			for (row_number = 2; row_number < ROW + 2; row_number++)
			{
				if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number + 1][column_number] == (char)FREE_SPACE)
				{
					board[row_number +1 ][column_number] = AVAILABLE_SPACE;
					break;
					
				}
			}
		}
	}

	for (column_number = 2; column_number < COLUMN + 2; column_number++)
	{
		if (column_x(board, column_number))
		{
			
			for (row_number = ROW + 2; row_number > 2; row_number --)
			{
				if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number - 1][column_number] == (char)FREE_SPACE)
				{
					board[row_number - 1][column_number] = AVAILABLE_SPACE;
					break;

				}
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		if (row_x(board, row_number))
		{
			for (column_number = 2; column_number < COLUMN+ 2; column_number++)
			{
				if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number][column_number + 1] == (char)FREE_SPACE)
				{
					board[row_number][column_number + 1] = AVAILABLE_SPACE;
					break;
				}
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		if (row_x(board, row_number))
		{
			for (column_number = COLUMN + 2; column_number > 2; column_number--)
			{
				if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number][column_number - 1] == (char)FREE_SPACE)
				{
					board[row_number][column_number - 1] = AVAILABLE_SPACE;
					break;
				}
			}
		}
	}

	slant_left_right_x(board);
	slant_right_left_x(board);
}
int row_x(char board[ROW + 2][COLUMN + 2], int row)
{
	int column;
	for (column = 2; column < COLUMN + 2; column++)
	{
		if (board[row][column] == PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int column_x(char board[ROW + 2][COLUMN + 2], int column)
{
	int row;
	for (row = 2; row < ROW + 2; row++)
	{
		if (board[row][column] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
void slant_left_right_x(char board[ROW + 2][COLUMN + 2])
{
	int current_row = 0, current_column = 0;
	int row_number = 0, column_number = 0;
	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row++;
					current_column++;
					if (board[current_row][current_column] == (char)PLAYER_TWO && board[current_row + 1][current_column + 1] == (char)FREE_SPACE)
					{
						board[current_row + 1][current_column + 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column < COLUMN + 2 || current_row < ROW + 2);				
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row--;
					current_column--;
					if (board[current_row][current_column] == (char)PLAYER_TWO && board[current_row - 1][current_column - 1] == (char)FREE_SPACE)
					{
						board[current_row - 1][current_column - 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column > 1 || current_row > 1);
			}
		}
	}





}
void slant_right_left_x(char board[ROW + 2][COLUMN + 2])
{
	int current_row = 0, current_column = 0;
	int row_number = 0, column_number = 0;
	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row++;
					current_column--;
					if (board[current_row][current_column] == (char)PLAYER_TWO && board[current_row + 1][current_column - 1] == (char)FREE_SPACE)
					{
						board[current_row + 1][current_column - 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column > 1 || current_row < ROW + 2);
			}
		}
	}


	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row--;
					current_column++;
					if (board[current_row][current_column] == (char)PLAYER_TWO && board[current_row - 1][current_column + 1] == (char)FREE_SPACE)
					{
						board[current_row - 1][current_column + 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column < COLUMN + 2 || current_row > 1);
			}
		}
	}


	
}

/*Marks available space for player two*/
void mark_player_two(char board[ROW + 2][COLUMN + 2])
{
	int row_number, column_number, currect_row;

	for (column_number = 2; column_number < COLUMN + 2; column_number++)
	{

		if (column_0(board, column_number))
		{
			for (row_number = 2; row_number < ROW + 2; row_number++)
			{
				if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number + 1][column_number] == (char)FREE_SPACE)
				{
					board[row_number + 1][column_number] = AVAILABLE_SPACE;
					break;

				}
			}
		}
	}

	for (column_number = 2; column_number < COLUMN + 2; column_number++)
	{
		if (column_0(board, column_number))
		{

			for (row_number = ROW + 2; row_number > 2; row_number--)
			{
				if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number - 1][column_number] == (char)FREE_SPACE)
				{
					board[row_number - 1][column_number] = AVAILABLE_SPACE;
					break;

				}
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		if (row_0(board, row_number))
		{
			for (column_number = 2; column_number < COLUMN + 2; column_number++)
			{
				if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number][column_number + 1] == (char)FREE_SPACE)
				{
					board[row_number][column_number + 1] = AVAILABLE_SPACE;
					break;
				}
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		if (row_0(board, row_number))
		{
			for (column_number = COLUMN + 2; column_number > 2 ; column_number--)
			{
				if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number][column_number -1] == (char)FREE_SPACE)
				{
					board[row_number][column_number - 1] = AVAILABLE_SPACE;
					break;
				}
			}
		}
	}
	
	slant_left_right_0(board);
	slant_right_left_0(board);
	
}
int row_0(char board[ROW + 2][COLUMN + 2], int row)
{
	int column;
	for (column = 2; column < COLUMN + 2; column++)
	{
		if (board[row][column] == PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int column_0(char board[ROW + 2][COLUMN + 2], int column)
{
	int row;
	for (row = 2; row < ROW + 2; row++)
	{
		if (board[row][column] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
void slant_left_right_0(char board[ROW + 2][COLUMN + 2])
{
	int current_row = 0, current_column = 0;
	int row_number = 0, column_number = 0;
	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row++;
					current_column++;
					if (board[current_row][current_column] == (char)PLAYER_ONE && board[current_row + 1][current_column + 1] == (char)FREE_SPACE)
					{
						board[current_row + 1][current_column + 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column < COLUMN + 2 || current_row < ROW + 2);
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row--;
					current_column--;
					if (board[current_row][current_column] == (char)PLAYER_ONE && board[current_row - 1][current_column - 1] == (char)FREE_SPACE)
					{
						board[current_row - 1][current_column - 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column > 1 || current_row > 1);
			}
		}
	}
}
void slant_right_left_0(char board[ROW + 2][COLUMN + 2])
{
	int current_row = 0, current_column = 0;
	int row_number = 0, column_number = 0;
	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row++;
					current_column--;
					if (board[current_row][current_column] == (char)PLAYER_ONE && board[current_row + 1][current_column - 1] == (char)FREE_SPACE)
					{
						board[current_row + 1][current_column - 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column > 1 || current_row < ROW + 2);
			}
		}
	}

	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				current_row = row_number;
				current_column = column_number;
				do
				{
					current_row--;
					current_column++;
					if (board[current_row][current_column] == (char)PLAYER_ONE && board[current_row - 1][current_column + 1] == (char)FREE_SPACE)
					{
						board[current_row - 1][current_column + 1] = (char)AVAILABLE_SPACE;
						break;
					}

				} while (current_column < COLUMN + 2 || current_row > 1);
			}
		}
	}
}


void update_board(char board[ROW + 2][COLUMN + 2], int current_row, int current_column,char symbol)
{
	int row_number, column_number;
	
	if (symbol == 'X')
	{
		/*Row up*/
		for (row_number = current_row; row_number > 2; row_number--)
		{
			if (board[row_number][current_column] == (char)PLAYER_TWO && board[row_number - 1][current_column] == (char)PLAYER_ONE)
			{
				board[row_number][current_column] = PLAYER_ONE;
			}
		}

		/*Row down*/
		for (row_number = current_row; row_number < ROW + 2; row_number++)
		{
			if (board[row_number][current_column] == (char)PLAYER_TWO && board[row_number + 1][current_column] == (char)PLAYER_ONE)
			{
				board[row_number][current_column] = PLAYER_ONE;
			}
		}

		/*Column left*/
		for (column_number = current_column; column_number > 2; column_number--)
		{
			if (board[current_row][column_number] == (char)PLAYER_TWO && board[current_row][column_number - 1] == (char)PLAYER_ONE)
			{
				board[current_row][column_number] = PLAYER_ONE;
			}

		}
		/*Column right*/
		for (column_number = current_column; column_number < COLUMN + 2; column_number++)
		{
			if (board[current_row][column_number] == (char)PLAYER_TWO && board[current_row][column_number + 1] == (char)PLAYER_ONE)
			{
				board[current_row][column_number] = PLAYER_ONE;
			}

		}
		
		/*Slant(/) left to right down */
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number + 1][column_number - 1] == (char)PLAYER_ONE)
			{
				board[row_number][column_number] = PLAYER_ONE;
			}
			row_number++;
			column_number--;
		} while (row_number < ROW + 2 || column_number > 2);

		/*Slant(/) left to right up */
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number - 1][column_number + 1] == (char)PLAYER_ONE)
			{
				board[row_number][column_number] = PLAYER_ONE;
			}
			row_number--;
			column_number++;
		} while (row_number > 2 || column_number < COLUMN +2);	

		/*Slant(\) right to left down */
		row_number = current_row;
		column_number = current_column;
		do 
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number + 1][column_number + 1] == (char)PLAYER_ONE)
			{
				board[row_number][column_number] = PLAYER_ONE;
			}
			row_number++;
			column_number++;
		} while (row_number < ROW + 2 || column_number < COLUMN + 2);

		/*Slant(\) right to left up*/
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number - 1][column_number - 1] == (char)PLAYER_ONE)
			{
				board[row_number][column_number] = PLAYER_ONE;
			}
			row_number--;
			column_number--;
		} while (row_number > 2 || column_number > 2);
	}
	else if (symbol == '0')
	{
		/*Row up*/
		for (row_number = current_row; row_number > 2; row_number--)
		{
			if (board[row_number][current_column] == (char)PLAYER_ONE && board[row_number - 1][current_column] == (char)PLAYER_TWO)
			{
				board[row_number][current_column] = PLAYER_TWO;
			}
		}

		/*Row down*/
		for (row_number = current_row; row_number < ROW + 2; row_number++)
		{
			if (board[row_number][current_column] == (char)PLAYER_ONE && board[row_number + 1][current_column] == (char)PLAYER_TWO)
			{
				board[row_number][current_column] = PLAYER_TWO;
			}
		}

		/*Column left*/
		for (column_number = current_column; column_number > 2; column_number--)
		{
			if (board[current_row][column_number] == (char)PLAYER_ONE && board[current_row][column_number - 1] == (char)PLAYER_TWO)
			{
				board[current_row][column_number] = PLAYER_TWO;
			}

		}
		
		/*Column right*/
		for (column_number = current_column; column_number < COLUMN + 2; column_number++)
		{
			if (board[current_row][column_number] == (char)PLAYER_ONE && board[current_row][column_number + 1] == (char)PLAYER_TWO)
			{
				board[current_row][column_number] = PLAYER_TWO;
			}

		}

		/*Slant(/) left to right down */
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number + 1][column_number - 1] == (char)PLAYER_TWO)
			{
				board[row_number][column_number] = PLAYER_TWO;
			}
			row_number++;
			column_number--;
		} while (row_number < ROW + 2 || column_number > 2);

		/*Slant(/) left to right up */
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number - 1][column_number + 1] == (char)PLAYER_TWO)
			{
				board[row_number][column_number] = PLAYER_TWO;
			}
			row_number--;
			column_number++;
		} while (row_number > 2 || column_number < COLUMN + 2);

		/*Slant(\) right to left down */
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number + 1][column_number + 1] == (char)PLAYER_TWO)
			{
				board[row_number][column_number] = PLAYER_TWO;
			}
			row_number++;
			column_number++;
		} while (row_number < ROW + 2 || column_number < COLUMN + 2);

		/*Slant(\) right to left up*/
		row_number = current_row;
		column_number = current_column;
		do
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number - 1][column_number - 1] == (char)PLAYER_TWO)
			{
				board[row_number][column_number] = PLAYER_TWO;
			}
			row_number--;
			column_number--;
		} while (row_number > 2 || column_number > 2);
	}
}