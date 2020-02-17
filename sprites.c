/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:42:07 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/17 09:56:27 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	render_dist(t_game *game)
{
	int i;

	i = 0;
	while (i < game->numsprites)
	{
		game->locations[i].dist = sqrt(pow(game->locations[i].x -
			game->map->x, 2) + pow(game->locations[i].y - game->map->y, 2));
		i++;
	}
}

void
	bubble_texture(t_game *game)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < game->numsprites)
	{
		j = i;
		while (j < game->numsprites - 1)
		{
			if (game->locations[j].dist < game->locations[j + 1].dist)
			{
				tmp = game->locations[j];
				game->locations[j] = game->locations[j + 1];
				game->locations[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void
	get_sprite_pos(t_game *game)
{
	int			i;
	int			count;
	char		c;
	t_sprite	s;

	i = 0;
	count = 0;
	while ((c = game->mapstr[i]) != '\0')
	{
		if (c == '2')
		{
			s.x = i % game->map->w - 0.5;
			s.y = i / game->map->w - 0.5;
			game->locations[count] = s;
			count++;
		}
		i++;
	}
}

void
	count_sprites(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	game->numsprites = 0;
	i = 0;
	while (i < game->map->h)
	{
		j = 0;
		while (j < game->map->w)
		{
			if (game->map->walls[i][j] == 2)
				game->numsprites++;
			j++;
		}
		i++;
	}
	game->locations = (t_sprite*)malloc(sizeof(t_sprite) * game->numsprites);
	get_sprite_pos(game);
}
