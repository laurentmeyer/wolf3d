/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:44:54 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:44:56 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdlib.h>

# define MAX_EVENTS 256
# define KEYBOARD_KEY_COUNT 128

# define ESC_KEY 0x35
# define LEFT_KEY 0x7B
# define RIGHT_KEY 0x7C
# define DOWN_KEY 0x7D
# define UP_KEY 0x7E

# define KEY_PRESS_EVENT 2
# define KEY_RELEASE_EVENT 3

# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

typedef struct	s_input
{
	int			*keys_pressed;
}				t_input;

#endif
