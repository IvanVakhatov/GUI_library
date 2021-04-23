#ifndef WINDOW_H_
#define WINDOW_H_

typedef struct window {
	int startx, starty, endx, endy;
	char attrib;
	char name[80];
	char *p;
	char *buffer;
	int active;
} window_t;

/********************************************
 * Creates a window structure object        *
 *                                          *
 * *name: a string of 1 to 77 symbols long  *
 * startx: value in the range [0, 24]       *
 * endx: value in the range [0, 24]         *
 * starty: value in the range [0, 79]       *
 * endy: value in the range [0, 79]         *
 * attrib: a bit flag (color in CAPITAL)    *
 *                                          *
 * returns: created window object           *
 ********************************************/
window_t *window_create(char *name, int startx, int endx, int starty, int endy, char attrib);

/********************************************
 * Shows the contents of the window         *
 * 		If ACTIVE flag = 1                  *
 *                                          *
 * *w: previously created window object     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void window_open(window_t *w);

/********************************************
 * Close the window by opening the          *
 * initial state of the window              *
 * 		If ACTIVE flag = 1                  *
 *                                          *
 * *w: previously created window object     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void window_close(window_t *w);

/********************************************
 * Clears the memory of window object       *
 *                                          *
 * *w: previously created window object     *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void window_destroy(window_t *w);

/********************************************
 * If something went wrong creating a       *
 * window object, you would know it!        *
 *                                          *
 *                                          *
 *                                          *
 * returns: error code (if errors)          *
 ********************************************/
int get_error(void);

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
void move_string(char *string, window_t *w, char s_attrib);

/********************************************
 * Allows user to enter color and background*
 * color values of symbols. Checks the      *
 * entered value and handles errors         *
 *                                          *
 * *type: object type for the attribute     *
 *                                          *
 * returns: final attrib for symbols        *
 ********************************************/
char attrib_valid(char *type);

/********************************************
 * Prints the help messages for user        *
 *                                          *
 * number: utility variable for SWITCH      *
 *                                          *
 * returns: nothing                         *
 ********************************************/
void instructions(int number);
#endif