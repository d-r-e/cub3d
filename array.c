/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:13:45 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/13 15:52:54 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		toarray(t_game *game)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = game->mapstr;
	game->map->walls = malloc(sizeof(int*) * game->map->h);
	i = -1;
	while (++i < game->map->h)
	{
		game->map->walls[i] = malloc(sizeof(int) * game->map->w);
		j = -1;
		while (++j != game->map->w)
		{
			if (*ptr == '0' || ft_isalpha(*ptr))
				game->map->walls[i][j] = 0;
			else if (*ptr == '1')
				game->map->walls[i][j] = 1;
			else if (*ptr == '2')
				game->map->walls[i][j] = 2;
			else
				return (-1);
			ptr++;
		}
	}
	return (0);
}
