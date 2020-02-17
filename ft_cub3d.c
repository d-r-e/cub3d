/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:58:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/17 11:15:39 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_render(t_game *game)
{
	move_pos(game);
	free(game->img);
	new_frame(game);
	ft_caster(game);
	if (game->minimap == 1)
		print_minimap(game);
	if (game->mira == 1)
		put_mira(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->ptr, 0, 0);
	mlx_destroy_image(game->mlx, game->img->ptr);
	return (0);
}

int
	init_map(t_game *game)
{
	int err;

	err = 0;
	game->map = create_map(game);
	err += locate_start_point(game);
	err += toarray(game);
	if (game->nopth != NULL)
		err += load_textures(game);
	if (err < 0)
		exit_game(game, "Error\nMap misconfiguration.\n");
	return (0);
}

void
	init_game(t_game *game, int arc, char **argv)
{
	int		err;

	initial_values(game);
	err = 0;
	if (arc == 3 && ft_strcmp(argv[2], "--save") == 0 && (game->screenshot = 1))
		arc--;
	if (arc == 2 && (err = read_map(game, argv[1])))
	{
		if (err < 0 || !game->mapstr)
		{
			ft_putstr("Error\nWrong map file\n");
			exit(0);
		}
	}
	else
	{
		ft_putstr("Error\nNo map specified.\n");
		exit(0);
	}
	if (game->wres < 200 || game->wres > RES_W)
		game->wres = RES_W;
	if (game->hres < 200 || game->hres > RES_H)
		game->hres = RES_H;
}

int
	exit_game(t_game *game, const char *str)
{
	mlx_destroy_window(game->mlx, game->win);
	if (str)
		ft_putstr(str);
	free_map(game);
	free_textures(game);
	system("leaks cub3D");
	exit(0);
}

int
	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game*)malloc(sizeof(t_game));
	init_game(game, argc, argv);
	game->mlx = mlx_init();
	init_map(game);
	if (validate_map(game->map->walls, game) != 0)
	{
		ft_putstr("Error\nMap is not closed.");
		exit(0);
	}
	count_sprites(game);
	game->win = mlx_new_window(game->mlx, game->wres, game->hres, "CUB3D");
	mlx_hook(game->win, 2, 1L << 0, &key_press, (void*)game);
	mlx_hook(game->win, 3, 1L << 1, &key_release, (void*)game);
	mlx_hook(game->win, 17, 1L << 2, &exit_game, (void*)game);
	mlx_hook(game->win, 6, 0, &ft_mouse, (void*)game);
	mlx_loop_hook(game->mlx, &ft_render, (void*)game);
	mlx_loop(game->mlx);
	exit_game(0, NULL);
}
