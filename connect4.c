#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <time.h>

#define MAX_COLUMNS 7
#define MAX_LINES 5
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define FLICKER 10

int matrix[MAX_LINES][MAX_COLUMNS];
int redLines[5] = {PA0, PA1, PC5, PC6, PB0};
int greenLines[5] = {PC0, PA2, PA3, PA6, PC7};
int columns[7] = {PC2, PC3, PC1, PC4, PA7, PA4, PA5};
int buttons[4] = {PD0, PD1, PD4, PD5};

int turn = 0;
int pressButton = 0;
int endOfGame = 1;
int gameMode = 1;

void enableColumn(int column){
	switch (column){
		case 0:
			PORTC |= (1 << columns[0]);
			break;
		case 1:
			PORTC |= (1 << columns[1]);
			break;
		case 2:
			PORTC |= (1 << columns[2]);
			break;
		case 3:
			PORTC |= (1 << columns[3]);
			break;
		case 4:
			PORTA |= (1 << columns[4]);
			break;
		case 5:
			PORTA |= (1 << columns[5]);
			break;
		default:
			PORTA |= (1 << columns[6]);
			break;
	} 
}

void enableRedRow(int row){
	switch (row){
		case 0:
			PORTA |= (1 << redLines[0]);
			break;
		case 1:
			PORTA |= (1 << redLines[1]);
			break;
		case 2:
			PORTC |= (1 << redLines[2]);
			break;
		case 3:
			PORTC |= (1 << redLines[3]);
			break;
		default:
			PORTB |= (1 << redLines[4]);
			break;
	}
}

void disableRedRow(int row){
	switch (row){
		case 0:
			PORTA &= ~(1 << redLines[0]);
			break;
		case 1:
			PORTA &= ~(1 << redLines[1]);
			break;
		case 2:
			PORTC &= ~(1 << redLines[2]);
			break;
		case 3:
			PORTC &= ~(1 << redLines[3]);
			break;
		default:
			PORTB &= ~(1 << redLines[4]);
			break;
	}
}

void enableGreenRow(int row){
	switch (row){
		case 0:
			PORTC |= (1 << greenLines[0]);
			break;
		case 1:
			PORTA |= (1 << greenLines[1]);
			break;
		case 2:
			PORTA |= (1 << greenLines[2]);
			break;
		case 3:
			PORTA |= (1 << greenLines[3]);
			break;
		default:
			PORTC |= (1 << greenLines[4]);
			break;
	}
}

void disableGreenRow(int row){
	switch (row){
		case 0:
			PORTC &= ~(1 << greenLines[0]);
			break;
		case 1:
			PORTA &= ~(1 << greenLines[1]);
			break;
		case 2:
			PORTA &= ~(1 << greenLines[2]);
			break;
		case 3:
			PORTA &= ~(1 << greenLines[3]);
			break;
		default:
			PORTC &= ~(1 << greenLines[4]);
			break;
	}
}

void lightGreen(int row, int column){
	enableColumn(column);
	enableGreenRow(row);
}

void unlightGreen(int row, int column){
	disableColumn(column);
	disableGreenRow(row);
}

void lightRed(int row, int column){
	enableColumn(column);
	enableRedRow(row);
}

void unlightRed(int row, int column){
	disableColumn(column);
	disableRedRow(row);
}

int verifyEndOfGame(){
	int i, j;

	for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				if (matrix[i][j] == 0){
					return 0;
				}

	return 1;
}

int checkHorizontal()
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

int HorizontalMove(int player){
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

int checkVertical(){
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

int VerticalMove(int player){
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

int checkLeftDiagonal(){
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

int LeftDiagonalMove(int player){
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

int checkRightDiagonal(){
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

int RightDiagonalMove(int player){
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

int verifyWhoWins(){
	int whoWins;

	whoWins = checkHorizontal();
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	whoWins = checkVertical();
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	whoWins = checkLeftDiagonal();
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	whoWins = checkRightDiagonal();
	if (whoWins == 1)
		return 1;

	if (whoWins == 2)
		return 2;

	return 0;
}

int selectMove(int player){
	int selected, available;

	selected = HorizontalMove(player);
	if (selected != -1)
		return selected;

	selected = VerticalMove(player);
	if (selected != -1)
		return selected;

	selected = LeftDiagonalMove(player);
	if (selected != -1)
		return selected;

	selected = RightDiagonalMove(player);
	if (selected != -1)
		return selected;

	return selected;
}

int main(){
	int i, j, left, right, whoWins, selected, available, times;
	
	srand(time(NULL));
	
	DDRA = 0xFF;
	DDRB |= (1 << PB0);
	DDRC = 0xFF;
	
	DDRD &= ~(1 << buttons[0]);
	DDRD &= ~(1 << buttons[1]);
	DDRD &= ~(1 << buttons[2]);
	DDRD &= ~(1 << buttons[3]);
	
	for (i = 0; i < MAX_LINES; i++)
		for (j = 0; j < MAX_COLUMNS; j++)
			matrix[i][j] = 0;
	
	while (!(PIND & (1 << PD4))){
		if ((PIND & (1 << PD5)) == 0)
			gameMode = (gameMode + 1) % 3;
	}
	
	while (1){
		left = 0;
		right = 0;
		
		whoWins = verifyWhoWins();
		//something to do with leds
		
		endOfGame = verifyEndOfGame();
		//something to do with both colors if it'a a tie
		
		if (turn % 2 == 0){
			while (!(PIND & (1 << PD4))){
				//PD0 dreapta; PD1 stanga; PD4 selectie; PD5 mod joc
				if ((PIND & (1 << PD0)) == 0)
					right++;
				if ((PIND & (1 << PD1)) == 0)
					left++;
					
				selected = 0 + right - left;
					
				for (i = MAX_LINES - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = PLAYER_TWO;
						break;
					}
					
				for (times = 0; times < FLICKERS; times++){
						lightRed(i, selected);
						unlightRed(i, selected);
					}	

			}
			
			selected = 0 + right - left;
			
			for (i = MAX_LINES - 1; i >= 0; i--)
				if (matrix[i][selected] == 0){
					matrix[i][selected] = PLAYER_ONE;
					break;
				}
			
			lightRed(i, selected);
		}
		else{
			if (gameMode == 1){
				while (!(PIND & (1 << PD4))){
					//PD0 dreapta; PD1 stanga; PD4 selectie; PD5 mod joc
					if ((PIND & (1 << PD0)) == 0)
						right++;
					if ((PIND & (1 << PD1)) == 0)
						left++;
						
					selected = 0 + right - left;
					
					for (i = MAX_LINES - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = PLAYER_TWO;
						break;
					}
					
					for (times = 0; times < FLICKERS; times++){
						lightGreen(i, selected);
						unlightGreen(i, selected);
					}	
				}	
			
				for (i = MAX_LINES - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = PLAYER_TWO;
						break;
					}
					
				lightGreen(i, selected);
			}
			else if (gameMode == 2){
				do{
					selected = rand() % 7;
					if (matrix[0][selected] != 0)
						available = 1;
					else
						available = 0;
				}while (available == 1);

				for (i = MAX_LINES - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = PLAYER_TWO;
						break;
					}
				
				lightGreen(i, selected);
			}
			else if (gameMode == 3){
				if (turn == 1)
					selected = rand() % MAX_COLUMNS;
				else{
					selected = selectMove(PLAYER_TWO);
					if (selected == -1){
						selected = selectMove(PLAYER_ONE);
						if (selected == -1)
							do{
								selected = rand() % 7;
								if (matrix[0][selected] != 0)
									available = 1;
								else
									available = 0;
							}while (available == 1);
					}
					
					for (i = n - 1; i >= 0; i--)
					if (matrix[i][selected] == 0){
						matrix[i][selected] = PLAYER_TWO;
						break;
					}
					
					lightGreen(i, selected);
				}
			}
		}
		
		turn++;
		endOfGame = 1;
	}
}
