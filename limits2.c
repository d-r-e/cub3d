/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:58:39 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 15:32:37 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	move(t_game *game)
{
	if (game->up == 1)
	{
		game->map->x += game->map->dirx * SPEED;
		game->map->y += game->map->diry * SPEED;
	}
	if (game->down == 1)
	{
		game->map->x -= game->map->dirx * SPEED;
		game->map->y -= game->map->diry * SPEED;
	}
	if (game->left == 1)
	{
		game->map->y -= game->map->dirx * SPEED;
		game->map->x += game->map->diry * SPEED;
	}
	if (game->right == 1)
	{
		game->map->y += game->map->dirx * SPEED;
		game->map->x -= game->map->diry * SPEED;
	}
}

void
	prvv(t_game *game, double *prev)
{
	prev[0] = game->map->x;
	prev[1] = game->map->y;
	prev[2] = game->map->dirx;
	prev[3] = game->map->diry;
	prev[4] = game->map->planex;
	prev[5] = game->map->planey;
}

void
	turn_right(t_game *game)
{
	game->offset++;
	game->oldx = game->map->dirx;
	game->map->dirx = game->map->dirx * cos(-ROT) - game->map->diry * sin(-ROT);
	game->map->diry = game->oldx * sin(-ROT) + game->map->diry * cos(-ROT);
	game->oldplanex = game->map->planex;
	game->map->planex = game->map->planex * cos(-ROT) - game->map->planey *
			sin(-ROT);
	game->map->planey = game->oldplanex * sin(-ROT) + game->map->planey *
			cos(-ROT);
}

void
	restore_pos(t_game *game, double prev[6])
{
	game->map->x = prev[0];
	game->map->y = prev[1];
	game->map->dirx = prev[2];
	game->map->diry = prev[3];
	game->map->planex = prev[4];
	game->map->planey = prev[5];
}
