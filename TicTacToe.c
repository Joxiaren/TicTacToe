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
struct coordinates hardAlgorithm(int ttt[3][3], int currentPlayer);

void showTable(int ttt[3][3])
{
    for(int j = 0; j < 3; j++)
    {
        for(int jj = 0; jj < 3; jj++)
        {
            printf("%d", ttt[j][jj]);
            printf(" ");
        }
        printf("\n");
    }
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
struct coordinates playerChoice(int ttt[3][3], int currentPlayer)
{
    struct coordinates c;
    while(1)
    {
        int selectField;
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
struct coordinates hardAlgorithm(int ttt[3][3], int currentPLayer)
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
        if(!played)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int jj = 0; jj < 3; jj++)
                {
                    if(ttt[j][jj] == 0)
                    {
                        int hor = 0;
                        int ver = 0;
                        int mdi = 0;
                        int sdi = 0;
                        if(j != jj) mdi = -1;
                        if(j+jj != 2) sdi = -1;

                        for(int jjj = 0; jjj < 3; jjj++)
                        {
                            if(hor != -1)
                            {
                                
                            }
                        }
                    }
                }
            }
        }
        if(!played)
        {

        }

    }
    if(c.x == -1  && c.y == -1) c = easyAlgorithm(ttt,currentPLayer);
    return c;
}
struct coordinates easyAlgorithm(int ttt[3][3], int currentPlayer)
{
    int k = 0;
    int freeSpace[9];
    for(int j = 0; j < 9; j++) freeSpace[j] = 0;
    printf("\nFree spaces:");
    for(int j = 0; j < 3; j++)
    {
        for(int jj = 0; jj < 3; jj++)
        {
            if(ttt[j][jj] == 0)
            {
                freeSpace[k] = j * 3 + jj;
                k++;
                printf(" %d", freeSpace[k-1]);
            }
        }
    }
    printf("\n");
    int choice = freeSpace[rand()%k];
    printf("Computer choose: %d\n", choice);
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
               else c = hardAlgorithm(ttt, currentPlayer);
               showTable(ttt);
            }
            else
            {
                c = playerChoice(ttt, currentPlayer);
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
