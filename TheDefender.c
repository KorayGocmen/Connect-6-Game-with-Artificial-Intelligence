#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void printBoard(char board[21][21], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == n - 1)
                printf("%c\n", board[i][j]);
            else
                printf("%c", board[i][j]);
        }
    }
}

int findLongest(char board[21][21], int n, int row, int col) {
    bool found = true;
    int longest1 = 0, longest2 = 0, longest3 = 0, longest4 = 0;
    int longest5 = 0, longest6 = 0, longest7 = 0, longest8 = 0;

    //left-up
    for (int i = 1; i <= row && i <= col && found; i++) {
        if (board[row][col] == board[row - i][col - i]) {
            longest1++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //up
    for (int i = 1; i <= row && found; i++) {
        if (board[row][col] == board[row - i][col]) {
            longest2++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //right-up
    for (int i = 1; i <= row && i <= n - col - 1 && found; i++) {
        if (board[row][col] == board[row - i][col + i]) {
            longest3++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //right
    for (int i = 1; i <= n - col - 1 && found; i++) {
        if (board[row][col] == board[row][col + i]) {
            longest4++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //right-down
    for (int i = 1; i <= n - row - 1 && i <= n - col - 1 && found; i++) {
        if (board[row][col] == board[row + i][col + i]) {
            longest5++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //down
    for (int i = 1; i <= n - row - 1 && found; i++) {
        if (board[row][col] == board[row + i][col]) {
            longest6++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //left-down
    for (int i = 1; i <= n - row - 1 && i <= col && found; i++) {
        if (board[row][col] == board[row + i][col - i]) {
            longest7++;
            found = true;
        } else
            found = false;
    }
    found = true;
    //left
    for (int i = 1; i <= col && found; i++) {
        if (board[row][col] == board[row][col - i]) {
            longest8++;
            found = true;
        } else
            found = false;
    }

    int leftUpToRightDown = longest1 + longest5 + 1;
    int upToDown = longest2 + longest6 + 1;
    int rightUpToLeftDown = longest3 + longest7 + 1;
    int rightToLeft = longest4 + longest8 + 1;

    int maxLongest = fmax(fmax(leftUpToRightDown, upToDown), fmax(rightUpToLeftDown, rightToLeft));

    return maxLongest;
}

int defender(char board[21][21], int n, char computerColor[3]) {

    int maxRow = 0, maxCol = 0;
    int currentMax = 0;
    int a;
    char enemyColor[3];
    int returner;



    if (computerColor[0] == 'W')
        enemyColor[0] = 'B';
    else if (computerColor[0] == 'B')
        enemyColor[0] = 'W';


    for (int i=n-1 ; i>=0 ; i--) {
        for (int j=n-1 ; j>=0 ; j--) {
            if (board[i][j] == 'U') {
                board[i][j] = enemyColor[0];
                a = findLongest(board, n, i, j);
                if (a > currentMax) {
                    currentMax = a;
                    maxRow = i;
                    maxCol = j;
                }
                board[i][j] = 'U';
            }
        }
    }

    returner = 1000 * maxRow + maxCol;
    return returner;
}

void computerMove(char board[21][21], int n, char computerColor[3], int depth) {

    int rowHolder, colHolder;
    char enemyColor[3];
    int totalHolder;

    if (computerColor[0] == 'W')
        enemyColor[0] = 'B';
    else if (computerColor[0] == 'B')
        enemyColor[0] = 'W';

    totalHolder = defender(board, n, computerColor);
    rowHolder = totalHolder / 1000;
    colHolder = totalHolder % 1000;

    if (computerColor[0] == 'W') {
        board[rowHolder][colHolder] = 'W';
        printf("Computer moves W at %d %d\n", rowHolder, colHolder);
    } else {
        board[rowHolder][colHolder] = 'B';
        printf("Computer moves B at %d %d\n", rowHolder, colHolder);
    }
}

int noWinner(char board[21][21], int n) {
    int noWinner = 1;
    for (int i=n-1 ; i>=0 ; i--) {
        for (int j=n-1 ; j>=0 ; j--) {
            if (board[i][j] == 'W' || board[i][j] == 'B') {
                if (findLongest(board, n, i, j) >= 6) {
                    noWinner = 0;
                }
            }
        }
    }
    return noWinner;
}

int notFull(char board[21][21], int n) {

    int notFull = 0;

    for (int i=n-1 ; i>=0 ; i--) {
        for (int j=n-1 ; j>=0 ; j--) {
            if (board[i][j] == 'U') {
                notFull = 1;
            }
        }
    }
    return notFull;
}

void whoIsTheWinner(char board[21][21], int n) {
    int theBiggest = 0;
    int maxLongest;
    int maxRow, maxCol;
    for (int i=n-1 ; i>=0 ; i--) {
        for (int j=n-1 ; j>=0 ; j--) {
            if (board[i][j] == 'W' || board[i][j] == 'B') {
                maxLongest = findLongest(board, n, i, j);
                if (maxLongest > theBiggest) {
                    theBiggest = maxLongest;
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
    }


    if (theBiggest >= 6 && board[maxRow][maxCol] == 'W')
        printf("\nWhite player wins.\n");

    else if (theBiggest >= 6 && board[maxRow][maxCol] == 'B')
        printf("\nBlack player wins.\n");

}

int main(void) {
    int dimensions, row, col;
    char computerColor[3];
    bool flag = true;
    bool noWinner1 = true, notFull1 = true;

    printf("Enter board dimensions (n), n>=6 and n<=21: ");
    scanf("%d", &dimensions);
    int n = dimensions;

    char board[21][21];
    char enemyColor[3];

    if (computerColor[0] == 'W')
        enemyColor[0] = 'B';
    else if (computerColor[0] == 'B')
        enemyColor[0] = 'W';

    /////////////////////////////////////////////
    ////// INITIALIZING THE BOARD   ////////////
    ////////////////////////////////////////////


    for (int i=n-1 ; i>=0 ; i--) {
        for (int j=n-1 ; j>=0 ; j--) {
            board[i][j] = 'U';
        }
    }

    printBoard(board, n);

    printf("Computer playing B or W?: ");
    scanf("%s", computerColor);

    if (computerColor[0] == 'W')
        flag = false;


    /////////////////////////////////////////////
    //////    BLOCKING THE SQUARES    //////////
    ////////////////////////////////////////////

    do {
        printf("Enter position (ROW COL) of blocked square; (-1 -1) to finish: ");
        scanf("%d %d", &row, &col);
        if (row > n || col > n)
            printf("Out of range row or column\n");
        else {
            if (col >= 0 && row >= 0) {
                if (board[row][col] != (char) 'U')
                    printf("Position already occupied, try again\n");
                else {
                    board[row][col] = (char) 'R';
                    printBoard(board, n);
                }
            }
        }
    } while (row >= 0 && col >= 0);

    ////////////////////////////////////////////
    /////////   PLAYING THE GAME     ///////////
    ///////////////////////////////////////////

    do {

        if (flag) { //COMPUTER STARTS

            if (noWinner1 && notFull1) {

                computerMove(board, n, computerColor, 1);
                printBoard(board, n);
                noWinner1 = noWinner(board, n);
                notFull1 = notFull(board, n);

            }

            bool found = true;
            //if there is no winner and the board is not full
            if (noWinner1 && notFull1) {
                do {
                    printf("Enter White Move (ROW COL): ");
                    scanf("%d %d", &row, &col);

                    if (row > n - 1 || col > n - 1) {
                        printf("Out of range row or column\n");
                        found = true;
                    } else {
                        if (board[row][col] != (char) 'U') {
                            printf("That square is already occupied or blocked\n");
                            found = true;
                        } else {
                            board[row][col] = (char) 'W';
                            printBoard(board, n);
                            found = false;
                            noWinner1 = noWinner(board, n);
                            notFull1 = notFull(board, n);
                        }
                    }

                } while (found);
            }
        } else { //HUMAN STARTS

            bool found = true;
            //if there is no winner and the board is not full
            if (noWinner1 && notFull1) {
                do {
                    printf("Enter Black Move (ROW COL): ");
                    scanf("%d %d", &row, &col);

                    if (row > n - 1 || col > n - 1) {
                        printf("Out of range row or column\n");
                        found = true;
                    } else {
                        if (board[row][col] != (char) 'U') {
                            printf("That square is already occupied or blocked\n");
                            found = true;
                        } else {
                            board[row][col] = (char) 'B';
                            printBoard(board, n);
                            found = false;
                            noWinner1 = noWinner(board, n);
                            notFull1 = notFull(board, n);
                        }
                    }

                } while (found);
            }

            //if there is no winner and the board is not full
            if (noWinner1 && notFull1) {

                computerMove(board, n, computerColor, 1);
                printBoard(board, n);
                noWinner1 = noWinner(board, n);
                notFull1 = notFull(board, n);

            }
        }

    } while (noWinner1 && notFull1);

    ///////////////////////////////////////////////
    /////////    FIND THE WINNER      /////////////
    //////////////////////////////////////////////

    //do the following only if there is a winner
    if (noWinner1 == 0) {
        whoIsTheWinner(board, n);
    }

    //do the following only if the board is full

    if (notFull1 == 0)
        printf("Draw!");

    return 0;
}
