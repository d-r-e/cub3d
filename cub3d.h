/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:45:46 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/17 09:58:45 by darodrig         ###   ########.fr       */
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
# define KEY_Y			16
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_I			34
# define KEY_O			31
# define KEY_P			35
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_M			46
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125
# define KEY_TAB	48
# define KEY_MAJ	257
# define KEY_ESC	53
# define KEY_TAB	48
# define RES_H	900
# define RES_W	1600
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17
# define BLACK	0
# define WHITE	0x00FFFFFF
# define PINK	0x00ffaacc
# define LIME	0x00d5ff61
# define RED	0x00e33642
# define SPEED	0.04
# define ROT	-0.03
# define SCALE	9
# define TEXW	64

typedef	struct	s_sprite
{
	double	x;
	double	y;
	double	dist;
}				t_sprite;

typedef struct	s_tex
{
	void	*ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	char	*cdata;
	int		w;
	int		h;
}				t_tex;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	char		*cdata;
	int			size_l;
	int			bpp;
	int			endian;
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
	double		x;
	double		y;
	double		dir;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	float		**walls;
	int			w;
	int			h;
}				t_map;

typedef struct	s_ray
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	*zbuffer;
	int		x;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		color;
	t_tex	*tx;
	double	wallx;
	double	step;
	int		drawstart;
	int		drawend;
	double	texpos;
	int		y;
	int		texx;
	int		texy;
	int		counter;
	double	spritex;
	double	spritey;
	double	inv;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spriteheight;
	int		spritewidth;
	int		drawstarty;
	int		drawstartx;
	int		drawendy;
	int		drawendx;
	int		stripe;
	int		d;
}				t_ray;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	int			wres;
	int			hres;
	int			ceil;
	int			floor;
	char		*nopth;
	char		*sopth;
	char		*wepth;
	char		*eapth;
	char		*sprpth;
	char		*mapstr;
	int			mapw;
	t_map		*map;
	int			up;
	int			down;
	int			left;
	int			right;
	int			turnleft;
	int			turnright;
	t_img		*img;
	t_tex		*hud;
	t_tex		*sky;
	int			textures;
	int			sprites;
	int			minimap;
	int			mira;
	int			scale;
	t_tex		*no;
	t_tex		*so;
	t_tex		*ea;
	t_tex		*we;
	t_tex		*sprite;
	int			numsprites;
	double		spr_x;
	double		spr_y;
	int			err;
	t_sprite	*locations;
	int			screenshot;
	double		oldx;
	double		oldy;
	double		prev[6];
	double		oldplanex;
	int			mousex;
	int			offset;
}				t_game;

int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				rgb_int(int red, int green, int blue);
void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putnbr(int nb);
int				ft_strcmp(const char *s1, const char *s2);
int				read_map(t_game *game, char *path);
int				print_minimap(t_game *game);
int				ft_isnum(char c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
t_map			*create_map(t_game *game);
int				locate_start_point(t_game *game);
int				toarray(t_game *game);
void			testpr(t_game *game);
int				ft_isalpha(char c);
char			*ft_cutspaces(char *str);
void			putsq(t_game *game, int x, int y, int color);
void			put_circle(t_game *game, t_circ c, int color);
int				exit_game(t_game *game, const char *str);
int				ft_caster(t_game *game);
void			ver_line(t_game *game, int x, int h, int color);
void			free_map(t_game *game);
void			free_textures(t_game *game);
void			move_pos(t_game *game);
int				print_minimap(t_game *game);
int				pix_pos(int x, int y, t_game *game);
void			new_frame(t_game *game);
void			pixelput(t_game *game, int x, int y, int color);
int				load_textures(t_game *game);
void			put_mira(t_game *game);
int				check_f(char *line, t_game *game);
int				check_r(char *line, t_game *game);
void			count_sprites(t_game *game);
int				faded_color(int color, int dist);
void			bubble_texture(t_game *game);
void			render_dist(t_game *game);
int				screenshot(t_game *game);
void			ft_caster_init(t_game *game, t_ray *r);
void			ft_caster7(t_game *game, t_ray *r);
void			ft_caster6(t_game *game, t_ray *r);
void			ft_caster5(t_game *game, t_ray *r);
void			ft_caster4(t_game *game, t_ray *r);
void			initial_values(t_game *game);
void			turn_right(t_game *game);
void			move(t_game *game);
void			prvv(t_game *game, double prev[6]);
int				validate_map(float **walls, t_game *game);
int				ft_mouse(int x, int y, t_game *game);
void			restore_pos(t_game *game, double prev[6]);
int				gradient(int color, int i, t_game *game);
void			delete_objects(t_game *game);
#endif
