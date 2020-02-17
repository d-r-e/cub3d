/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:49:37 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 13:58:32 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game, "");
	if (keycode == KEY_W)
		game->up = 1;
	if (keycode == KEY_S)
		game->down = 1;
	if (keycode == KEY_A)
		game->left = 1;
	if (keycode == KEY_D)
		game->right = 1;
	if (keycode == KEY_LEFT)
		game->turnleft = 1;
	if (keycode == KEY_RIGHT)
		game->turnright = 1;
	if (keycode == KEY_Q && game->textures == 1)
		game->minimap = !game->minimap;
	if (keycode == KEY_I)
		game->scale--;
	if (keycode == KEY_J)
		game->scale++;
	if (keycode == KEY_M)
		game->mira = !game->mira;
	return (0);
}

int		key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->up = 0;
	if (keycode == KEY_S)
		game->down = 0;
	if (keycode == KEY_A)
		game->left = 0;
	if (keycode == KEY_D)
		game->right = 0;
	if (keycode == KEY_LEFT)
		game->turnleft = 0;
	if (keycode == KEY_RIGHT)
		game->turnright = 0;
	if (keycode == KEY_Y)
	{
		game->sprites = 0;
		game->textures = 0;
	}
	return (0);
}

int		ft_mouse(int x, int y, t_game *game)
{
	(void)y;
	if (x - game->mousex > 1)
		game->turnright = 1;
	else
		game->turnright = 0;
	if (x - game->mousex < -1)
		game->turnleft = 1;
	else
		game->turnleft = 0;
	game->mousex = x;
	return (0);
}
