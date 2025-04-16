#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char CPU = 'O';
char WINNER = ' ';
int spaceAvailable = 9;

void printBoard();
void resetBoard();
char *getBoardPosition(int);
void throwError(char*);
bool isValidEntry(int);
void makeEntry(int, bool);
void checkWinner();
void theGame();
void displayWinner();
int getPlayerInput();
int getCpuInput();

int main() {
    theGame();
}

void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}

void resetBoard() {
    int k = 49;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            board[i][j] = k++;
    }
}

char *getBoardPosition(int position) {
    switch (position) {
        case 1:
            return &board[0][0];
            break;
        case 2:
            return &board[0][1];
            break;
        case 3:
            return &board[0][2];
            break;
        case 4:
            return &board[1][0];
            break;
        case 5:
            return &board[1][1];
            break;
        case 6:
            return &board[1][2];
            break;
        case 7:
            return &board[2][0];
            break;
        case 8:
            return &board[2][1];
            break;
        case 9:
            return &board[2][2];
            break;
    }
    return "";
}

void throwError(char *errDesc) {
    fprintf(stderr, "%s\n", errDesc);
    exit(EXIT_FAILURE);
}

bool isValidEntry(int position) {
    if (position < 1 || position > 9)
        return false;
    if (!spaceAvailable)
        return false;
    char *ch = getBoardPosition(position);
    if (!isdigit(*ch))
        return false;
    return true;
}

void makeEntry(int position, bool isPlayer) {
    if (!isValidEntry(position))
        throwError("not a valid entry!");
    char *boardPosition = getBoardPosition(position);
    if (isPlayer)
        *boardPosition = PLAYER;
    else
        *boardPosition = CPU;
    spaceAvailable--;
    checkWinner();
}

void checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            WINNER = board[i][0];
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            WINNER = board[0][i];
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        WINNER = board[0][0];
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        WINNER = board[0][2];
}

int getPlayerInput() {
    int userInput;
    printf("Enter your choice : ");
    scanf("%d", &userInput);
    getchar();
    return userInput;
}

int getCpuInput() {
    int cpuInput;
    srand(time(NULL));
    do {
        cpuInput = rand() % 9 + 1;
    } while (!isValidEntry(cpuInput));
    return cpuInput;
}

void displayWinner() {
    if (WINNER == PLAYER)
        printf("Congrats! You Win....!\n");
    else if (WINNER == CPU)
        printf("CPU won... Try Again!\n");
    else
        printf("its a draw!\n");
}

void theGame() {
    resetBoard();
    printBoard();
    while(WINNER == ' ' && spaceAvailable > 0) {
        int playerInput = getPlayerInput();
        makeEntry(playerInput, true);
        int cpuInput = getCpuInput();
        makeEntry(cpuInput, false);
        printBoard();
    }
    displayWinner();
}

