#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void delay(int iLim,int jLim)
{
    int i,j;
    for(i=0;i<iLim;i++)
    {
        for(j=0;j<jLim;j++);
    }
}

void initBorder(char arr[20][20])
{
    int i=0;
    for(i=0;i<20;i++)
    {
        arr[0][i]='*';
        arr[i][0]='*';
        arr[19][i]='*';
        arr[i][19]='*';
    }
}

void printArena(char arr[20][20])
{
    int i=0,j=0;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            cout<<arr[i][j];
        }
        cout<<endl;
    }
}

void printGameOver(char arr[20][20])
{
    arr[7][8]='G';
    system("cls");
    printArena(arr);
    delay(3000,3000);
    arr[7][9]='A';
    system("cls");
    printArena(arr);
    delay(3000,3000);
    arr[7][10]='M';
    system("cls");
    printArena(arr);
    delay(3000,3000);
    arr[7][11]='E';
    system("cls");
    printArena(arr);
    delay(3000,3000);

    arr[9][8]='O';
    system("cls");
    printArena(arr);
    delay(3000,3000);
    arr[9][9]='V';
    system("cls");
    printArena(arr);
    delay(3000,3000);
    arr[9][10]='E';
    system("cls");
    printArena(arr);
    delay(3000,3000);
    arr[9][11]='R';
    system("cls");
    printArena(arr);
    delay(3000,3000);
}

struct snake
{
    int snakeI;
    int snakeJ;
};

void updateSnake(int len,struct snake snakeArr[])
{
    int i;
    for(i=len-1;i>0;i--)
    {
        snakeArr[i].snakeI=snakeArr[i-1].snakeI;
        snakeArr[i].snakeJ=snakeArr[i-1].snakeJ;
    }
}

int main()
{
    system("cls");
    char arr[20][20]={" "};
    char input,prevInput='p';
    snake snakeArr[324];            //since the max length of snake can be of 18*18, filling whole arena
    int len=1;
    int moveI=0,moveJ=0;
    int foodI=1,foodJ=1;
    bool gameFlag=true;
    int pts=0;
    initBorder(arr);

    //arr[snakeI][snakeJ]='*';
    printArena(arr);

    srand(time(NULL));
    foodI= 1+rand()%18;
    foodJ= 1+rand()%18;
    arr[foodI][foodJ]='O';

    snakeArr[0].snakeI=10;
    snakeArr[0].snakeJ=10;

    while(gameFlag)            // 27 is ASCII value of escape
    {
        if(kbhit())
        {
            input=getch();
            if(input=='w' && prevInput!='s')
            {
                moveI=-1;
                moveJ=0;
                prevInput=input;
            }
            else if(input=='a' && prevInput!='d')
            {
                moveI=0;
                moveJ=-1;
                prevInput=input;
            }
            else if(input=='s' && prevInput!='w')
            {
                moveI=1;
                moveJ=0;
                prevInput=input;
            }
            else if(input=='d' && prevInput!='a')
            {
                moveI=0;
                moveJ=1;
                prevInput=input;
            }
            else if(input=='p')
            {
                moveI=0;
                moveJ=0;
            }
            else if(input==27)
            {
                gameFlag=false;
                continue;
            }
        }

        arr[snakeArr[len-1].snakeI][snakeArr[len-1].snakeJ]=' ';
        updateSnake(len,snakeArr);
        snakeArr[0].snakeI += moveI;
        snakeArr[0].snakeJ += moveJ;

        if(arr[snakeArr[0].snakeI][snakeArr[0].snakeJ]=='*')
        {
            gameFlag=false;
            continue;
        }

        if(arr[snakeArr[0].snakeI][snakeArr[0].snakeJ]=='O')
        {
            pts++;
            snakeArr[len].snakeI = snakeArr[len-1].snakeI;
            snakeArr[len].snakeJ = snakeArr[len-1].snakeJ;
            len++;
            do
            {
                foodI= 1+rand()%18;
                foodJ= 1+rand()%18;
            }while(arr[foodI][foodJ]=='*');
            arr[foodI][foodJ]='O';
        }

        arr[snakeArr[0].snakeI][snakeArr[0].snakeJ]='*';

        delay(9000,3000);           //Change the values to adjust the speed
        system("cls");
        printArena(arr);
    }
    system("cls");
    //arr[snakeI][snakeJ]=' ';
    printGameOver(arr);
    cout<<endl<<"Final Score : "<<pts;
    cout<<endl<<"Press enter to finish...";
    cin.clear();
    cin.ignore(5,'\n');
    return 0;
}
