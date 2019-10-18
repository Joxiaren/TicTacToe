#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>




struct coordinates
{
    int x;
    int y;
};

struct coordinates easyAlgorithm(int ttt[3][3], int currentPlayer);
struct coordinates hardAlgorithm(int ttt[3][3], int currentPlayer, struct coordinates previousCMove, struct coordinates prevoiusHMove);
struct coordinates playerChoice(int ttt[3][3], int currentPlayer);
struct coordinates winSpot(int ttt[3][3], struct coordinates previousMove, int currentPlayer);
void showTable(int ttt[3][3]);
void startGame(int select);
int winCondition(int ttt[3][3], struct coordinates c, int currentPlayer);

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

void showTable(int ttt[3][3])
{
    printf("=============\n");
    for(int j = 0; j < 3; j++)
    {
        printf("| ");
        for(int jj = 0; jj < 3; jj++)
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
int winCondition(int ttt[3][3], struct coordinates c, int currentPlayer)
{
    int winner = 0;
    bool winV = true;
    bool winH = true;
    bool winMD = false;
    bool winSD = false;

    if(c.y == c.x) winMD = true;
    if(c.y + c.x == 2) winSD = true;
    for(int j = 0; j < 3; j++)
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
struct coordinates winSpot(int ttt[3][3], struct coordinates previousMove, int currentPlayer)
{
    struct coordinates winningCoordinates;
    winningCoordinates.x = -1;
    winningCoordinates.y = -1;

    struct coordinates V,H,MD,SD;
    short int winV = 0;
    short int winH = 0;
    short int winMD = 0;
    short int winSD = 0;

    for(int j = 0; j < 3; j++)
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
struct coordinates playerChoice(int ttt[3][3], int currentPlayer)
{
    struct coordinates c;
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
struct coordinates hardAlgorithm(int ttt[3][3], int currentPLayer, struct coordinates previousCMove, struct coordinates previousHMove)
{
    struct coordinates c;

    bool played = false;
    c.x = -1;
    c.y = -1;
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
            c = winSpot(ttt, previousCMove, currentPLayer);
            if(c.x != -1) played = true;
        }
        //block player from playing the winning move
        if(!played)
        {
            if(currentPLayer == 1) currentPLayer = 2;
            else currentPLayer = 1;
            
            c = winSpot(ttt, previousHMove, currentPLayer);
            if(c.x != -1) played = true;
            
            if(currentPLayer == 1) currentPLayer = 2;
            else currentPLayer = 1;
        }
        //dont play corner if player has 2 opposite corners
        //dont play side when player has center
        
        //irrelevant cases
        if(!played)
        {
            c = easyAlgorithm(ttt, currentPLayer);
        }

    }
    ttt[c.y][c.x] = currentPLayer;
    return c;
}
struct coordinates easyAlgorithm(int ttt[3][3], int currentPlayer)
{
    int k = 0;
    int freeSpace[9];
    for(int j = 0; j < 9; j++) freeSpace[j] = 0;
    
    for(int j = 0; j < 3; j++)
    {
        for(int jj = 0; jj < 3; jj++)
        {
            if(ttt[j][jj] == 0)
            {
                freeSpace[k] = j * 3 + jj;
                k++;
                
            }
        }
    }  
    int choice = freeSpace[rand()%k];
    struct coordinates c;
    c.x = choice%3;
    c.y = choice/3;
    ttt[c.y][c.x] = currentPlayer;
    return c;

}
void startGame(int select)
{
    int ttt[3][3];
    for(int j = 0; j < 3; j++)
    {
        for(int jj = 0; jj < 3; jj++)
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

            struct coordinates c = playerChoice(ttt, currentPlayer);
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
        struct coordinates previousCMove; previousCMove.x = 0; previousCMove.y = 0;
        struct coordinates previousHMove; previousHMove.x = 0; previousHMove.y = 0;

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
            struct coordinates c;
            if(currentPlayer == computer)
            {
               if(difficulty == 1) c =  easyAlgorithm(ttt, currentPlayer);
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

