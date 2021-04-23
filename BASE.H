/********************************************
 * File: BASE.C                             *
 * Summary of File:                         *
 * 		Description of the basis functions  *
 *                                          *
 * Author: Vakhatov Ivan Alekseevich        *
 * Group: PRI20. 20                         *
 *                                          *
 ********************************************/

#if !defined (_BASE_H_)
#define _BASE_H_

#define MEM (char*) 0xB8000000L

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

#define EMPTY_SYMB 0xB0

/********************************************
 * x: value in the range [1, 23]            *
 * y: value in the range [1, 78]            *
 * ch: any letter or symbol in ASCII        *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void write_char(int x, int y, char ch, char attrib);

/********************************************
 * Calculating the length of a string       *
 *                                          *
 * *str: a string of 1 to 78 symbols long   *
 *                                          *
 * returns: length of the string as integer *
 ********************************************/
int len_str(char *str);

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
void write_string(int x, int y, char *string, char attrib);

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
void *create_buffer(int startx, int starty, int endx, int endy);

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
void get_vmem(int startx, int starty, int endx, int endy, char *buffer);

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
void put_vmem(int startx, int starty, int endx, int endy, char *buffer);

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
void clear(int startx, int starty, int endx, int endy, char ch, char attrib);

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
void border(int startx, int starty, int endx, int endy, char attrib, int typ);

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
void borders(int startx, int starty, int endx, int endy, char attrib);

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
void name(int startx, int starty, int endy, char *string, char attrib);
#endif