// snack.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include "stafx.h"


#define MAP_WIDTH 60
#define MAP_HEiGTH 60

void Init_map()
{
	for(int i =0; i< MAP_HEIGTH ; i++)
	{
		for(int j = 0;i< MAP_WIDTH ; j++)
		{
			if(j == MAP_WIDTH)
			{
				printf("||\n");
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
}

void GameLoop()
{

}

void Score()
{

}
int main(int argc, char* argv[])
{
	init();
	GameLoop();
	Score();
	return 0;
}

