/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:11:15 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/17 09:58:42 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map
	*create_map(t_game *game)
{
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	map->w = game->mapw;
	map->h = ft_strlen(game->mapstr) / map->w;
	return (map);
}

int
	get_dir(t_map *map, char c)
{
	if (c == 'N' && (map->dir = -M_PI / 2))
	{
		map->planex = 0.5;
		map->planey = 0;
	}
	else if (c == 'S' && (map->dir = -3 * M_PI / 2))
	{
		map->planex = -0.5;
		map->planey = 0;
	}
	else if (c == 'E' && (map->dir = 2 * M_PI))
	{
		map->planex = 0;
		map->planey = 0.66;
	}
	else if (c == 'W' && (map->dir = M_PI))
	{
		map->planex = 0;
		map->planey = -0.66;
	}
	else
		return (-1);
	map->dirx = cos(map->dir);
	map->diry = sin(map->dir);
	return (0);
}

int
	locate_start_point(t_game *game)
{
	int		i;
	char	c;

	i = 0;
	while ((c = game->mapstr[i]) != '\0')
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			game->map->x = i % game->map->w + 0.5;
			game->map->y = i / game->map->w + 0.5;
			return (get_dir(game->map, c));
		}
		i++;
	}
	return (-1);
}

int
	validate_map(float **walls, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->h)
	{
		x = 0;
		while (x < game->map->w)
		{
			if (y == 0 && walls[y][x] != (float)1)
				return (-1);
			if (y == game->map->h - 1 && walls[y][x] != (float)1)
				return (-1);
			if (x == 0 && walls[y][x] != (float)1)
				return (-1);
			if (x == game->map->w - 1 && walls[y][x] != (float)1)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

void
	delete_objects(t_game *game)
{
	int i;
	int j;

	if (game->no && game->so && game->ea && game->sprite && game->we)
		return ;
	i = 0;
	while (i < game->map->h)
	{
		j = 0;
		while (j < game->map->w)
		{
			if (game->map->walls[i][j] == 2)
				game->map->walls[i][j] = 0;
			j++;
		}
		i++;
	}
}
