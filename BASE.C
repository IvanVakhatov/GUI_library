/********************************************
 * File: BASE.C                             *
 * Summary of File:                         *
 *	  The functional of basis functions     *
 *                                          *
 * Author: Vakhatov Ivan Alekseevich        *
 * Group: PRI20. 20                         *
 *                                          *
 ********************************************/

#include <base.h>
#include <stdio.h>
#include <stdlib.h>

/********************************************
 * x: value in the range [1, 23]            *
 * y: value in the range [1, 78]            *
 * ch: any letter or symbol in ASCII        *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void write_char(int x, int y, char ch, char attrib)
{
	char *p;
	p = (MEM + x * 160 + y * 2);
	*p = ch;
	p++;
	*p = attrib;
	p++;
}

/********************************************
 * Calculating the length of a string       *
 *                                          *
 * *str: a string of 1 to 78 symbols long   *
 *                                          *
 * returns: length of the string as integer *
 ********************************************/
int len_str(char *str)
{
	int j = 0;
	while(*str)
	{
		j++;
		str++;
	}
	return j;
}

/********************************************
 * Displaying a string on the screen        *
 *                                          *
 * x: value in the range [1, 23]            *
 * y: value in the range [1, 78]            *
 * *string: a string of 1 to 78 symbols long*
 * attrib: a bit flag (color in CAPITAL)    *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void write_string(int x, int y, char *string, char attrib)
{
	int i;
	for (i = 0; i < len_str(string); i++)
	{
		write_char(x, y+i, string[i], attrib);
	}
}

/********************************************
 * Creating a video memory buffer           *
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endx: value in the range [0, 24]         *
 * endy: value in the range [0, 79]         *
 *                                          *
 * returns: video memory buffer             *
 ********************************************/
void *create_buffer(int startx, int starty, int endx, int endy)
{
	char *buffer;
	int size = (endx - startx + 1) * (endy - starty + 1) * 2 * sizeof(char);
	buffer = malloc(size);
	if (!buffer) {
		fprintf(stderr, "Error");
		exit(1);
	}
	return buffer;
}

/********************************************
 * Writes the current state of the screen   *
 * to the created buffer                    *
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endx: value in the range [0, 24]         *
 * endy: value in the range [0, 79]         *
 * *buffer: previously created              *
 *	video memory buffer                     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void get_vmem(int startx, int starty, int endx, int endy, char *buffer)
{
	char *p;
	int x, y;
	for (x=startx; x<=endx; x++)
	{
		for (y=starty; y<=endy; y++)
		{
			p =  MEM + x*160 + y*2;
			*buffer++ = *p++;
			*buffer++ = *p;
		}
	}
}


/********************************************
 * Reads the current state of the screen    *
 * from the video memory buffer             *
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endx: value in the range [0, 24]         *
 * endy: value in the range [0, 79]         *
 * *buffer: previously created              *
 *	video memory buffer                     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void put_vmem(int startx, int starty, int endx, int endy, char *buffer)
{
	char *p;
	int x, y;
	for (x=startx; x<=endx; x++)
	{
		for (y=starty; y<=endy; y++)
		{
			p =  MEM + x*160 + y*2;
			*p++ = *buffer++;
			*p++ = *buffer++;
		}
	}
}

/********************************************
 * Fills the screen area with a             *
 * specific symbol and attribute            *
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endx: value in the range [0, 24]         *
 * endy: value in the range [0, 79]         *
 * ch: any letter or symbol in ASCII        *
 * attrib: a bit flag (color in CAPITAL)    *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void clear(int startx, int starty, int endx, int endy, char ch, char attrib)
{
	int i, j;
	for (i = startx; i <= endx; i++)
	{
		for (j = starty; j <= endy; j++)
		{
			write_char(i, j, ch, attrib);
		}
	}
}

/********************************************
 * Displays a specific type of screen border*
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endx: value in the range [0, 24]         *
 * endy: value in the range [0, 79]         *
 * attrib: a bit flag (color in CAPITAL)    *
 * typ: value in the range [1, 8]           *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void border(int startx, int starty, int endx, int endy, char attrib, int typ)
{
	int i, j;
	switch (typ)
	{
		case 1:
			write_char(startx, starty, 0xC9, attrib);
			break;
		case 2:
			for (i = starty + 1; i < endy; i++)
				write_char(startx, i, 0xCD, attrib);
			break;
		case 3:
			write_char(startx, endy, 0xBB, attrib);
			break;
		case 4:
			for (j = startx + 1; j < endx; j++)
				write_char(j, endy, 0xBA, attrib);
			break;
		case 5:
			write_char(endx, endy, 0xBC, attrib);
			break;
		case 6:
			for (i = starty + 1; i < endy; i++)
				write_char(endx, i, 0xCD, attrib);
			break;
		case 7:
			write_char(endx, starty, 0xC8, attrib);
			break;
		case 8:
			for (j = startx + 1; j < endx; j++)
				write_char(j, starty, 0xBA, attrib);
			break;
		default:
			break;
	}
}

/********************************************
 * Displays a double-lined border along     *
 * the screen's side                        *
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endx: value in the range [0, 24]         *
 * endy: value in the range [0, 79]         *
 * attrib: a bit flag (color in CAPITAL)    *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void borders(int startx, int starty, int endx, int endy, char attrib)
{
	int i;
	for (i = 1; i < 9; i++)
		border(startx, starty, endx, endy, attrib, i);
}

/********************************************
 * Displays screen's name in the middle     *
 * of the upper border                      *
 *                                          *
 * startx: value in the range [0, 24]       *
 * starty: value in the range [0, 79]       *
 * endy: value in the range [0, 79]         *
 * *string: a string of 1 to 76 symbols long*
 * attrib: a bit flag (color in CAPITAL)    *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void name(int startx, int starty, int endy, char *string, char attrib)
{
	int y = starty + (endy - starty - len_str(string))/2;
	write_string(startx, y, string, attrib);
}