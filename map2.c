/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:27:15 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/13 15:31:03 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	check_r(char *line, t_game *game)
{
	game->wres = 0;
	game->hres = 0;
	if (ft_strlen(line) < 4)
		return (-1);
	while (*line == ' ')
		line++;
	while (*line >= '0' && *line <= '9')
	{
		game->wres = game->wres * 10 + (*line - '0');
		line++;
	}
	while (*line == ' ')
		line++;
	while (*line >= '0' && *line <= '9')
	{
		game->hres = game->hres * 10 + (*line - '0');
		line++;
	}
	if (game->wres == 0 || game->hres == 0)
		return (-1);
	return (0);
}

int
	check_f(char *line, t_game *game)
{
	int		rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (ft_strlen(line) < 7 || *(line++ + 1) != ' ')
		return (-1);
	while (*line == ' ')
		line++;
	while (*line >= '0' && *line <= '9')
		rgb[0] = rgb[0] * 10 + (*line++ - '0');
	if (*line++ != ',' || !ft_isnum(*line))
		return (-1);
	while (*line >= '0' && *line <= '9')
		rgb[1] = rgb[1] * 10 + (*line++ - '0');
	if (*line++ != ',' || !ft_isnum(*line))
		return (-1);
	while (*line >= '0' && *line <= '9')
		rgb[2] = rgb[2] * 10 + (*line++ - '0');
	game->floor = rgb_int(rgb[0], rgb[1], rgb[2]);
	return (0);
}
