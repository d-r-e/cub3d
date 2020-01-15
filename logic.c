/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:11:15 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/15 11:55:01 by darodrig         ###   ########.fr       */
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
			return (0);
		}
		i++;
	}
	return (-1);
}
