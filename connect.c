#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "slist.h"

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];
char playerYellow[30];
char playerRed[30];
char currentPlayer = 'R';
slist replay = {NULL, NULL}; //Creates a linked list.

    void CreateBoard() { //Creates the empty spots of the board to fill during game
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void DisplayBoard() { //Prints the current board
        printf("\n");
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printf("|%c", board[i][j]);
            }
            printf("|\n");
        }
        printf("---------------\n");
    }

	int GetColumn(char player) { //Prompts user to select a column 1-7
		int column = 0;
        printf("%s, player %c to play. Pick a column (1-7): ", (currentPlayer == 'R' ? playerRed : playerYellow), currentPlayer);
        scanf("%d", &column);

        while (!(column >= 1 && column <= COLS && board[0][column - 1] == ' ')) { // Tells you to redo it if column is full or out of range of 1-7
            printf("Invalid input. Please enter another column: ");  // lol try again
            scanf("%d", &column);
            while (getchar() != '\n');
        }
		return column - 1;
	}

    void MakeMove(char board[ROWS][COLS], int colChosen, char player) { //Once valid column is chosen, fills spot with players token
        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][colChosen] == ' ') {
                board[i][colChosen] = player; //Places Y or R depending on whose turn it is
                insertTail(&replay, i, colChosen, player); //Inserts a node of the player's move for replay.
                break;
            }
        }
    }

    bool CheckFull() { //Checks if the board is full already
        // iterate through all rows and columns to check is != ' ' (aka empty)
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    int CheckWinner(int tokens) { //Declares which player has won
        // Horizontally
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j <= COLS - tokens; j++) {
                int count = 0;
                for (int k = 0; k < tokens; k++) {
                    if (board[i][j + k] == currentPlayer) {
                        count++;
                    }
                }
                if (count == tokens) {
                    return 1;
                }
            }
        }

        // Vertically
        for (int i = 0; i <= ROWS - tokens; i++) {
            for (int j = 0; j < COLS; j++) {
                int count = 0;
                for (int k = 0; k < tokens; k++) {
                    if (board[i + k][j] == currentPlayer) {
                        count++;
                    }
                }
                if (count == tokens) {
                    return 1;
                }
            }
        }

        // Diagonally from bottom left to top-right
        for (int i = tokens - 1; i < ROWS; i++) {
            for (int j = 0; j <= COLS - tokens; j++) {
                int count = 0;
                for (int k = 0; k < tokens; k++) {
                    if (board[i - k][j + k] == currentPlayer) {
                        count++;
                    }
                }
                if (count == tokens) {
                    return 1;
                }
            }
        }

        // Diagonally from top left to bottom-right
        for (int i = 0; i <= ROWS - tokens; i++) {
            for (int j = 0; j <= COLS - tokens; j++) {
                int count = 0;
                for (int k = 0; k < tokens; k++) {
                    if (board[i+ k][j + k] == currentPlayer) {
                        count++;
                    }
                }
                if (count == tokens) {
                    return 1;
                }
            }
        }
        return 0;
    }

	void PlayConnectFour() {
        int tokens;
        bool winner = false;
        bool tied = false;

        printf("Enter how many tokens are needed to win: ");
        scanf("%d", &tokens);

        while (tokens >= 5 || tokens <= 0) {
        	printf("Invalid input, please enter another one: ");
            scanf("%d", &tokens);
        }
        printf("\n");

        printf("Please enter player yellow: ");
        scanf("%s", &playerYellow);

        printf("Please enter player red: ");
        scanf("%s", &playerRed);

        CreateBoard();
        DisplayBoard(); // Sets up initial board

        while ((winner != 1) && !tied) { // While game is not over yet
        	int col = GetColumn(currentPlayer);
            MakeMove(board, col, currentPlayer);
            DisplayBoard();
            winner = CheckWinner(tokens);
            if(winner != 1) {
                tied = CheckFull();
                if (!tied) {
                	currentPlayer = (currentPlayer == 'R') ? 'Y' : 'R';
                }
            } 
        }

        if (winner == 1) {
            printf("%s, has won!\n", (currentPlayer == 'R' ? playerRed : playerYellow));
        }
	}

	void ReplayBoard(slist* list) { //Replays the previous game.
		struct Node* current = list->head;
		CreateBoard(); //Resets the board for replay.
		DisplayBoard();

		while (current != NULL) { //While the list is not empty.
			int row = current->row;
			int col = current->col;

			if (board[row][col] == ' ') { //Using the node's data, it fills in the player's spot from the actual game.
				board[row][col] = current->player;
			}

			DisplayBoard();
			current = current->next; //Moves onto the next node of the list.
		}
		printf("End of replay.\n");

	}

	int main() {
		char c = '\0';
		bool done = false;

		printf("Welcome! Press 'q' to quit or any key to continue: ");

		while (!done) {
			scanf(" %c", &c);

			if (c == 'q') {
				printf("Bye Bye!\n");
				freeList(&replay);
				done = true;
			} else if (c == 'r') {
				ReplayBoard(&replay);
		        printf("Welcome! Press 'q' to quit or 'r' to replay or any key to continue: ");
			}else {
				PlayConnectFour();
		        printf("Welcome! Press 'q' to quit or 'r' to replay or any key to continue: ");
			}
		}
        return 0;
	}

