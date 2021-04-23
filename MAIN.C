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
	w2 = window_create("WINDOW2", 3, 9, -45, 79, W2_ATTRIB);
	
	window_open(w1);
	instructions(7);
	move_string(w1, STR1_ATTRIB);
	getch();
	window_open(w2);
	move_string(w2, STR2_ATTRIB);
	getch();
	window_close(w2);
	window_close(w1);
	window_destroy(w2);
	window_destroy(w1);
	return 0;
}

/*int main(void)
{
	int startx = 10, starty = 10, endx = 20, endy = 50;
	char *buffer = create_buffer(startx, starty, endx, endy);
	get_vmem(startx, starty, endx, endy, buffer);
	getch();
	clear(startx, starty, endx, endy, 0xB0, BGBLUE);
	clrscr();
	write_string(10, 10, " ", LIGHTBLUE | BGLIGHTGRAY);
	write_char(15, 15, 'C', GREEN);
	getch();
	clrscr();
	desktop();
	getch();
	borders();
	getch();
	name(0, 0, 79, "WINDOW", RED);
	getch();
	put_vmem(startx, starty, endx, endy, buffer);
	getch();
	free(buffer);
}*/