#ifndef WINDOW_H_
#define WINDOW_H_

typedef struct window {
	int startx, starty, endx, endy;
	char attrib;
	char name[80];
	char *p;
	char *buffer;
} window_t;

window_t *window_create(char *name, int startx, int endx, int starty, int endy, char attrib);
void window_open(window_t *w);
void move_string(window_t *w, char s_attrib);
void window_close(window_t *w);
void window_destroy(window_t *w);
int get_error(void);
char attrib_valid(void);
void instructions(int number);
#endif