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
	int msg;
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
	
	msg = get_error();
	if (msg == 0)
	{	
		w->startx = startx;
		w->endx = endx;
		w->starty = starty;
		w->endy = endy;
		w->attrib = attrib;
		strcpy(w->name, name);
		w->p = malloc(sizeof(w));
		w->buffer = create_buffer(w->startx, w->starty, w->endx, w->endy);
		w->active = 1;
	}
	else
	{
		w->p = malloc(sizeof(w));
		w->active = 0;
	}
	return w;
}

/********************************************
 * Shows the contents of the window         *
 * 		If ACTIVE flag = 1                  *
 *                                          *
 * *w: previously created window object     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void window_open(window_t *w)
{
	if (w->active == 1)
	{
		get_vmem(w->startx, w->starty, w->endx, w->endy, w->buffer);
		clear(w->startx, w->starty, w->endx, w->endy, EMPTY_SYMB, w->attrib);
		borders(w->startx, w->starty, w->endx, w->endy, w->attrib);
		name(w->startx, w->starty, w->endy, w->name, w->attrib);
	}
}

/********************************************
 * Close the window by opening the          *
 * initial state of the window              *
 * 		If ACTIVE flag = 1                  *
 *                                          *
 * *w: previously created window object     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void window_close(window_t *w)
{
	if (w->active == 1)
	{
		put_vmem(w->startx, w->starty, w->endx, w->endy, w->buffer);
		getch();
	}
}

/********************************************
 * Clears the memory of window object       *
 *                                          *
 * *w: previously created window object     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void window_destroy(window_t *w)
{
	free(w->p);
	free(w);	
}

/********************************************
 * If something went wrong creating a       *
 * window object, you would know it!        *
 *                                          *
 *                                          *
 *                                          *
 * returns: error code (if errors)          *
 ********************************************/
int get_error(void)
{
	return INTERRUPT;
}

/********************************************
 * Allow to move the string in rect window  *
 * (using UP, DOWN, LEFT, RIGHT arrows)     *
 * 		If ACTIVE flag = 1                  *
 *                                          *
 * *string: a string of 1 to 77 symbols long*
 * *w: previously created window object     *
 * s_attrib: a bit flag (color in CAPITAL)  *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void move_string(char *string, window_t *w, char s_attrib)
{
	if (w->active == 1)
	{
		if (len_str(string) < (w->endy - 2))
		{
			char key = 0;
			int x = w->startx+1;
			int y = w->starty+1;
			
			/* While ESC is not pressed */
			while(key != 0x1b)
			{
				/* If any key has been pressed */
				if(kbhit())
				{
					key = getch();
					if(key == (char)0)
					{
						key = getch();
						/* Key handling */
						switch(key)
						{
							case 0x48: /*up arrow*/
								x -= 1;
								if(x < w->startx+1)
								{
									x = w->startx+1;
								}
								clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
								break;
									
							case 0x4d: /*right arrow*/
								y += 2;
								if(y > w->endy-len_str(string))
								{
									y = w->endy-len_str(string);
								}
								clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
								break;

							case 0x50: /*down arrow*/
								x += 1;
								if(x > w->endx-1)
								{
									x = w->endx-1;
								}
								clear(w->startx+1, w->starty+1, w->endx-1, w->endy-1, 0xB0, w->attrib);
								break;
									
							case 0x4b: /*left arrow*/
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
			getch();
		}
	}
}

/********************************************
 * Allows user to enter color and background*
 * color values of symbols. Checks the      *
 * entered value and handles errors         *
 *                                          *
 * *type: object type for the attribute     *
 *                                          *
 * returns: final attrib for symbols        *
 ********************************************/
char attrib_valid(char *type)
{
	char *COLORS[] = {"BLACK", "BLUE", "GREEN", "CYAN", "RED",
					"MAGENTA", "BROWN", "LIGHTGRAY", "DARKGRAY",
					"LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN",
					"LIGHTRED", "LIGHTMAGENTA", "YELLOW"};
	char *BGCOLORS[] = {"BGBLACK", "BGBLUE", "BGGREEN", "BGCYAN",
					"BGRED", "BGMAGENTA", "BGBROWN", "BGLIGHTGRAY"};
	char *COLOR =  (char*)malloc(100);
	char *BGCOLOR = (char*)malloc(100);
	char col, bgcol, attrib;
	int i, col_len = sizeof(COLORS)/sizeof(COLORS[0]);
	int bgcol_len = sizeof(BGCOLORS)/sizeof(BGCOLORS[0]);

	clrscr();
	if (strcmp(type, "W1") == 0)
		instructions(3);
	else if (strcmp(type, "W2") == 0)
		instructions(4);
	else if (strcmp(type, "STR1") == 0)
		instructions(5);
	else if (strcmp(type, "STR2") == 0)
		instructions(6);
			
	while (1)
	{
		instructions(1);
		printf("Enter the color value in CAPITAL: ");
		scanf("%s", COLOR);
		
		col = 0x15;
		for(i = 0; i < col_len; ++i)
		{
			if(strcmp(COLORS[i], COLOR) == 0)
			{
				if (strcmp(COLOR, "BLACK") == 0)
					col = BLACK;
				else if (strcmp(COLOR, "BLUE") == 0)
					col = BLUE;
				else if (strcmp(COLOR, "GREEN") == 0)
					col = GREEN;
				else if (strcmp(COLOR, "CYAN") == 0)
					col = CYAN;
				else if (strcmp(COLOR, "RED") == 0)
					col = RED;
				else if (strcmp(COLOR, "MAGENTA") == 0)
					col = MAGENTA;
				else if (strcmp(COLOR, "BROWN") == 0)
					col = BROWN;
				else if (strcmp(COLOR, "LIGHTGRAY") == 0)
					col = LIGHTGRAY;
				else if (strcmp(COLOR, "DARKGRAY") == 0)
					col = DARKGRAY;
				else if (strcmp(COLOR, "LIGHTBLUE") == 0)
					col = LIGHTBLUE;
				else if (strcmp(COLOR, "LIGHTGREEN") == 0)
					col = LIGHTGREEN;
				else if (strcmp(COLOR, "LIGHTCYAN") == 0)
					col = LIGHTCYAN;
				else if (strcmp(COLOR, "LIGHTRED") == 0)
					col = LIGHTRED;
				else if (strcmp(COLOR, "LIGHTMAGENTA") == 0)
					col = LIGHTMAGENTA;
				else if (strcmp(COLOR, "YELLOW") == 0)
					col = YELLOW;
				else if (strcmp(COLOR, "WHITE") == 0)
					col = WHITE;
			}
		}
		if (col != 0x15)
		{
			printf("\nOK! Selected color: %s\n\n", COLOR);
			break;
		}
		else
		{
			printf("\nINVALID COLOR VALUE! Try again.\n\n");
		}
	}
	
	while (1)
	{
		instructions(2);
		printf("Enter the background color value in CAPITAL: ");
		scanf("%s", BGCOLOR);
		
		bgcol = 0x7E;			
		for(i = 0; i < bgcol_len; ++i)
		{
			if(strcmp(BGCOLORS[i], BGCOLOR) == 0)
			{
				if (strcmp(BGCOLOR, "BGBLACK") == 0)
					bgcol = BGBLACK;
				else if (strcmp(BGCOLOR, "BGBLUE") == 0)
					bgcol = BGBLUE;
				else if (strcmp(BGCOLOR, "BGGREEN") == 0)
					bgcol = BGGREEN;
				else if (strcmp(BGCOLOR, "BGCYAN") == 0)
					bgcol = BGCYAN;
				else if (strcmp(BGCOLOR, "BGRED") == 0)
					bgcol = BGRED;
				else if (strcmp(BGCOLOR, "BGMAGENTA") == 0)
					bgcol = BGMAGENTA;
				else if (strcmp(BGCOLOR, "BGBROWN") == 0)
					bgcol = BGBROWN;
				else if (strcmp(BGCOLOR, "BGLIGHTGRAY") == 0)
					bgcol = BGLIGHTGRAY;
			}
		}
		if (bgcol != 0x7E)
		{
			printf("\nOK! Selected background color: %s\n\n", BGCOLOR);
			break;
		}
		else
		{
			printf("\nINVALID BACKGROUND COLOR VALUE! Try again.\n\n");
		}
	}
	
	attrib = col | bgcol;
	free(COLOR);
	free(BGCOLOR);
	return attrib;
}

/********************************************
 * Prints the help messages for user        *
 *                                          *
 * number: utility variable for SWITCH      *
 *                                          *
 * returns: nothing                         *
 ********************************************/
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
}