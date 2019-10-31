#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <sstream>
#define MAP_WIDTH 50
#define MAP_HEIGTH 20

typedef struct Postion
{
	int x;
	int y;

}Postion;
typedef struct snack
{
	int size;
	Postion pos[MAP_WIDTH * MAP_HEIGTH];
}Snack;

void DrawChar(int x,int y,char ch)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}

Snack g_snack;

Postion g_food;


void Initfood()
{
	srand((unsigned)time(NULL));
	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGTH;
	DrawChar(g_food.x,g_food.y,'#');
}
void InitSnack()
{
	g_snack.size = 3;

	g_snack.pos[0].x = MAP_WIDTH / 2;
	g_snack.pos[0].y = MAP_HEIGTH / 2;

	g_snack.pos[1].x = MAP_WIDTH /2 -1;
	g_snack.pos[1].y = MAP_HEIGTH /2;

	g_snack.pos[2].x = MAP_WIDTH /2-2;
	g_snack.pos[2].y = MAP_HEIGTH /2;
}


void DrawSnack()
{
	for(int i = 0;i<g_snack.size;i++)
	{
		if(i==0)
		{
			DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'*');

		}
		else
		{
			DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'#');
		}	
	}
}
void Init_map()
{
	for(int i =0;i<=MAP_HEIGTH;i++)
	{
		for(int j =0;j<=MAP_WIDTH;j++)
		{
		  if(j==MAP_WIDTH )
		  {
		     printf("|\n");
		  }
		  else if(i ==MAP_HEIGTH)
		  {
			  printf("=");
		  }
		  else
		  {
			  printf(" ");
		  }
		}
	
	}
	
}
void init()
{
	Init_map();
	InitSnack();
	
	DrawSnack();
	Initfood();
}
void UpdateScreen()
{
	DrawSnack();
}
void SnackMove(int key)
{
	int dalta_x = 0;
	int dalta_y = 0;
	if(key == 'w'|| key == 'W')
	{
		dalta_x = 0;
		dalta_y = -1;
	}
	else if(key == 's'|| key == 'S')
	{
		dalta_x = 0;
		dalta_y = 1;

	}
	else if(key == 'a'|| key == 'A')
	{
		dalta_x = -1;
		dalta_y = 0;
	}
	else if(key == 'd'|| key == 'D')
	{
		dalta_x = 1;
		dalta_y = 0;
	}
	else
	{
		return;
	}
	DrawChar(g_snack.pos[g_snack.size -1].x,g_snack.pos[g_snack.size -1].y,' ');
	for(int i =g_snack.size -1;i>0;i--)
	{
		g_snack.pos[i].x = g_snack.pos[i-1].x;
		g_snack.pos[i].y = g_snack.pos[i-1].y;
	}
		g_snack.pos[0].x += dalta_x;
		g_snack.pos[0].y += dalta_y;
	if(g_snack.pos[0].x == g_food.x && g_snack.pos[0].y == g_food.y)
	{
    	g_snack.size++;
		Initfood();
	}
}
void Score()
{

    char sz[10];//字符串
    sprintf(sz, "%d", g_snack.size-3);//这句需要头文件#include <stdio.h>
	for(int i =0;i<strlen(sz);i++)
	{
		DrawChar(30+i,10,sz[i]);
	}
}
void GameLoop()
{
	int key = 0;
	while(1)
	{
		if(_kbhit())
		{
			key = _getch();
		}
		if(key == 'q' || key == 'Q')
		{
		    
			 int ret = MessageBox(NULL,"是否退出游戏","Snack", MB_OKCANCEL );
			 
			 if(ret == IDOK)
			 {
			
		    	return;
			 }
			key =0;
		}
		SnackMove(key);
		if(g_snack.pos[0].x == MAP_WIDTH || g_snack.pos[0].y == MAP_HEIGTH ||g_snack.pos[0].x ==-1 ||g_snack.pos[0].y ==-1)
		{
			Score();
			int ret = MessageBox(NULL,"游戏结束","Snack", MB_OK);
		 
	    	return;	
		}
		UpdateScreen();
		Sleep(100);
	}

}


int main(int argc, char* argv[])
{
	init();

	GameLoop();
	
	Score();
	return 0;
}
