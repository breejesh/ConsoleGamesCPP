#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

/*************** Arena ******************/

void initBorders(char arena[20][20])
{
    for(int i=0;i<20;i++)
    {
        arena[i][0]=186;
        arena[0][i]=205;
        arena[i][19]=186;
        arena[19][i]=205;
    }
    arena[19][0]=200;
    arena[19][19]=188;
    arena[0][0]=201;
    arena[0][19]=187;
}
void initSprites(char arena[20][20],int mid)
{
    // Paddle

    arena[17][mid-2]='-';
    arena[17][mid-1]='-';
    arena[17][mid]='-';
    arena[17][mid+1]='-';
    arena[17][mid+2]='-';

    //Ball
    arena[9][9]='o';
}
void updateArena(char arena[20][20],int life)
{
    for(int i=19;i>0;i--)
        for(int j=1;j<19;j++)
            {


            }
}

void movePaddle(char arena[20][20],char input, int &pos,int &padDir)
{
    if(input=='a' && pos>3)
    {
            arena[17][pos-3]='-';
            arena[17][pos+2]=' ';
            pos-=1;
            padDir=-1;
    }
    else if(input=='d' && pos<16)
    {
        arena[17][pos+3]='-';
        arena[17][pos-2]=' ';
        pos+=1;
        padDir=1;
    }
    else padDir=0;

}

void delay(int outer=5000,int inner=2000)
{
    for(int i=0;i<outer;i++)
        for(int j=0;j<inner;j++);
}

void reset(char arena[20][20])
{
    char arena2[20][20]={" "};
    arena=arena2;
    initSprites(arena,9);
    initBorders(arena);
}
void moveBall(char arena[20][20],int &ballX,int &ballY,int &ballXvector,int &ballYvector,int padDir)
{
    ballX+=ballXvector;
    ballY+=ballYvector;
    if(ballX >= 17)
    {
       ballY-=ballYvector;
        if(arena[ballX][ballY]=='-')
        {
            ballY+=ballYvector;
            ballYvector+=padDir;
            if(ballYvector<-3)
            {
                ballYvector=-3;
            }
            else if(ballYvector >3)
            {
                ballYvector=3;
            }
            ballXvector=-ballXvector;
            ballX+=ballXvector;
            ballY+=ballYvector;
        }
        else
        {
            reset(arena);
            ballX=9;
            ballY=9;
            ballXvector=1;
            ballYvector=0;
            getch();
            return;
        }
    }
    else if(ballY > 18)
    {
        ballYvector=-ballYvector;
        ballY=18;
    }
    else if(ballY < 1)
    {
        ballYvector=-ballYvector;
        ballY=1;
    }
    else if(ballX <= 1)
    {
        ballXvector=-ballXvector;
        ballX=1;
    }


}

void display(char arena[20][20])
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
            cout<<arena[i][j];
        cout<<endl;
    }
}



int main()
{
    char arena[20][20]={" "};
    char input=0;
    int ballX=9,ballY=9,ballXvector=1,ballYvector=0;
    int pos=9;
    int padDir=0;
    initBorders(arena);
    initSprites(arena,pos);
    display(arena);
    while(input!=27)
    {
        if(kbhit())
        {
            input=getch();
            movePaddle(arena,input,pos,padDir);
        }
        arena[ballX][ballY]=' ';
        moveBall(arena,ballX,ballY,ballXvector,ballYvector,padDir);
        arena[ballX][ballY]='O';
        system("cls");
        display(arena);
        delay();
    }
    return 0;
}
