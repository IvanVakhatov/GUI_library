#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <base.h>
#include <window.h>

int main(void)
{
	window_t *w1, *w2;
	int ERROR1, ERROR2;
	char W1_ATTRIB, W2_ATTRIB, STR1_ATTRIB, STR2_ATTRIB;
	
	clrscr();
	instructions(3);
	W1_ATTRIB = attrib_valid();
	
	clrscr();
	instructions(4);
	W2_ATTRIB = attrib_valid();
	
	clrscr();
	instructions(5);
	STR1_ATTRIB = attrib_valid();
	
	clrscr();
	instructions(6);
	STR2_ATTRIB = attrib_valid();
	
	clrscr();
	w1 = window_create("WINDOW1", 10, 24, 0, 79, W1_ATTRIB);
	ERROR1 = get_error();
	w2 = window_create("WINDOW2", 3, 9, 45, 79, W2_ATTRIB);
	ERROR2 = get_error();
	getch();
	
	if (ERROR1 == 0 && ERROR2 == 0)
	{
		window_open(w1);
		getch();
		instructions(7);
		move_string(w1, STR1_ATTRIB);
		getch();
		window_open(w2);
		getch();
		move_string(w2, STR2_ATTRIB);
		getch();
		window_close(w2);
		getch();
		window_close(w1);
		getch();
		window_destroy(w2);
		window_destroy(w1);
	}
	
	else if (ERROR1 == 0)
	{
		window_open(w1);
		getch();
		instructions(7);
		move_string(w1, STR1_ATTRIB);
		getch();
		window_close(w1);
		getch();
		window_destroy(w1);
	}
	
	else if (ERROR2 == 0)
	{
		window_open(w2);
		getch();
		instructions(7);
		move_string(w2, STR2_ATTRIB);
		getch();
		window_close(w2);
		getch();
		window_destroy(w2);
	}
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