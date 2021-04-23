/********************************************
 * File: WINDOW.C                           *
 * Summary of File:                         *
 *	  The functional of window functions    *
 *                                          *
 * Author: Vakhatov Ivan Alekseevich        *
 * Group: PRI20. 20                         *
 *                                          *
 ********************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <window.h>
#include <base.h>

#define MEMERROR 1
#define XERROR 2
#define YERROR 3
#define STRERROR 4

int INTERRUPT;

/********************************************
 * Creates a window structure object        *
 *                                          *
 * *name: a string of 1 to 78 symbols long  *
 * startx: value in the range [0, 24]       *
 * endx: value in the range [0, 24]         *
 * starty: value in the range [0, 79]       *
 * endy: value in the range [0, 79]         *
 * attrib: a bit flag (color in CAPITAL)    *
 *                                          *
 * returns: created window object           *
 ********************************************/
window_t *window_create(char *name, int startx, int endx, int starty, int endy, char attrib)
{
	window_t *w = malloc(sizeof(window_t));
	INTERRUPT = 0;
	if (w == NULL)
	{
		INTERRUPT = MEMERROR;
	}
	
	else if (startx < 0 || startx > 24 || endx > 24 || endx < 0 || startx >= endx)
	{
		INTERRUPT = XERROR;
	}
	
	else if (starty < 0 || starty > 79 || endy > 79 || endy < 0 || starty >= endy)
	{
		INTERRUPT = YERROR;
	}
	
	else if (len_str(name) > (endy - 2))
	{
		INTERRUPT = STRERROR;
	}
	
	w->startx = startx;
	w->endx = endx;
	w->starty = starty;
	w->endy = endy;
	w->attrib = attrib;
	strcpy(w->name, name);
	w->p = malloc(sizeof(w));
	w->buffer = create_buffer(w->startx, w->starty, w->endx, w->endy);
	return w;
}

void window_open(window_t *w)
{
		get_vmem(w->startx, w->starty, w->endx, w->endy, w->buffer);
		clear(w->startx, w->starty, w->endx, w->endy, 0xB0, w->attrib);
		borders(w->startx, w->starty, w->endx, w->endy, w->attrib);
		name(w->startx, w->starty, w->endy, w->name, w->attrib);
}

void move_string(window_t *w, char s_attrib)
{
	char key = 0, *string = "IVAN";
	int x = w->startx+5;
	int y = w->starty+5;
	
	/* While ESC is not pressed */
	while(key != 0x1b)
	{
		if(kbhit()) /* If a key has been pressed */
		{
			key = getch();
			if(key == (char)0)
			{
				key = getch();
				/* Key handling */
				switch(key)
				{
					case 0x48: /*up key*/
						x -= 1;
						if(x < w->startx+1)
						{
							x = w->startx+1;
						}
						clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
						break;
							
					case 0x4d: /*right key*/
						y += 2;
						if(y > w->endy-len_str(string))
						{
							y = w->endy-len_str(string);
						}
						clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
						break;

					case 0x50: /*down key*/
						x += 1;
						if(x > w->endx-1)
						{
							x = w->endx-1;
						}
						clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
						break;
							
					case 0x4b: /*left key*/
						y -= 2;
						if(y < w->starty+1)
						{
							y = w->starty+1;
						}
						clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
						break;
					default: /* other keys */
						break;
				}
			}
		}
		write_string(x, y, string, s_attrib);
	}
}

void window_close(window_t *w)
{

	put_vmem(w->startx, w->starty, w->endx, w->endy, w->buffer);
}

void window_destroy(window_t *w)
{
	free(w->p);
	free(w);	
}

int get_error(void)
{
	return INTERRUPT;
}

char attrib_valid(void)
{
	char *COLORS = "BLACKBLUEGREENCYANREDMAGENTABROWNLIGHTGRAYDARKGRAYLIGHTBLUELIGHTGREENLIGHTCYANLIGHTREDLIGHTMAGENTAYELLOW";
	char *BGCOLORS = "BGBLACK_BGBLUE_BGGREEN_BGCYAN_BGRED_BGMAGENTA_BGBROWN_BGLIGHTGRAY";
	char *COLOR =  (char*)malloc(100);
	char *BGCOLOR = (char*)malloc(100);
	char c, bgc, attrib;
	
	while (1)
	{
		instructions(1);
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
		instructions(2);
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

void instructions(int number)
{
	switch(number)
	{
		case 1:
			printf("Available color values: \n");
			printf("\tBLACK; BLUE; GREEN; CYAN; RED; MAGENTA; BROWN; LIGHTGRAY; DARKGRAY;\n");
			printf("\tLIGHTBLUE; LIGHTGREEN; LIGHTCYAN; LIGHTRED; LIGHTMAGENTA; YELLOW\n\n");
			break;
		case 2:
			printf("Available background color values: \n");
			printf("\tBGBLACK; BGBLUE; BGGREEN; BGCYAN; BGRED;\n");
			printf("\tBGMAGENTA; BGBROWN; BGLIGHTGRAY\n\n");
			break;
		case 3:
			printf("Enter the color and background color values of the first window, please.\n\n");
			break;
		case 4:
			printf("Enter the color and background color values of the second window, please.\n\n");
			break;
		case 5:
			printf("Enter the color and background color values of the first string, please.\n\n");
			break;
		case 6:
			printf("Enter the color and background color values of the second string, please.\n\n");
			break;
		case 7:
			printf("Press ESC to exit from string manipulation.\n\n");
			printf("Move the text by pressing the arrows on the keyboard:\n");
			printf("\tUP; DOWN; LEFT; RIGHT;\n");
			break;
	}
}