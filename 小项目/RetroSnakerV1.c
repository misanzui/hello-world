#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>
#include<winbase.h>
#include<io.h>
#include<conio.h>
#include<shlobj.h>
#include<direct.h>
#include<time.h>

#define leng 16
#define sleep_leng 250

typedef struct position
{
    int x;
    int y;
    struct position *next;
    
}POSITION;

void yun();
int m_yi(POSITION *s,int t);
void clear_screen();
void gotoxy();
void Menu();
void game_init();
void see_num();
void game_start();
POSITION *add_round();
void begin_game();
void biandong();
void set_num();

//蛇的身体
static POSITION *hend;
static int m=0;
static int Fraction;
static short int num[leng][leng];//界面的状态
static POSITION tail;
static int tail_m=5;
void clear_screen(){
    system("cls");
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void gotoxy(int x,int y){
    COORD xy={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void yun(){

    POSITION *feed=hend;
    POSITION *snake=feed->next;
    int x=snake->x,xt=0;
    int y=snake->y,yt=y;//保存现在的头位置;
    int b=m_yi(snake,m);//头移动了
    if (b==1)
    {
        printf("game over");
        system("pause");
        exit(1);
    }else
    if(feed->x==snake->x&&feed->y==snake->y){//吃到食物了
        POSITION *i=add_round();
        POSITION *o=add_round();
        feed->x=i->x;
        feed->y=i->y;
        o->x=x;
        o->y=y;
        o->next=snake->next;
        snake->next=o;
        free(i);
    }else
    {
        POSITION *ts=snake->next;
        while (ts!=NULL)
        {
            xt=ts->x;
            yt=ts->y;
            ts->x=x;
            ts->y=y;
            x=xt;
            y=yt;
            ts=ts->next;
        }   
    }
        
}
void set_num(){
    POSITION *p=hend;
    memset(num,0,sizeof(num));
    num[p->x][p->y]=1;
    p=p->next;
    while (p!=NULL)
    { 
        num[p->x][p->y]=2;
        p=p->next;
    }
   
}
POSITION *add_round(){
    POSITION *T=(POSITION* )malloc(sizeof(POSITION));
    srand((unsigned)time(NULL));
    while (1)
    {
        int x=rand()%16;
        int y=rand()%16;
        if (num[x][y]==0)
        {
            T->x=x;
            T->y=y;
            T->next=NULL;
            break ;
        }else
        {
            continue;
        }
    }
    return T;
}
int m_yi(POSITION *s,int t){
    int x=s->x;
    int y=s->y;
    if (t==0&&x-1>=0)
    {
        x--;
    }
    if (t==1&&x+1<leng)
    {
        x++;
    }
    if (t==2&&y-1>=0)
    {
        y--;
    }
    if (t==3&&y+1<leng)
    {
        y++;
    }
    if (num[x][y]==0||num[x][y]==1);
    {
        s->x=x;
        s->y=y;
        return 0;
    }
    return 1;
}

void biandong(int key){
    
    if (key==72||key==119)
    {
        m=0;
    }
    if (key==80||key==115)
    {
        m=1;
    }
    if (key==75||key==97)
    {
        m=2;
    }
    if (key==77||key==100)
    { 
        m=3;
    }

}

void see_num(){
    int i,j;
    int u=0;
    set_num();
    for (i = 0; i < leng; i++)
    {
        printf("          ■");
        for (j = 0; j < leng; j++)
        {
            u=num[i][j];
            if (u==1)
            {
                gotoxy(j*2+12,i+4);
                printf("○");
            }
            if (u==2||u==3)
            {
                gotoxy(j*2+12,i+4);
                printf("●");
            }
        }
        gotoxy(44,i+4);
        printf("■\n");
    }
    
}
void game_start(){
    int key=0;
    while (1)
    {
        clear_screen();
        printf("\n\n\n");
        printf("          ■■■■■■■■■■■■■■■■■■\n");
        see_num();
        printf("          ■■■■■■■■■■■■■■■■■■\n");
        if (_kbhit())
        {
            key = _getch();
            biandong(key);
            
            
        }
        yun();
        Sleep(1*sleep_leng);
    }
    
    
}
void game_init(){
    clear_screen();
    hend=add_round();
    hend->x=8;
    hend->y=8;
    POSITION *SHhiwi=add_round();
    SHhiwi->next=hend;
    hend=SHhiwi;
    m=rand()%4;
    Fraction=1;
}
void begin_game(){
    char a;
    while (1)
    {
        clear_screen();
        Menu();
        scanf("%c",&a);
        switch ((int)a)
        {
        case 49:game_init();
                game_start();
            break;
        case 50:
            break;
        case 51:
            return;
        default:
            break;
        }

    }
    
}
void Menu(){
    printf("\n\n\n");
    printf("                贪吃蛇1.0              \n\n\n");
    printf("                1.开始游戏             \n\n");
    printf("                2.最 高 分             \n\n");
    printf("                3.退出游戏             \n\n");
    printf("       请输入你要选择的选项:");
}
int main(int argc,char argv[]){
    begin_game();
    system("pause");
    return 0;
}
