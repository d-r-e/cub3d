/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:13:45 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/20 15:02:17 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		toarray(t_game *game)
{
	int		i;
	int		j;

	game->map->walls = malloc(sizeof(int*) * game->map->h);
	i = 0;
	while (i < game->map->h)
	{
		game->map->walls[i] = malloc(sizeof(int) * game->map->w);
		j = 0;
		while (j != game->map->w)
		{
			if (*game->mapstr == '0' || ft_isalpha(*game->mapstr))
				game->map->walls[i][j] = 0;
			else if (*game->mapstr == '1')
				game->map->walls[i][j] = 1;
			else
				return (-1);
			game->mapstr++;
			j++;
		}
		i++;
	}
	return (0);
}

void	testpr(t_game *game)
{
	int	i;
	int	j;

	ft_putchar('\n');
	if (!game->map->walls)
	{
		ft_putstr("NO HAY MAPA\n");
		return ;
	}
	i = 0;
	while (i < game->map->h)
	{
		j = 0;
		while (j < game->map->w)
		{
			ft_putchar(game->map->walls[i][j] + '.');
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
