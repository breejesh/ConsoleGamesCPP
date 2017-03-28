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


void updateArena(char arena[20][20],int &life)
{
    for(int i=19;i>0;i--)
        for(int j=1;j<19;j++)
            {
                arena[i][j]=arena[i-1][j];
                if(i==1)
                {
                    arena[i][j]=' ';
                }
                if(i==19)
                {
                    arena[i][j]=205;
                    if(arena[i-1][j]>='a' && arena[i-1][j]<='z'  )
                    {
                        life--;                                             //Letter touched the 'ground'
                    }
                }
            }
}


/*************** Game Helpers *************/

void generateLetter(char arena[20][20])
{
    char letter = 'a' + rand()%26;            // A random letter
    int pos = 1 + rand()%18;                  // A random column
    while(arena[1][pos]>='a' && arena[1][pos]<='z')
    {

        pos = 1 + rand()%18;
    }
    arena[1][pos]=letter;
}

void checkHit(char arena[20][20],char input,int &score,int &difficulty)  // Maybe inefficient but anyways the time complexity was n2
{
    for(int i=18;i>0;i--)
    {
        for(int j=1;j<19;j++)
        {
            if(arena[i][j]==input)
            {
                arena[i][j]=' ';
                score++;
                difficulty+=2;
                if(rand()%3==1)                                        // 1/3 probability of generating a letter
                    generateLetter(arena);
                return;
            }
        }
    }
}

/******************* MISC ******************/

void display(char arena[20][20])
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
            cout<<arena[i][j];
        cout<<endl;
    }
}

void delay(int outer=5000,int inner=20000)
{
    for(int i=0;i<outer;i++)
        for(int j=0;j<inner;j++);
}


void printGameOver(char arena[20][20])                      //Credits : Sagar Kamdar
{
    arena[7][8]='G';
    system("cls");
    display(arena);
    delay();
    arena[7][9]='A';
    system("cls");
    display(arena);
    delay();
    arena[7][10]='M';
    system("cls");
    display(arena);
    delay();
    arena[7][11]='E';
    system("cls");
    display(arena);
    delay();

    arena[9][8]='O';
    system("cls");
    display(arena);
    delay();
    arena[9][9]='V';
    system("cls");
    display(arena);
    delay();
    arena[9][10]='E';
    system("cls");
    display(arena);
    delay();
    arena[9][11]='R';
    system("cls");
    display(arena);
    delay();
}

/***************** Main **********************/

int main()
{
    /********* Variables ********/

    char arena[20][20] = {" "};
    char input = 0;
    int difficulty = 10,score = 1,life=5,generater=0;
    int fakeTime=1;

    /******* Init *********/

    srand (time(NULL));
    initBorders(arena);
    generateLetter(arena);
    display(arena);

    /************* Game Loop ****************/

    cout<<endl<<"Press Enter to start...";
    while(input!=13)
    {
        if(kbhit())
        {
            input = getch();
        }
    }
    while(input != 27)
    {
        if(kbhit())
        {
            input = getch();
            checkHit(arena,input,score,difficulty);
        }
        updateArena(arena,life);
        if(life<0)
            break;
        if(fakeTime%4==0)                                           // one letter in every 4 fake seconds
            {
                generateLetter(arena);
            }
        system("cls");
        display(arena);
        cout<<endl<<"Score : "<<score-1;
        cout<<endl<<"Lives : "<<life;
        delay((50)*(100-0.2*difficulty),(200)*(100-0.2*difficulty));    // 'difficulty' not needed as such, 'score' can be used
        fakeTime++;
    }
    system("cls");
    printGameOver(arena);
    cout<<endl<<char(176) <<" Final Score : "<<score-1;
    cout<<endl<<"Press Enter to finish...";
    cin.clear();
    cin.ignore(5,'\n');
    return 0;
}
