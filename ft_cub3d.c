/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:58:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/15 12:20:08 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			put_circle(t_game *game, t_circ c, int color)
{
	float	x;
	float	y;
	int		xmax;
	int		ymax;

	x = c.x - (sqrt(2) * c.r);
	xmax = x + (2 * c.r) > RES_W ? RES_W : x + (2 * c.r);
	x = x < 0 ? 0 : x;
	while (x < RES_W)
	{
		y = c.y - (sqrt(2) * c.y);
		ymax = y + (2 * c.r) > RES_H ? RES_H : y + (2 * c.r);
		y = y < 0 ? 0 : y;
		while (y < RES_H)
		{
			if ((pow(c.x - x, 2) + pow(c.y - y, 2) - pow(c.r, 2)) < 10)
				mlx_pixel_put(game->mlx, game->win, x, y, color);
			y++;
		}
		x++;
	}
}

int				rgb_int(int red, int green, int blue)
{
	int rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

t_circ			rand_circle(void)
{
	t_circ c;

	c.x = rand() % RES_W;
	c.y = rand() % RES_H;
	c.r = rand() % 100;
	return (c);
}

void			put_line(t_line line, t_game *game)
{
	int	m;
	int	n;

	m = (line->y2 - line->y1) / (line->x2 - line->x1);

}

int				key_press(int keycode, t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	ft_putstr("KEYCODE: ");
	ft_putnbr(game->keycode);
	ft_putchar('\n');
	if (keycode == KEY_E)
		put_circle(game, rand_circle(), rand() % 0x00FFFFFF);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game);
		exit(0);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_game	*game;
	int		err;

	err = 0;
	game = malloc(sizeof(t_game));
	if (argc == 2)
	{
		err = read_map(game, argv[1]);
		if (err < 0 || !game->mapstr)
		{
			ft_putstr("Error\nWrong map file\n");
			free(game);
			exit(0);
		}
	}
	game->mlx = mlx_init();
	if (!game->wres)
		game->wres = RES_W;
	if (!game->hres)
		game->hres = RES_H;
	create_map(game);
	locate_start_point(game);
	game->win = mlx_new_window(game->mlx, game->wres, game->hres, "CUB3D");
	game->keycode = mlx_hook(game->win, 2, 0, &key_press, (void*)game);
	mlx_loop(game->mlx);
	free(game);
	return (EXIT_SUCCESS);
}
