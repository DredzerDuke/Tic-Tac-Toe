#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

char board[3][3];
int chances = 0;

void clear_board();
void print_board();
void take_userinput();
bool check_empty(int r, int c);
bool check_chances();
void take_cpuinput();

int main()
{
    clear_board();
    while (check_chances())
    {
        take_cpuinput();
        print_board();
        take_userinput();
        print_board();
    }
    printf("You ran out of chances!...\n");
}

void clear_board()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void print_board()
{
    printf("\n %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("--- --- ---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("--- --- ---\n");
    printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void take_userinput()
{
    while (1) 
    {
        int row, column;
        printf("Enter the row : ");
        scanf("%d", &row);
        if (row > 3 || row < 0) {
            printf("only row 1 to 3 accepted!\n");
            continue;
        }
        row -= 1;
        printf("Enter the column : ");
        scanf("%d", &column);
        if (column > 3 || column < 0) {
            printf("only column 1 to 3 accepted!\n");
            continue;
        }
        column -= 1;

        if (check_chances() && check_empty(row, column))
        {
            board[row][column] = 'X';
            break;
        } else if (!check_empty(row, column))
            printf("Try again..! \nThe place is occupied.\n");
        else if (!check_chances()) {
            printf("You ran out of chances!\n");
            break;
        }
    }
}

bool check_empty(int r, int c)
{
    if (board[r][c] == ' ')
        return true;
    else
        return false;
}

bool check_chances()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++){
            if (board[i][j] = ' ')
                return true;
        }
    }
    return false;
}

void take_cpuinput()
{
    srand(time(NULL));
    while (1)
    {
        int row = rand() % 3;
        int column = rand() % 3;
        if (check_chances() && check_empty(row, column))
        {
            board[row][column] = 'O';
            break;
        }
        else if (!check_chances()) {
            printf("You ran out of chances!\n");
            exit(1);
        }
    }
}
