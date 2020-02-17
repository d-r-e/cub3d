/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:12:53 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/07 08:48:57 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_game *game)
{
	if (game->no != NULL)
		free(game->no);
	if (game->so != NULL)
		free(game->so);
	if (game->ea != NULL)
		free(game->ea);
	if (game->we != NULL)
		free(game->we);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->h)
	{
		free(game->map->walls[i]);
		i++;
	}
	free(game->map->walls);
}
