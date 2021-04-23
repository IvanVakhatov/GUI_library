#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

#define NUM_COLORS 256

#define SET_MODE 0x00
#define VIDEO_INT 0x10
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 320

#define PALETTE_INDEX 0x3C8
#define PALETTE_DATA 0x3C9
#define INPUT_STATUS 0x03DA
#define VRETRACE 0x08

typedef unsigned char byte;

typedef struct {
  byte color;
  int x, y;
  int width;
  int height;
  int score;
  byte *backup;
} player;

byte far *VGA=(byte far *)0xA0000000L;

#define SETPIX(x,y,c) *(VGA+(x)+(y)*SCREEN_WIDTH)=c
#define GETPIX(x,y) *(VGA+(x)+(y)*SCREEN_WIDTH)
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

void set_mode(byte mode)
{
  union REGS regs;
  regs.h.ah = SET_MODE;
  regs.h.al = mode;
  int86( VIDEO_INT, &regs, &regs );
}

void wait_for_retrace()
{
  while( inp( INPUT_STATUS ) & VRETRACE );
  while( ! (inp( INPUT_STATUS ) & VRETRACE) );
}

void draw_background()
{
  int x, y;

  for( y = 0; y < SCREEN_HEIGHT; ++y ) {
    for( x = 0; x < SCREEN_WIDTH; ++x ) {
      SETPIX( x, y, y );
    }
  }
}

byte *get_sky_palette()
{
  byte *pal;
  int i;
  pal = malloc( NUM_COLORS * 3 ); /* RGB */

  for( i = 0; i < 100; ++i ) {
    pal[ i*3 + 0 ] = MIN( 63, i ); /* RED */
    pal[ i*3 + 1 ] = MIN( 63, i ); /* GREEN */
    pal[ i*3 + 2 ] = 63; /* BLUE */
  }
  for( i = 100; i < 200; ++i ) {
    pal[ i*3 + 0 ] = 5; /* RED */
    pal[ i*3 + 1 ] = (i - 100) / 2; /* GREEN */
    pal[ i*3 + 2 ] = 5; /* BLUE */
  }

  i = 255;
  pal[ i*3 + 0 ] = 63; /* RED */
  pal[ i*3 + 1 ] = 20; /* GREEN */
  pal[ i*3 + 2 ] = 20; /* BLUE */

  return pal;
}

void set_palette(byte *palette)
{
  int i;

  outp( PALETTE_INDEX, 0 );
  for( i = 0; i < NUM_COLORS * 3; ++i ) {
    outp( PALETTE_DATA, palette[ i ] );
  }
}

void blit2mem( byte far *d, int x, int y, int w, int h )
{
  int i;
  byte far *src = VGA + x + y * SCREEN_WIDTH;
  byte far *dst = d;
  for( i = y; i < y + h; ++i ) {
    movedata( FP_SEG( src ), FP_OFF( src ),
	      FP_SEG( dst ), FP_OFF( dst ), w );
    src += SCREEN_WIDTH;
    dst += w;
  }
}

void blit2vga( byte far *s, int x, int y, int w, int h )
{
  int i;
  byte far *src = s;
  byte far *dst = VGA + x + y * SCREEN_WIDTH;
  for( i = y; i < y + h; ++i ) {
    movedata( FP_SEG( src ), FP_OFF( src ),
	      FP_SEG( dst ), FP_OFF( dst ), w );
    src += w;
    dst += SCREEN_WIDTH;
  }
}

/* Warning: no clipping! */
void draw_rectangle( int x, int y, int w, int h, byte c )
{
  int i, j;
  for( j = y; j < y + h; ++j ) {
    for( i = x; i < x + w; ++i ) {
      byte far *dst = VGA + i + j * SCREEN_WIDTH;
      *dst = c;
    }
  }
}

void restore_player( player *p )
{
  blit2vga( p->backup, p->x, p->y, p->width, p->height );
}

void store_player( player *p )
{
  blit2mem( p->backup, p->x, p->y, p->width, p->height );
}

void draw_player( player *p )
{
  draw_rectangle( p->x, p->y, p->width, p->height, p->color );
}

int main()
{
  char kc = 0;
  char s[255];
  byte *pal;
  player p1, p2;

  p1.color = 255;
  p1.height = 30;
  p1.width = 5;
  p1.x = 5;
  p1.y = SCREEN_HEIGHT / 2 - p1.height / 2;
  p1.score = 0;
  p1.backup = malloc( p1.height * p1.width );
  memset( p1.backup, 0, p1.height * p1.width );

  p2.color = 255;
  p2.height = 30;
  p2.width = 5;
  p2.x = SCREEN_WIDTH - p2.width - 5;
  p2.y = SCREEN_HEIGHT / 2 - p2.height / 2;
  p2.score = 0;
  p2.backup = malloc( p2.height * p2.width );
  memset( p1.backup, 0, p2.height * p2.width );

  set_mode( VGA_256_COLOR_MODE );

  pal = get_sky_palette();
  set_palette( pal );

  clrscr();
  draw_background();

  store_player( &p1 );
  store_player( &p2 );

  /* loop until ESC pressed */
  while( kc != 0x1b )
  {
    restore_player( &p1 );
    restore_player( &p2 );

    if(kbhit()) {
      kc = getch();
      if( kc == (char)0 ) {
	kc = getch();
	/* special key handling */
	switch( kc )
	{
	case 0x48: /* up arrow */
	  p1.y -= 4;
	  if( p1.y < 0 ) {
	    p1.y = 0;
	  }
	  break;
	case 0x50: /* down arrow */
	  p1.y += 4;
	  if( p1.y + p1.height > SCREEN_HEIGHT ) {
	    p1.y = SCREEN_HEIGHT - p1.height;
	  }
	  break;
	default: /* other special keys */
	  break;
	}
      }
    }

    store_player( &p1 );
    store_player( &p2 );
    draw_player( &p1 );
    draw_player( &p2 );
    wait_for_retrace();
  }

  set_mode( TEXT_MODE );

  return 0;
}