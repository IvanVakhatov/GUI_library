#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define LIGHTGRAY 0x07
#define DARKGRAY 0x08
#define LIGHTBLUE 0x09
#define LIGHTGREEN 0x0A
#define LIGHTCYAN 0x0B
#define LIGHTRED 0x0C
#define LIGHTMAGENTA 0x0D
#define YELLOW 0x0E
#define WHITE 0x0F

#define BGBLACK 0x00
#define BGBLUE 0x10
#define BGGREEN 0x20
#define BGCYAN 0x30
#define BGRED 0x40
#define BGMAGENTA 0x50
#define BGBROWN 0x60
#define BGLIGHTGRAY 0x70

char attrib_valid(void)
{
	char *COLORS = "BLACKBLUEGREENCYANREDMAGENTABROWNLIGHTGRAYDARKGRAYLIGHTBLUELIGHTGREENLIGHTCYANLIGHTREDLIGHTMAGENTAYELLOW";
	char *BGCOLORS = "BGBLACK_BGBLUE_BGGREEN_BGCYAN_BGRED_BGMAGENTA_BGBROWN_BGLIGHTGRAY";
	char *COLOR =  (char*)malloc(100);
	char *BGCOLOR = (char*)malloc(100);
	char c, bgc, attrib;
	
	clrscr();
	while (1)
	{
		printf("Enter the color value in CAPITAL: ");
		scanf("%s", COLOR);
		if(strstr(COLORS, COLOR) != NULL)
		{
			if (strcmp(COLOR, "BLACK") == 0)
				c = BLACK;
			else if (strcmp(COLOR, "BLUE") == 0)
				c = BLUE;
			else if (strcmp(COLOR, "GREEN") == 0)
				c = GREEN;
			else if (strcmp(COLOR, "CYAN") == 0)
				c = CYAN;
			else if (strcmp(COLOR, "RED") == 0)
				c = RED;
			else if (strcmp(COLOR, "MAGENTA") == 0)
				c = MAGENTA;
			else if (strcmp(COLOR, "BROWN") == 0)
				c = BROWN;
			else if (strcmp(COLOR, "LIGHTGRAY") == 0)
				c = LIGHTGRAY;
			else if (strcmp(COLOR, "DARKGRAY") == 0)
				c = DARKGRAY;
			else if (strcmp(COLOR, "LIGHTBLUE") == 0)
				c = LIGHTBLUE;
			else if (strcmp(COLOR, "LIGHTGREEN") == 0)
				c = LIGHTGREEN;
			else if (strcmp(COLOR, "LIGHTCYAN") == 0)
				c = LIGHTCYAN;
			else if (strcmp(COLOR, "LIGHTRED") == 0)
				c = LIGHTRED;
			else if (strcmp(COLOR, "LIGHTMAGENTA") == 0)
				c = LIGHTMAGENTA;
			else if (strcmp(COLOR, "YELLOW") == 0)
				c = YELLOW;
			else if (strcmp(COLOR, "WHITE") == 0)
				c = WHITE;
			else
				c = 0;
			printf("OK!\n");
			break;
		}
		else
		{
			printf("INVALID COLOR! Try again.\n");
		}
	}
	
	while (1)
	{
		printf("Enter the background color value in CAPITAL: ");
		scanf("%s", BGCOLOR);
		if(strstr(BGCOLORS, BGCOLOR) != NULL)
		{
			if (strcmp(BGCOLOR, "BGBLACK") == 0)
				bgc = BGBLACK;
			else if (strcmp(BGCOLOR, "BGBLUE") == 0)
				bgc = BGBLUE;
			else if (strcmp(BGCOLOR, "BGGREEN") == 0)
				bgc = BGGREEN;
			else if (strcmp(BGCOLOR, "BGCYAN") == 0)
				bgc = BGCYAN;
			else if (strcmp(BGCOLOR, "BGRED") == 0)
				bgc = BGRED;
			else if (strcmp(BGCOLOR, "BGMAGENTA") == 0)
				bgc = BGMAGENTA;
			else if (strcmp(BGCOLOR, "BGBROWN") == 0)
				bgc = BGBROWN;
			else if (strcmp(BGCOLOR, "BGLIGHTGRAY") == 0)
				bgc = BGLIGHTGRAY;
			else
				bgc = 0;
			printf("OK!\n");
			break;
		}
		else
		{
			printf("INVALID COLOR! Try again.\n");
		}
	}
	
	attrib = c | bgc;
	getch();
	free(COLOR);
	free(BGCOLOR);
	return attrib;
}

int main()
{
	char attrib = attrib_valid();
	printf("FINAL ATTRIB: %x\n", attrib);
	getch();
	return 0;
}
