#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

typedef struct coordinates
{
    int x;
    int y;
} coordinates;

coordinates easyAlgorithm(int ttt[3][3], int currentPlayer);
coordinates hardAlgorithm(int ttt[3][3], int currentPlayer, coordinates previousCMove, coordinates prevoiusHMove);
coordinates playerChoice(int ttt[3][3], int currentPlayer);
coordinates winSpot(int ttt[3][3], coordinates previousMove, int currentPlayer);
void switchPlayer(int* player);
void showTable(int ttt[3][3]);
void startGame(int select);
int winCondition(int ttt[3][3], coordinates c, int currentPlayer);

int main()
{
    srand(time(0));
    printf("Welcome to TicTacToe made by JovanS\n\n");
    while(1)
    {
        printf("Select an option:\n");
        printf("1.Play with a human\n");
        printf("2.Play with a machine\n");
        printf("3.Exit\n");

        int select;
        scanf("%d", &select);
        if(select == 1 || select == 2)
        {
            startGame(select);
        }
        else if(select == 3)
        {
            printf("Goodbye\n");
            return 0;
        }
        else
        {
            printf("You are stupid try again");
        }
    }
    return 0;
}
void switchPlayer(int* player)
{
    if (*player == 1) *player = 2;
    else *player = 1;
}
void showTable(int ttt[3][3])
{
    printf("=============\n");
    int j, jj;
    for(j = 0; j < 3; j++)
    {
        printf("| ");
        for(jj = 0; jj < 3; jj++)
        {
            if(ttt[j][jj] == 1) printf("x");
            else if(ttt[j][jj] == 2) printf("o");
            else printf(" ");

            printf(" | ");
        }
        printf("\n");
    }
    printf("=============\n");
}
int winCondition(int ttt[3][3], coordinates c, int currentPlayer)
{
    int winner = 0;
    int j;
    bool winV = true;
    bool winH = true;
    bool winMD = false;
    bool winSD = false;

    if(c.y == c.x) winMD = true;
    if(c.y + c.x == 2) winSD = true;
    for(j = 0; j < 3; j++)
    {
        if(winV && ttt[j][c.x] != currentPlayer) winV = false;
        if(winH && ttt[c.y][j] != currentPlayer) winH = false;
        if(winMD && ttt[j][j] != currentPlayer) winMD = false;
        if(winSD && ttt[j][2-j] != currentPlayer) winSD = false;
    }
    if(winV || winH || winMD || winSD)
        winner = currentPlayer;
    return winner;
}
coordinates winSpot(int ttt[3][3], coordinates previousMove, int currentPlayer)
{
    coordinates winningCoordinates;
    winningCoordinates.x = -1;
    winningCoordinates.y = -1;

    coordinates V,H,MD,SD;
    short int winV = 0;
    short int winH = 0;
    short int winMD = 0;
    short int winSD = 0;

    int j;
    for(j = 0; j < 3; j++)
    {
        if(ttt[j][previousMove.x] == currentPlayer) winV++;
        else if(ttt[j][previousMove.x] == 0) {V.x = previousMove.x; V.y = j; }
        else winV = -1;
        
        if(ttt[previousMove.y][j] == currentPlayer) winH++;
        else if(ttt[previousMove.y][j] == 0) {H.x = j; H.y = previousMove.y; }
        else winH = -1;

        if(ttt[j][j] == currentPlayer) winMD++;
        else if(ttt[j][j] == 0) {MD.x = j; MD.y = j; }
        else winMD = -1;

        if(ttt[j][previousMove.x] == currentPlayer) winSD++;
        else if(ttt[j][2-j] == 0) {SD.x = j; SD.y = 2-j; }
        else winSD = -1;
    }
    if(winV == 2) winningCoordinates = V;
    else if(winH == 2) winningCoordinates = H;
    else if(winMD == 2) winningCoordinates = MD;
    else if(winSD == 2) winningCoordinates = SD;

    return winningCoordinates;
}
coordinates playerChoice(int ttt[3][3], int currentPlayer)
{
    coordinates c;
    while(1)
    {
        int selectField;
        printf("Your Choice: ");
        scanf("%d", &selectField);
        selectField--;

        c.x = selectField%3;
        c.y = selectField/3;
        if(selectField >= 0 && selectField < 9 && ttt[c.y][c.x] == 0)
        {
            ttt[c.y][c.x] = currentPlayer;
            break;
        }
        else
        {
            printf("Try Again\n");
        }
    }
    return c;

}
coordinates hardAlgorithm(int ttt[3][3], int currentPlayer, coordinates previousCMove, coordinates previousHMove)
{
    coordinates c;

    bool played = false;
    c.x = -1;
    c.y = -1;

    //play center if it isnt already played
    if(ttt[1][1] == 0)
    {
        c.x = 1;
        c.y = 1;
    }
    else
    {
        //play the winning move
        if(!played)
        {
            c = winSpot(ttt, previousCMove, currentPlayer);
            if(c.x != -1) played = true;
        }
        switchPlayer(&currentPlayer);
        //block player from playing the winning move
        if(!played)
        {          
            c = winSpot(ttt, previousHMove, currentPlayer);
            if(c.x != -1) played = true;
        }
        //dont play corner if player has 2 opposite corners
        if(!played)
        {
            if((ttt[0][0] == currentPlayer && ttt[2][2] == currentPlayer) || (ttt[0][2] == currentPlayer && ttt[2][0] == currentPlayer))
            {

                if(ttt[0][1] == 0)
                {
                    c.x = 1;
                    c.y = 0;
                }
                else if(ttt[1][0] == 0)
                {
                    c.x = 1;
                    c.y = 0;
                }
                else if(ttt[1][2] == 0)
                {
                    c.x = 2;
                    c.y = 1;
                }
                else if(ttt[2][1] == 0)
                {
                    c.x = 1;
                    c.y = 2;
                }
                if(c.x != -1) played = true;
            }
        }
        //dont play side when player has center
        if(!played)
        {
            if(ttt[1][1] == currentPlayer)
            {
                if(ttt[0][0] == 0)
                {
                    c.x = 0;
                    c.y = 0;
                }
                else if(ttt[0][2] == 0)
                {
                    c.x = 2;
                    c.y = 0;
                }
                else if(ttt[2][0] == 0)
                {
                    c.x = 0;
                    c.y = 2;
                }
                else if(ttt[2][2] == 0)
                {
                    c.x = 2;
                    c.y = 2;
                }
            }
            if(c.x != -1) played = true;
        }
        switchPlayer(&currentPlayer);
        //irrelevant cases
        if(!played)
        {
            c = easyAlgorithm(ttt, currentPlayer);
        }

    }
    ttt[c.y][c.x] = currentPlayer;
    return c;
}
coordinates easyAlgorithm(int ttt[3][3], int currentPlayer)
{
    int k = 0,j,jj;
    int freeSpace[9];
    for(j = 0; j < 9; j++) freeSpace[j] = 0;
    
    for(j = 0; j < 3; j++)
    {
        for(jj = 0; jj < 3; jj++)
        {
            if(ttt[j][jj] == 0)
            {
                freeSpace[k] = j * 3 + jj;
                k++;
                
            }
        }
    }  
    int choice = freeSpace[rand()%k];
    coordinates c;
    c.x = choice%3;
    c.y = choice/3;
    ttt[c.y][c.x] = currentPlayer;
    return c;

}
void startGame(int select)
{
    int ttt[3][3],j,jj;
    for(j = 0; j < 3; j++)
    {
        for(jj = 0; jj < 3; jj++)
        {
            ttt[j][jj] = 0;
        }
    }
    int counter = 0;
    if(select == 1)
    {
        while(1)
        {
            showTable(ttt);
            int currentPlayer = counter%2 + 1;
            if(currentPlayer == 1) printf("Player 1 choose field: ");
            else printf("Player 2 choose field: ");

            coordinates c = playerChoice(ttt, currentPlayer);
            int winner = winCondition(ttt, c, currentPlayer);

            counter++;

            if(winner == 1)
            {
                printf("Player one wins\n");
                showTable(ttt);
                break;
            }
            else if(winner == 2)
            {
                printf("Player two wins\n");
                showTable(ttt);
                break;
            }
            else if(counter == 9)
            {
                printf("Draw\n");
                showTable(ttt);
                break;
            }

        }
    }
    else
    {
        int computer = 1;
        int difficulty = 1;
        coordinates previousCMove; previousCMove.x = 0; previousCMove.y = 0;
        coordinates previousHMove; previousHMove.x = 0; previousHMove.y = 0;

        while(1)
        {
            printf("Who goes first?\n1.Computer\n2.Human\n");
            scanf("%d", &select);
            if(select == 1 || select == 2)
            {
                computer = select;
                break;
            }
            else printf("y u so stupid \n");

        }
        while(1)
        {
            printf("Computer difficulty?\n1.Easy\n2.Hard\n");
            scanf("%d", &select);
            if(select == 1 || select == 2)
            {
                difficulty = select;
                break;
            }
            else printf("Try Again\n");
        }
        while(1)
        {
            int currentPlayer = counter%2 + 1;
            int winner;
            coordinates c;
            if(currentPlayer == computer)
            {
               if(difficulty == 1) c = easyAlgorithm(ttt, currentPlayer);
               else c = hardAlgorithm(ttt, currentPlayer, previousCMove, previousHMove);
               printf("Computer choose: x = %d, y = %d\n", c.x, c.y);
               previousCMove = c;
               showTable(ttt);
            }
            else
            {
                c = playerChoice(ttt, currentPlayer);
                previousHMove = c;
            }
            winner = winCondition(ttt,c,currentPlayer);

            counter++;
            if(winner == computer)
            {
                if(difficulty == 1) printf("Easy ");
                else printf("Hard ");
                printf("Computer wins\n");
                showTable(ttt);
                break;
            }
            else if(winner != computer && winner != 0)
            {
                printf("Human wins\n");
                showTable(ttt);
                break;
            }
            else if(counter == 9)
            {
                printf("Draw\n");   
                showTable(ttt);
                break;
            }
        }
    }
}

