#ifndef INPUT_H
# define INPUT_H

# include "wolf3d.h"
# include <stdlib.h>

# define MAX_EVENTS 256
# define KEYBOARD_KEY_COUNT 128

# define ESC_KEY 0x35
# define LEFT_KEY 0x7B
# define RIGHT_KEY 0x7C
# define DOWN_KEY 0x7D
# define UP_KEY 0x7E
# define OPEN_KEY 0x21
# define CLOSE_KEY 0x1E
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4e
# define P_KEY 0x23
# define O_KEY 0x1f
# define D_KEY 0x2
# define M_KEY 0x2e
# define E_KEY 0xe
# define PAGEUP_KEY 0x74
# define PAGEDOWN_KEY 0x79
# define MOUSEWHEEL_UP 5
# define MOUSEWHEEL_DOWN 4
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK (1L<<6)
# define KEY_PRESS_EVENT 2
# define KEY_RELEASE_EVENT 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

typedef struct	s_input
{
	int			keys_pressed[KEYBOARD_KEY_COUNT];
}				t_input;

#endif