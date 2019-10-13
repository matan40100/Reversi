#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include<conio.h>
#define ROW 8
#define COLUMN 8

#define PLAYER_ONE 'X' 
#define PLAYER_TWO '0' 
#define FREE_SPACE 254
#define AVAILABLE_SPACE 249

/*Last update : 13.10.19 19:17*/
void create_board(char board[ROW + 2][COLUMN + 2]); //Create Board;
void print_board(char board[ROW + 2][COLUMN + 2]); //Print Board
int is_board_full(char board[ROW + 2][COLUMN + 2]); //Check if the board is full(1) or not(0)
int count_X(char board[ROW + 2][COLUMN + 2]); // Return how much time X appers in the board
int count_0(char board[ROW + 2][COLUMN + 2]); //Return how much times 0 appears in the board
void print_winner(char board[ROW + 2][COLUMN + 2]); //Print the winner and the final board

void player_one_turn(char board[ROW + 2][COLUMN + 2]); //Player one turn
void player_two_turn(char board[ROW + 2][COLUMN + 2]);//Player two turn

int legal_move(char board[ROW + 2][COLUMN + 2], int row, int column); //Return 1 if the move is legal else return 0
int is_available_space(char board[ROW + 2][COLUMN + 2]); // Return 1 if there is available space else return 0
void clear_all_mark(char board[ROW + 2][COLUMN + 2]); //Clear all mark from the board

void mark_available_space_for_player(char board[ROW + 2][COLUMN + 2], int symbol); // Mark all the spcae for player one and two

void update_board_x(char board[ROW + 2][COLUMN + 2], int current_row, int current_column, char symbol); // Changes the board according to where I placed the mark for player one
void update_board_0(char board[ROW + 2][COLUMN + 2], int current_row, int current_column, char symbol); // Changes the board according to where I placed the mark for player two

/*Check if there is x in row / column / slant*/
int is_x_row_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); //Row down
int is_x_row_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Row up
int is_x_column_right(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Column right
int is_x_column_left(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Column left
int is_x_slant_left_right_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (/)UP
int is_x_slant_left_right_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (/)DOWN
int is_x_slant_right_left_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column);// (\)UP
int is_x_slant_right_left_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (\)down

/*Check if there is 0 in row / column / slant*/
int is_0_row_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); //Row down
int is_0_row_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Row up
int is_0_column_right(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Column right
int is_0_column_left(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Column left
int is_0_slant_left_right_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (/)UP
int is_0_slant_left_right_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (/)DOWN
int is_0_slant_right_left_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (\)UP
int is_0_slant_right_left_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (\)down

/*Check if there is free space in row / column / slant*/
int is_free_space_row_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); //Row down
int is_free_space_row_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Row up
int is_free_space_column_right(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Column right
int is_free_space_column_left(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // Column left
int is_free_space_slant_left_right_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (/)UP
int is_free_space_slant_left_right_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (/)DOWN
int is_free_space_slant_right_left_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (\)UP
int is_free_space_slant_right_left_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column); // (\)down

//color
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
		print_winner(board);

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


void create_board(char board[ROW + 2][COLUMN + 2])
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
	printf(" Score:  X %c %d    0 %c %d\n", 175, count_X(board), 175, count_0(board));
	printf("-------------------------------\n");
}
int is_board_full(char board[ROW + 2][COLUMN + 2])
{
	int row, column;
	for (row = 2; row < COLUMN + 2; row++)
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
	int row, column, counter = 0;
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
void print_winner(char board[ROW + 2][COLUMN + 2])
{
	int score_player_one = count_X(board);
	int score_player_two = count_0(board);

	if (score_player_one > score_player_two)
	{
		red_color();
		printf("Final Board\n");
		reset_color();
		print_board(board);
		red_color();
		printf("Winner: ");
		reset_color();
		player_one_color_magenta();
		printf("Player 1(X)\n");
		reset_color();
	}
	else if (score_player_one < score_player_two)
	{
		red_color();
		printf("Final Board\n");
		reset_color();
		print_board(board);
		red_color();
		printf("Winner: ");
		reset_color();
		player_two_color_cyan();
		printf("Player 2(0)\n");
		reset_color();

	}
	else
	{
		red_color();
		printf("Final Board\n");
		reset_color();
		print_board(board);
		red_color();
		printf("Draw");
		reset_color();
	}
}
int is_available_space(char board[ROW + 2][COLUMN + 2])
{
	int row_number, column_number;
	for (row_number = 2; row_number < ROW + 2; row_number++)
	{
		for (column_number = 2; column_number < COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)AVAILABLE_SPACE)
			{
				return 1;
			}
		}
	}
	return 0;
}

void player_one_turn(char board[ROW + 2][COLUMN + 2])
{
	if (!is_board_full)
	{
		return;
	}
	mark_available_space_for_player(board, PLAYER_ONE);
	if (!is_available_space(board))
	{
		int answer = 0;
		red_color();
		printf("Player 1(X): You dont have available space, Press 1 to skip your turn\n");
		scanf("%d", &answer);
		reset_color();
		return;
	}
	print_board(board);
	int row_number = 0, column_number = 0;
	player_one_color_magenta();
	printf("Player 1(X): enter row number:\n");
	scanf("%d", &row_number);
	printf("Player 1(X): enter colunm number:\n");
	scanf("%d", &column_number);
	reset_color();

	if (row_number == 999)
	{
		red_color();
		printf("Player one(X) choose to exit");
		exit();
	}

	if (legal_move(board, row_number, column_number))
	{
		board[row_number + 1][column_number + 1] = PLAYER_ONE;
		clear_all_mark(board);
		update_board_x(board, row_number + 1, column_number + 1, PLAYER_ONE);

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
	if (!is_board_full)
	{
		return;
	}
	mark_available_space_for_player(board, PLAYER_TWO);
	if (!is_available_space(board))
	{
		int answer = 0;
		red_color();
		printf("Player 2(0): You dont have available space, Press 1 to skip your turn\n");
		scanf("%d", &answer);
		reset_color();
		return;
	}
	print_board(board);
	int row_number = 0, column_number = 0;
	player_two_color_cyan();
	printf("Player 2(0): enter row number:\n");
	scanf("%d", &row_number);
	printf("Player 2(0): enter colunm number:\n");
	scanf("%d", &column_number);
	reset_color();

	if (row_number == 999)
	{
		red_color();
		printf("Player two(0) choose to exit");
		exit();
	}

	if (legal_move(board, row_number, column_number) == 1)
	{
		board[row_number + 1][column_number + 1] = PLAYER_TWO;
		clear_all_mark(board);
		update_board_0(board, row_number + 1, column_number + 1, PLAYER_TWO);



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
			if (board[row][column] == (char)AVAILABLE_SPACE)
			{
				board[row][column] = FREE_SPACE;
			}
		}
	}
}
void mark_available_space_for_player(char board[ROW + 2][COLUMN + 2], int symbol)
{
	int row_number, column_number;

	int current_row = 0, current_column = 0;
	int count = 0;
	/*Row down*/
	for (column_number = 2; column_number <= COLUMN + 2; column_number++)
	{
		for (row_number = 2; row_number <= ROW + 2; row_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				/*Player one*/
				if (symbol == PLAYER_ONE)
				{
					current_row = row_number;
					while (current_row < ROW + 2)
					{
						current_row++;
						if (board[current_row][column_number] == (char)FREE_SPACE && board[current_row - 1][column_number] == (char)PLAYER_TWO)
						{
							board[current_row][column_number] = AVAILABLE_SPACE;
							break;
						}

					}
				}
			}

			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				/*Player two*/
				if (symbol == PLAYER_TWO)
				{
					current_row = row_number;
					while (current_row < ROW + 2)
					{
						current_row++;
						if (board[current_row][column_number] == (char)FREE_SPACE && board[current_row - 1][column_number] == (char)PLAYER_ONE)
						{
							board[current_row][column_number] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}
		}
	}

	/*Row up*/
	for (column_number = 2; column_number <= COLUMN + 2; column_number++)
	{
		for (row_number = ROW + 2; row_number >= 2; row_number--)
		{
			/*Player one*/
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				if (symbol == PLAYER_ONE)
				{
					current_row = row_number;
					while (current_row >= 2)
					{
						current_row--;
						if (board[current_row][column_number] == (char)FREE_SPACE && board[current_row + 1][column_number] == (char)PLAYER_TWO)
						{
							board[current_row][column_number] = AVAILABLE_SPACE;
							break;
						}

					}
				}
			}
			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_row = row_number;
					while (current_row >= 2)
					{
						current_row--;
						if (board[current_row][column_number] == (char)FREE_SPACE && board[current_row + 1][column_number] == (char)PLAYER_ONE)
						{
							board[current_row][column_number] = AVAILABLE_SPACE;
							break;
						}

					}
				}
			}
		}
	}

	/*Column right*/
	for (row_number = 2; row_number <= COLUMN + 2; row_number++)
	{
		for (column_number = 2; column_number <= COLUMN + 2; column_number++)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				/*Player one*/
				if (symbol == PLAYER_ONE)
				{
					current_column = column_number;
					while (current_column < COLUMN + 2)
					{
						current_column++;
						if (board[row_number][current_column] == (char)FREE_SPACE && board[row_number][current_column - 1] == (char)PLAYER_TWO)
						{
							board[row_number][current_column] = AVAILABLE_SPACE;
							break;
						}

					}
				}
			}
			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_column = column_number;
					while (current_column < COLUMN + 2)
					{
						current_column++;
						if (board[row_number][current_column] == (char)FREE_SPACE && board[row_number][current_column - 1] == (char)PLAYER_ONE)
						{
							board[row_number][current_column] = AVAILABLE_SPACE;
							break;
						}

					}
				}
			}
		}
	}

	/*Column left*/
	for (row_number = 2; row_number <= COLUMN + 2; row_number++)
	{
		for (column_number = COLUMN + 2; column_number >= 2; column_number--)
		{
			/*Player one*/
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				if (symbol == PLAYER_ONE)
				{
					current_column = column_number;
					while (current_column >= 2)
					{
						current_column--;
						if (board[row_number][current_column] == (char)FREE_SPACE && board[row_number][current_column + 1] == (char)PLAYER_TWO)
						{
							board[row_number][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}

			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_column = column_number;
					while (current_column >= 2)
					{
						current_column--;
						if (board[row_number][current_column] == (char)FREE_SPACE && board[row_number][current_column + 1] == (char)PLAYER_ONE)
						{
							board[row_number][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}

		}
	}

	/*Slant(/) left to right down*/
	for (row_number = 2; row_number <= ROW + 2; row_number++)
	{
		for (column_number = 2; column_number <= COLUMN + 2; column_number++)
		{
			/*Player one*/
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				if (symbol == PLAYER_ONE)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row < ROW + 2 && current_column > 2)
					{
						current_row++;
						current_column--;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row - 1][current_column + 1] == (char)PLAYER_TWO)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}

			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row < ROW + 2 && current_column > 2)
					{
						current_row++;
						current_column--;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row - 1][current_column + 1] == (char)PLAYER_ONE)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}
		}
	}

	/*Slant(/) left to right up*/
	for (row_number = 2; row_number <= ROW + 2; row_number++)
	{
		for (column_number = 2; column_number <= COLUMN + 2; column_number++)
		{
			/*Player one*/
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				if (symbol == PLAYER_ONE)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row >= 2 && current_column < COLUMN + 2)
					{
						current_row--;
						current_column++;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row + 1][current_column - 1] == (char)PLAYER_TWO)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}

			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row >= 2 && current_column < COLUMN + 2)
					{
						current_row--;
						current_column++;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row + 1][current_column - 1] == (char)PLAYER_ONE)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}
		}
	}

	/*Slant(\) left to right down*/
	for (row_number = 2; row_number <= ROW + 2; row_number++)
	{
		for (column_number = 2; column_number <= COLUMN + 2; column_number++)
		{
			/*Player one*/
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				if (symbol == PLAYER_ONE)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row <= ROW + 2 && current_column <= COLUMN + 2)
					{
						current_row++;
						current_column++;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row - 1][current_column - 1] == (char)PLAYER_TWO)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}

			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row <= ROW + 2 && current_column <= COLUMN + 2)
					{
						current_row++;
						current_column++;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row - 1][current_column - 1] == (char)PLAYER_ONE)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}
		}
	}

	/*Slant(\) left to right up*/
	for (row_number = 2; row_number <= ROW + 2; row_number++)
	{
		for (column_number = 2; column_number <= COLUMN + 2; column_number++)
		{
			/*Player one*/
			if (board[row_number][column_number] == (char)PLAYER_ONE)
			{
				if (symbol == PLAYER_ONE)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row >= 2 && current_column >= 2)
					{
						current_row--;
						current_column--;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row + 1][current_column + 1] == (char)PLAYER_TWO)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}

			/*Player two*/
			if (board[row_number][column_number] == (char)PLAYER_TWO)
			{
				if (symbol == PLAYER_TWO)
				{
					current_row = row_number;
					current_column = column_number;
					while (current_row >= 2 && current_column >= 2)
					{
						current_row--;
						current_column--;
						if (board[current_row][current_column] == (char)FREE_SPACE && board[current_row + 1][current_column + 1] == (char)PLAYER_ONE)
						{
							board[current_row][current_column] = AVAILABLE_SPACE;
							break;
						}
					}
				}
			}
		}
	}
}

void update_board_x(char board[ROW + 2][COLUMN + 2], int current_row, int current_column, char symbol)
{
	int row_number, column_number;

	/*Column right*/
	if (is_x_column_right(board, current_row, current_column))
	{
		column_number = current_column + 1;
		while (board[current_row][column_number] == (char)PLAYER_TWO)
		{
			if (board[current_row][column_number] == (char)PLAYER_TWO && board[current_row][column_number + 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[current_row][column_number] = PLAYER_ONE;
			column_number++;
		}
	}

	/*Column left*/
	if (is_x_column_left(board, current_row, current_column))
	{
		column_number = current_column - 1;
		while (board[current_row][column_number] == (char)PLAYER_TWO)
		{
			if (board[current_row][column_number] == (char)PLAYER_TWO && board[current_row][column_number - 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[current_row][column_number] = PLAYER_ONE;
			column_number--;
		}
	}

	/*Row up*/
	if (is_x_row_up(board, current_row, current_column))
	{
		row_number = current_row - 1;
		while (board[row_number][current_column] == (char)PLAYER_TWO)
		{
			if (board[row_number][current_column] == (char)PLAYER_TWO && board[row_number - 1][current_column] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][current_column] = PLAYER_ONE;
			row_number--;
		}
	}

	/*Row down*/
	if (is_x_row_down(board, current_row, current_column))
	{
		row_number = current_row + 1;
		while (board[row_number][current_column] == (char)PLAYER_TWO)
		{
			if (board[row_number][current_column] == (char)PLAYER_TWO && board[row_number + 1][current_column] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][current_column] = PLAYER_ONE;
			row_number++;
		}
	}

	/*Slant(/) left to right up*/
	if (is_x_slant_left_right_up(board, current_row, current_column))
	{
		row_number = current_row - 1;
		column_number = current_column + 1;
		while (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number - 1][column_number + 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_ONE;
			row_number--;
			column_number++;
		}
	}

	/*Slant(/) left to right down*/
	if (is_x_slant_left_right_down(board, current_row, current_column))
	{
		row_number = current_row + 1;
		column_number = current_column - 1;
		while (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number + 1][column_number - 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_ONE;
			row_number++;
			column_number--;
		}
	}

	/*Slant(\) right to left up*/
	if (is_x_slant_right_left_up(board, current_row, current_column))
	{

		row_number = current_row - 1;
		column_number = current_column - 1;
		while (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number - 1][column_number - 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_ONE;
			row_number--;
			column_number--;
		}
	}

	/*Slant(\) right to left down*/
	if (is_x_slant_right_left_down(board, current_row, current_column))
	{
		row_number = current_row + 1;
		column_number = current_column + 1;
		while (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			if (board[row_number][column_number] == (char)PLAYER_TWO && board[row_number + 1][column_number + 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_ONE;
			row_number++;
			column_number++;
		}
	}
}
void update_board_0(char board[ROW + 2][COLUMN + 2], int current_row, int current_column, char symbol)
{
	int row_number, column_number;

	/*Column right*/
	if (is_0_column_right(board, current_row, current_column))
	{
		column_number = current_column + 1;
		while (board[current_row][column_number] == (char)PLAYER_ONE)
		{
			if (board[current_row][column_number] == (char)PLAYER_ONE && board[current_row][column_number + 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[current_row][column_number] = PLAYER_TWO;
			column_number++;
		}
	}

	/*Column left*/
	if (is_0_column_left(board, current_row, current_column))
	{
		column_number = current_column - 1;
		while (board[current_row][column_number] == (char)PLAYER_ONE)
		{
			if (board[current_row][column_number] == (char)PLAYER_ONE && board[current_row][column_number - 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[current_row][column_number] = PLAYER_TWO;
			column_number--;
		}
	}

	/*Row up*/
	if (is_0_row_up(board, current_row, current_column))
	{
		row_number = current_row - 1;
		while (board[row_number][current_column] == (char)PLAYER_ONE)
		{
			if (board[row_number][current_column] == (char)PLAYER_ONE && board[row_number - 1][current_column] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][current_column] = PLAYER_TWO;
			row_number--;

		}
	}

	/*Row down*/
	if (is_0_row_down(board, current_row, current_column))
	{

		row_number = current_row + 1;
		while (board[row_number][current_column] == (char)PLAYER_ONE)
		{
			if (board[row_number][current_column] == (char)PLAYER_ONE && board[row_number + 1][current_column] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][current_column] = PLAYER_TWO;
			row_number++;

		}

	}

	/*Slant(/) left to right up*/
	if (is_0_slant_left_right_up(board, current_row, current_column))
	{
		row_number = current_row - 1;
		column_number = current_column + 1;
		while (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number - 1][column_number + 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_TWO;
			row_number--;
			column_number++;
		}
	}

	/*Slant(/) left to right down*/
	if (is_0_slant_left_right_down(board, current_row, current_column))
	{
		row_number = current_row + 1;
		column_number = current_column - 1;
		while (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number + 1][column_number - 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_TWO;
			row_number++;
			column_number--;
		}
	}

	/*Slant(\) right to left up*/
	if (is_0_slant_right_left_up(board, current_row, current_column))
	{
		row_number = current_row - 1;
		column_number = current_column - 1;
		while (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number - 1][column_number - 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_TWO;
			row_number--;
			column_number--;
		}
	}

	/*Slant(\) right to left down*/
	if (is_0_slant_right_left_down(board, current_row, current_column))
	{
		row_number = current_row + 1;
		column_number = current_column + 1;
		while (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			if (board[row_number][column_number] == (char)PLAYER_ONE && board[row_number + 1][column_number + 1] == (char)FREE_SPACE)
			{
				break;
			}
			board[row_number][column_number] = PLAYER_TWO;
			row_number++;
			column_number++;
		}
	}
}

int is_x_row_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int row_number;
	for (row_number = current_row + 1; row_number <= ROW + 2; row_number++)
	{
		if (board[row_number][current_column] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_row_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int row_number;
	for (row_number = current_row - 1; row_number >= 2; row_number--)
	{
		if (board[row_number][current_column] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_column_right(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int column_number;
	for (column_number = current_column + 1; column_number <= COLUMN + 2; column_number++)
	{
		if (board[current_row][column_number] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_column_left(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int column_number;
	for (column_number = current_column - 1; column_number >= 2; column_number--)
	{
		if (board[current_row][column_number] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_slant_left_right_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (/)UP
{
	int row_number, column_number;
	for (row_number = current_row - 1, column_number = current_column + 1; row_number >= 2 && column_number <= COLUMN + 2; row_number--, column_number++)
	{
		if (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_slant_left_right_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (/)DOWN
{
	int row_number, column_number;
	for (row_number = current_row + 1, column_number = current_column - 1; row_number <= ROW + 2 && column_number >= 2; row_number++, column_number--)
	{
		if (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_slant_right_left_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (\)UP
{
	int row_number, column_number;
	for (row_number = current_row - 1, column_number = current_column - 1; row_number >= 2 && column_number >= 2; row_number--, column_number--)
	{
		if (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}
int is_x_slant_right_left_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (\)down
{
	int row_number, column_number;
	for (row_number = current_row + 1, column_number = current_column + 1; row_number <= ROW + 2 && column_number <= COLUMN + 2; row_number++, column_number++)
	{
		if (board[row_number][column_number] == (char)PLAYER_ONE)
		{
			return 1;
		}
	}
	return 0;
}

int is_0_row_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int row_number;
	for (row_number = current_row + 1; row_number <= ROW + 2; row_number++)
	{
		if (board[row_number][current_column] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_row_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int row_number;
	for (row_number = current_row - 1; row_number >= 2; row_number--)
	{
		if (board[row_number][current_column] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_column_right(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int column_number;
	for (column_number = current_column + 1; column_number <= COLUMN + 2; column_number++)
	{
		if (board[current_row][column_number] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_column_left(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int column_number;
	for (column_number = current_column - 1; column_number >= 2; column_number--)
	{
		if (board[current_row][column_number] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_slant_left_right_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (/)UP
{
	int row_number, column_number;
	for (row_number = current_row - 1, column_number = current_column + 1; row_number >= 2 && column_number <= COLUMN + 2; row_number--, column_number++)
	{
		if (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_slant_left_right_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (/)DOWN
{
	int row_number, column_number;
	for (row_number = current_row + 1, column_number = current_column - 1; row_number <= ROW + 2 && column_number >= 2; row_number++, column_number--)
	{
		if (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_slant_right_left_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (\)UP
{
	int row_number, column_number;
	for (row_number = current_row - 1, column_number = current_column - 1; row_number >= 2 && column_number >= 2; row_number--, column_number--)
	{
		if (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}
int is_0_slant_right_left_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (\)down
{
	int row_number, column_number;
	for (row_number = current_row + 1, column_number = current_column + 1; row_number <= ROW + 2 && column_number <= COLUMN + 2; row_number++, column_number++)
	{
		if (board[row_number][column_number] == (char)PLAYER_TWO)
		{
			return 1;
		}
	}
	return 0;
}


int is_free_space_row_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int row_number;
	for (row_number = current_row + 1; row_number < ROW + 2; row_number++)
	{
		if (board[row_number][current_column] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_row_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int row_number;
	for (row_number = current_row - 1; row_number > 2; row_number--)
	{
		if (board[row_number][current_column] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_column_right(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int column_number;
	for (column_number = current_column + 1; column_number < COLUMN + 2; column_number++)
	{
		if (board[current_row][column_number] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_column_left(char board[ROW + 2][COLUMN + 2], int current_row, int current_column)
{
	int column_number;
	for (column_number = current_column - 1; column_number > 2; column_number--)
	{
		if (board[current_row][column_number] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_slant_left_right_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (/)UP
{
	int row_number, column_number;
	for (row_number = current_row - 1, column_number = current_column + 1; row_number > 2 && column_number < COLUMN + 2; row_number--, column_number++)
	{
		if (board[row_number][column_number] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_slant_left_right_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (/)DOWN
{
	int row_number, column_number;
	for (row_number = current_row + 1, column_number = current_column - 1; row_number < ROW + 2 && column_number > 2; row_number++, column_number--)
	{
		if (board[row_number][column_number] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_slant_right_left_up(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (\)UP
{
	int row_number, column_number;
	for (row_number = current_row - 1, column_number = current_column - 1; row_number > 2 && column_number > 2; row_number--, column_number--)
	{
		if (board[row_number][column_number] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}
int is_free_space_slant_right_left_down(char board[ROW + 2][COLUMN + 2], int current_row, int current_column) // (\)down
{
	int row_number, column_number;
	for (row_number = current_row + 1, column_number = current_column + 1; row_number < ROW + 2 && column_number < COLUMN + 2; row_number++, column_number++)
	{
		if (board[row_number][column_number] == (char)FREE_SPACE)
		{
			return 1;
		}
	}
	return 0;
}