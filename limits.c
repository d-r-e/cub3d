/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:44:59 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 18:38:17 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	limitsr(t_game *game, double prev[6])
{
	int newx;
	int	newy;

	newx = game->map->x + game->map->dirx * 0.5 - (game->map->planex / 4);
	newy = game->map->y + game->map->diry * 0.5 - game->map->planey / 2;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
	newx = game->map->x + game->map->dirx * 0.5 + (game->map->planex / 4);
	newy = game->map->y + game->map->diry * 0.5 + game->map->planey / 2;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
}

void
	limitst(t_game *game, double prev[6])
{
	int newx;
	int	newy;

	newx = game->map->x + game->map->dirx * 0.5 - (game->map->planex / 2);
	newy = game->map->y + game->map->diry * 0.5 - game->map->planey / 2;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
	newx = game->map->x + game->map->dirx * 0.5 + (game->map->planex / 2);
	newy = game->map->y + game->map->diry * 0.5 + game->map->planey / 2;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
	newx = game->map->x + game->map->dirx * 0.6 - (game->map->planex / 2);
	newy = game->map->y + game->map->diry * 0.6 - game->map->planey / 2;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
	newx = game->map->x + game->map->dirx * 0.6 + (game->map->planex / 2);
	newy = game->map->y + game->map->diry * 0.6 + game->map->planey / 2;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
}

void
	limitspos(t_game *game, double prev[6])
{
	double	newx;
	double	newy;

	newx = game->map->x - 0.2 * game->map->dirx;
	newy = game->map->y - 0.2 * game->map->diry;
	if (game->map->walls[(int)(trunc(newy))][(int)(trunc(newx))] != 0)
		restore_pos(game, prev);
	newx = game->map->x + 0.2 * game->map->diry;
	newy = game->map->y + 0.2 * game->map->dirx;
	if (game->map->walls[(int)(trunc(newy))][(int)(trunc(newx))] != 0)
		restore_pos(game, prev);
	newx = game->map->x - 0.2 * game->map->diry;
	newy = game->map->y - 0.2 * game->map->dirx;
	if (game->map->walls[(int)(trunc(newy))][(int)(trunc(newx))] != 0)
		restore_pos(game, prev);
	newx = game->map->x + game->map->dirx * 0.2 + (game->map->planex / 4);
	newy = game->map->y + game->map->diry * 0.2 + (game->map->planey / 4);
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
	newx = game->map->x + game->map->dirx * 0.7;
	newy = game->map->y + game->map->diry * 0.7;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
		restore_pos(game, prev);
}

void
	limits(t_game *game, double prev[6])
{
	int newx;
	int	newy;

	newx = game->map->x + game->map->dirx;
	newy = game->map->y + game->map->diry;
	if (game->map->walls[(int)(newy)][(int)(newx)] != 0)
	{
		restore_pos(game, prev);
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

void
	move_pos(t_game *game)
{
	game->oldx = game->map->dirx;
	prvv(game, game->prev);
	move(game);
	if (game->turnright == 1)
		turn_right(game);
	if (game->turnleft == 1)
	{
		game->offset--;
		game->oldx = game->map->dirx;
		game->map->dirx = game->map->dirx * cos(ROT) - game->map->diry *
				sin(ROT);
		game->map->diry = game->oldx * sin(ROT) + game->map->diry * cos(ROT);
		game->oldplanex = game->map->planex;
		game->map->planex = game->map->planex * cos(ROT) - game->map->planey *
				sin(ROT);
		game->map->planey = game->oldplanex * sin(ROT) + game->map->planey *
				cos(ROT);
	}
	limits(game, game->prev);
	limitspos(game, game->prev);
	limitsr(game, game->prev);
	limitst(game, game->prev);
}
