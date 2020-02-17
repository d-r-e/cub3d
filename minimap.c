/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:54:22 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/14 12:25:53 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	put_map(t_game *game)
{
	float	x;
	float	y;
	int		i;
	int		j;

	y = game->hres - (game->map->h * game->scale);
	i = 0;
	while (i < game->map->h)
	{
		j = 0;
		x = 0;
		while (j < game->map->w)
		{
			if (game->map->walls[i][j] == 1)
				putsq(game, x, y, 0x00EEEEEE);
			else if (game->map->walls[i][j] == 2)
				putsq(game, x, y, PINK);
			x += game->scale;
			j++;
		}
		i++;
		y += game->scale;
	}
}

void
	put_hud(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < 50)
	{
		x = game->wres - 97;
		while (x < game->wres)
		{
			if (game->hud->data[y * 97 + x - 40] != 0)
				pixelput(game, x, y, game->hud->data[y * 97 + x - 40]);
			x++;
		}
		y++;
	}
}

int
	print_minimap(t_game *game)
{
	t_circ	circ;

	circ.x = game->scale * game->map->x;
	circ.y = (game->scale * game->map->y) + game->hres - (game->map->h *
			game->scale);
	circ.r = game->scale / 3;
	put_map(game);
	put_circle(game, circ, 0x00EE0000);
	pixelput(game, game->map->x * game->scale + game->scale * game->map->dirx
			* 0.7, game->scale * (game->map->y + game->map->diry * 0.7) +
			game->hres - game->map->h * game->scale, RED);
	pixelput(game, game->scale * (game->map->x + game->map->dirx * 0.4 +
			game->map->planex / 4), game->scale * (game->map->y +
			game->map->diry * 0.5 + game->map->planey / 2) +
			game->hres - game->map->h * game->scale, RED);
	pixelput(game, game->scale * (game->map->x + game->map->dirx * 0.4 -
			game->map->planex / 4), game->scale * (game->map->y +
			game->map->diry * 0.5 - game->map->planey / 2) +
			game->hres - game->map->h * game->scale, RED);
	put_hud(game);
	return (0);
}
