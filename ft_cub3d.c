/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:58:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/21 15:48:21 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				rgb_int(int red, int green, int blue)
{
	int rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

void			put_map(t_game *game)
{
	float	x;
	float	y;
	int		i;
	int		j;

	y = game->hres - (game->map->h * 10);
	i = 0;
	while (i < game->map->h)
	{
		j = 0;
		x = 0;
		while (j < game->map->w)
		{
			if (game->map->walls[i][j] == 1)
				putsq(game, x, y);
			x += 10;
			j++;
		}
		i++;
		y += 10;
	}
}

int				print_minimap(t_game *game)
{
	t_circ	circ;

	circ.x = 10 * game->map->x;
	circ.y = (10 * game->map->y) + game->hres - (game->map->h * 10); 
	circ.r = game->wres / 800;

	put_map(game);
	put_circle(game, circ, rgb_int(255, 54, 94));
	return (0);
}

int				key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit_game(game);
	}
	if (keycode == KEY_W)
		game->up = 1;
	if (keycode == KEY_S)
		game->down = 1;
	if (keycode == KEY_A)
		game->left = 1;
	if (keycode == KEY_D)
		game->right = 1;
	return (0);
}

void		limits(t_game *game, float prev[2])
{
	if (game->map->walls[(int)(game->map->y)][(int)(game->map->x)] == 1)
	{
		game->map->y = prev[0];
		game->map->x = prev[1];
	}
	if (game->map->x < 0)
		game->map->x = 0;
	if (game->map->x > game->map->w)
		game->map->x = game->map->w;
	if (game->map->y > game->map->h)
		game->map->y = game->map->h;
	if (game->map->y < 0)
		game->map->y = 0;	
}

int			move_pos(t_game *game)
{
	float	speed;
	float	prev[2];

	prev[0] = game->map->y;
	prev[1] = game->map->x;
	speed = 0.1;
	if (game->up == 1)
	{
		game->map->y -= speed * sin(game->map->dir);
		game->map->x += speed * cos(game->map->dir);
	}
	if (game->down == 1)
	{
		game->map->y += speed * sin(game->map->dir);
		game->map->x -= speed * cos(game->map->dir);
	}
	if (game->left == 1)
		game->map->dir += speed * 0.5;
	if (game->right == 1)
		game->map->dir -= speed * 0.5;
	limits(game, prev);
	mlx_clear_window(game->mlx, game->win);
	print_minimap(game);
	return (0);
}

int				key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->up = 0;
	if (keycode == KEY_S)
		game->down = 0;
	if (keycode == KEY_A)
		game->left = 0;
	if (keycode == KEY_D)
		game->right = 0;
	return (0);
}

int				init_map(t_game *game)
{
	int err;

	err = 0;
	create_map(game);
	err += locate_start_point(game);
	err += toarray(game);
	if (err < 0)
	{
		ft_putstr("Error\nWrong map format\n");
		exit_game(game);
	}
	return (0);
}

int				exit_game(t_game *game)
{
	if (game)
		free(game);
	exit(0);
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
	else
		exit(0);
	if (!game->wres)
		game->wres = RES_W;
	if (!game->hres)
		game->hres = RES_H;
	game->mlx = mlx_init();
	init_map(game);
	game->win = mlx_new_window(game->mlx, game->wres, game->hres, "CUB3D");
	mlx_hook(game->win, 2, 1L << 0, &key_press, (void*)game);
	mlx_hook(game->win, 3, 1L << 1, &key_release, (void*)game);
	mlx_hook(game->win, 17, 1L << 2, &exit_game, (void*)game);
	mlx_loop_hook(game->mlx, &move_pos, (void*)game);
	mlx_loop(game->mlx);
	exit_game(game);
}
