#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 5
#define m 7

int verifyEndOfGame(int** matrix){
  int i, j;

	for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				if (matrix[i][j] == 0){
					return 0;
				}

	return 1;
}

int checkHorizontal(int** matrix){
	int i, j;

	for (i = n - 1; i >= 0; i--)
		for (j = 0; j < m - 3; j++){
			if ((matrix[i][j] == 1) && (matrix[i][j + 1] == 1) &&
				(matrix[i][j + 2] == 1) && (matrix[i][j + 3] == 1))
				return 1;

			if ((matrix[i][j] == 2) && (matrix[i][j + 1] == 2) &&
				(matrix[i][j + 2] == 2) && (matrix[i][j + 3] == 2))
				return 2;
		}

	return 0;
}

int HorizontalMove(int** matrix, int player){
	//when player is 1, lose is checked; otherwise, win is checked
	int i, j;

	for (i = n - 1; i >= 0; i--)
		for (j = 0; j < m - 3; j++){
			if ((matrix[i][j] == player) && (matrix[i][j + 1] == player) &&
				(matrix[i][j + 2] == player) && (matrix[i][j + 3] == 0) &&
				(i == n - 1 || matrix[i - 1][j + 3] != 0))
				return j + 3;
			if ((matrix[i][j] == player) && (matrix[i][j + 1] == player) &&
				(matrix[i][j + 3] == player) && (matrix[i][j + 2] == 0) &&
				(i == n - 1 || matrix[i - 1][j + 2] != 0))
				return j + 2;
			if ((matrix[i][j] == player) && (matrix[i][j + 2] == player) &&
				(matrix[i][j + 3] == player) && (matrix[i][j + 1] == 0) &&
				(i == n - 1 || matrix[i - 1][j + 1] != 0))
				return j + 1;
			if ((matrix[i][j + 1] == player) && (matrix[i][j + 2] == player) &&
				(matrix[i][j + 3] == player) && (matrix[i][j] == 0) &&
				(i == n - 1 || matrix[i - 1][j] != 0))
				return j;
		}

	return -1;
}

int checkVertical(int** matrix){
	int i, j;

	for (j = 0; j < m; j++)
		for (i = 0; i < n - 3; i++){
			if ((matrix[i][j] == 1) && (matrix[i + 1][j] == 1) &&
				(matrix[i + 2][j] == 1) && (matrix[i + 3][j] == 1))
				return 1;

			if ((matrix[i][j] == 2) && (matrix[i + 1][j] == 2) &&
				(matrix[i + 2][j] == 2) && (matrix[i + 3][j] == 2))
				return 2;
		}

	return 0;
}

int VerticalMove(int** matrix, int player){
	int i, j;
	
	for (j = 0; j < m; j++){
		for(i = n - 1; i > n - 3; i--){
			if ((matrix[i][j] == player) && (matrix[i - 1][j] == player) &&
				(matrix[i - 2][j] == player) && (matrix[i - 3][j] == 0))
				return j;
		}
	}
	return -1;
}

int checkLeftDiagonal(int** matrix){
	int i, j;

	for (i = 0; i < n - 3; i++)
		for (j = 0; j < m - 3; j++){
			if ((matrix[i][j] == 1) && (matrix[i + 1][j + 1] == 1) &&
				(matrix[i + 2][j + 2] == 1) && (matrix[i + 3][j + 3] == 1))
				return 1;

			if ((matrix[i][j] == 2) && (matrix[i + 1][j + 1] == 2) &&
				(matrix[i + 2][j + 2] == 2) && (matrix[i + 3][j + 3] == 2))
				return 2;
		}

	return 0;
}

int LeftDiagonalMove(int** matrix, int player){
	int i, j;

	for (i = 0; i < n - 3; i++)
		for (j = 0; j < m - 3; j++){
			if ((matrix[i][j] == player) && (matrix[i + 1][j + 1] == player) &&
				(matrix[i + 2][j + 2] == player) && (matrix[i + 3][j + 3] == 0) &&
				((i + 3) == (n - 1) || (matrix[i + 4][j + 3] != 0)))
				return j + 3;
			if ((matrix[i][j] == player) && (matrix[i + 1][j + 1] == player) &&
				(matrix[i + 3][j + 3] == player) && (matrix[i + 2][j + 2] == 0) &&
				(matrix[i + 3][j + 2] != 0))
				return j + 2;
			if ((matrix[i][j] == player) && (matrix[i + 2][j + 2] == player) &&
				(matrix[i + 3][j + 3] == player) && (matrix[i + 1][j + 1] == 0) &&
				(matrix[i + 2][j + 1] != 0))
				return j + 1;
			if ((matrix[i + 1][j + 1] == player) && (matrix[i + 2][j + 2] == player) &&
				(matrix[i + 3][j + 3] == player) && (matrix[i][j] == 0) &&
				(matrix[i + 1][j] != 0))
				return j;
		}
		
	return -1;
}

int checkRightDiagonal(int** matrix){
	int i, j;

	for (i = 0; i < n - 3; i++)
		for (j = m - 1; j >= 3; j--){
			if ((matrix[i][j] == 1) && (matrix[i + 1][j - 1] == 1) &&
				(matrix[i + 2][j - 2] == 1) && (matrix[i + 3][j - 3] == 1))
				return 1;

			if ((matrix[i][j] == 2) && (matrix[i + 1][j - 1] == 2) &&
				(matrix[i + 2][j - 2] == 2) && (matrix[i + 3][j - 3] == 2))
				return 2;
		}

	return 0;
}

int RightDiagonalMove(int** matrix, int player){
	int i, j;

	for (i = 0; i < n - 3; i++)
		for (j = m - 1; j >= 3; j--){
			if ((matrix[i][j] == player) && (matrix[i + 1][j - 1] == player) &&
				(matrix[i + 2][j - 2] == player) && (matrix[i + 3][j - 3] == 0) &&
				((i + 3) == (n - 1) || matrix[i + 4][j - 3] != 0))
				return j - 3;
			if ((matrix[i + 1][j - 1] == player) && (matrix[i + 2][j - 2] == player) &&
				(matrix[i + 3][j - 3] == player) && (matrix[i][j] == 0) &&
				(matrix[i + 1][j] != 0))
				return j;
			if ((matrix[i][j] == player) && (matrix[i + 2][j - 2] == player) &&
				(matrix[i + 3][j - 3] == player) && (matrix[i + 1][j - 1] == 0) &&
				(matrix[i + 2][j - 1] != 0))
				return j - 1;
			if ((matrix[i][j] == player) && (matrix[i + 1][j - 1] == player) &&
				(matrix[i + 3][j - 3] == player) && (matrix[i + 2][j - 2] == 0) &&
				(matrix[i + 3][j - 2] != 0))
				return j - 2;
		}

	return -1;
}

int verifyWhoWins(int** matrix){
	int whoWins;

	whoWins = checkHorizontal(matrix);
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	whoWins = checkVertical(matrix);
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	whoWins = checkLeftDiagonal(matrix);
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	whoWins = checkRightDiagonal(matrix);
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	return 0;
}

int selectMove(int** matrix, int player){
	int selected, available;

	selected = HorizontalMove(matrix, player);
	if (selected != -1)
		return selected;

	selected = VerticalMove(matrix, player);
	if (selected != -1)
		return selected;

	selected = LeftDiagonalMove(matrix, player);
	if (selected != -1)
		return selected;

	selected = RightDiagonalMove(matrix, player);
	if (selected != -1)
		return selected;

	return selected;
}

int main(){
	int** matrix;
	int i, j, selected, turn, endOfGame, whoWins, checkLose, available, gameMode;

	srand(time(NULL));

	turn = 0;
	endOfGame = 1;

	printf("Select game mode:\n");
	printf("\t1. Player vs player\n");
	printf("\t2. Player vs dummy computer\n");
	printf("\t3. Player vs smart computer\n");
	scanf("%d", &gameMode);

	matrix = calloc(n, sizeof(int*));
	for (i = 0; i < n; i++)
		matrix[i] = calloc(m, sizeof(int));

	while (1){
		whoWins = verifyWhoWins(matrix);
		if (whoWins == 1){
			printf("Red wins!\n");
			break;
		}
		if (whoWins == 2){
			printf("Green wins!\n");
			break;
		}

		endOfGame = verifyEndOfGame(matrix);

		if (endOfGame == 1){
			printf("It's a tie!\n");
			break;
		}

		if (turn % 2 == 0){
			printf("Introduceti un numar de la 0 la 6: ");
			scanf("%d", &selected);

			for (i = n - 1; i >= 0; i--)
				if (matrix[i][selected] == 0){
					matrix[i][selected] = 1;
					break;
				}
		}
		else{
			if (gameMode == 1){
				printf("Introduceti un numar de la 0 la 6: ");
				scanf("%d", &selected);

				for (i = n - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = 2;
						break;
					}
			}
			else if (gameMode == 2){
				do{
					selected = rand() % 7;
					if (matrix[0][selected] != 0)
						available = 1;
					else
						available = 0;
				}while (available == 1);

				for (i = n - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = 2;
						break;
					}
			}
			else if (gameMode == 3){
				if (turn == 1)
					selected = rand() % m;
				else{
					selected = selectMove(matrix, 2);
					if (selected == -1){
						selected = selectMove(matrix, 1);
						if (selected == -1)
							do{
								selected = rand() % 7;
								if (matrix[0][selected] != 0)
									available = 1;
								else
									available = 0;
							}while (available == 1);
					}
				}
				
				for (i = n - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = 2;
						break;
					}
			}
		}

		for (i = 0; i < n; i++){
			for (j = 0; j < m; j++)
				printf("%d ", matrix[i][j]);
			printf("\n");
		}
		printf("\n");

		turn++;
		endOfGame = 1;
	}

	for (i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);

	return 0;
}
