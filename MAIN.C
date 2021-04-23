#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <base.h>
#include <window.h>

int main(void)
{
	window_t *w1, *w2;
	char W1_ATTRIB, W2_ATTRIB, STR1_ATTRIB, STR2_ATTRIB;
	
	W1_ATTRIB = attrib_valid("W1");
	W2_ATTRIB = attrib_valid("W2");
	STR1_ATTRIB = attrib_valid("STR1");
	STR2_ATTRIB = attrib_valid("STR2");
	
	clrscr();
	w1 = window_create("WINDOW1", 10, 24, 0, 79, W1_ATTRIB);
	w2 = window_create("WINDOW2", 3, 9, 45, 79, W2_ATTRIB);
	
	window_open(w1);
	instructions(7);
	move_string("IVAN", w1, STR1_ATTRIB);
	window_open(w2);
	move_string("TEST_STRING", w2, STR2_ATTRIB);
	window_close(w2);
	window_close(w1);
	window_destroy(w2);
	window_destroy(w1);
	return 0;
}