/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:11:15 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/20 15:54:47 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*create_map(t_game *game)
{
	t_map *map;

	map = malloc(sizeof(t_map*));
	map->w = game->mapw;
	map->h = ft_strlen(game->mapstr) / map->w;
	game->map = map;
	return (map);
}

int		get_dir(t_map *map, char c)
{
	if (c == 'N')
		map->dir = M_PI / 2;
	else if (c == 'S')
		map->dir = (3 / 2) * M_PI;
	else if (c == 'E')
		map->dir = 0;
	else if (c == 'W')
		map->dir = M_PI;
	else
		return (-1);
	return (0);
}

int		locate_start_point(t_game *game)
{
	int		i;
	char	c;

	i = 0;
	while ((c = game->mapstr[i]) != '\0')
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			game->map->x = i % game->map->w + 1;
			game->map->y = i / game->map->w;
			return (get_dir(game->map, c));
		}
		i++;
	}
	return (-1);
}
