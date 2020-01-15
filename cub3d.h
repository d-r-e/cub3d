/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:45:46 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/15 12:19:55 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "get_next_line.h"

# define LEFT_CLICK 	1
# define RIGHT_CLICK 	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_I			34
# define KEY_O			31
# define KEY_P			35
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125
# define KEY_TAB	48
# define KEY_MAJ	257
# define KEY_ESC	53
# define KEY_TAB	48
# define RES_W	1920
# define RES_H	1080
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17
# define BLACK	0
# define WHITE	0x00FFFFFF

typedef struct	s_img
{
	int			x;
	int			y;
	int			h;
	int			w;
	void		*ptr;
	void		*mlx;
}				t_img;

typedef struct	s_line
{
	int x1;
	int y1;
	int x2;
	int y2;
}				t_line;

typedef struct	s_circ
{
	int			x;
	int			y;
	int			r;
}				t_circ;

typedef struct	s_map
{
	int			x;
	int			y;

	int			w;
	int			h;
}				t_map;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	int			posx;
	int			posy;
	int			keycode;
	int			wres;
	int			hres;
	int			ceilcolor;
	int			floorcolor;
	char		*nopth;
	char		*sopth;
	char		*wepth;
	char		*eapth;
	char		*sprpth;
	char		*mapstr;
	int			mapw;
	t_map		*map;
}				t_game;

int				rgb_int(int red, int green, int blue);
void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putnbr(int nb);
int				read_map(t_game *game, char *path);
int				ft_isnum(char c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
t_map			*create_map(t_game *game);
int				locate_start_point(t_game *game);
#endif
