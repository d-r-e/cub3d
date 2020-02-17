/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:04:16 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/13 16:15:25 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_c(char *line, t_game *game)
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
	game->ceil = rgb_int(rgb[0], rgb[1], rgb[2]);
	return (0);
}

int		count_ones(char *s)
{
	int ones;

	ones = 0;
	while (*s)
	{
		if (*s == '1')
			ones++;
		s++;
	}
	return (ones);
}

int		get_map(char *line, t_game *game, int fd)
{
	int		maplen;
	char	*tmp;
	char	*ln;

	game->mapstr = ft_strdup(line);
	if ((maplen = count_ones(line)) < 3)
		return (-1);
	while ((get_next_line(fd, &ln)) > 0)
	{
		if (*ln == 0)
			break ;
		tmp = ft_strjoin(game->mapstr, ln);
		free(game->mapstr);
		free(ln);
		game->mapstr = tmp;
	}
	free(ln);
	tmp = ft_cutspaces(game->mapstr);
	free(game->mapstr);
	game->mapstr = tmp;
	game->mapw = maplen;
	return (0);
}

int		check_line(char *l, t_game *game, int fd)
{
	game->err = 0;
	if (*l == '\0' || *l == '\n' || !l)
		game->err = 0;
	else if (*l == 'R' && *(l + 1))
		game->err = check_r(l + 1, game);
	else if (*l == 'F')
		game->err = check_f(l, game);
	else if (*l == 'C')
		game->err = check_c(l, game);
	else if (*l == 'S' && *(l + 1) == 'O' && *(l + 2) == ' ' && *(l + 3))
		game->sopth = ft_strdup(ft_strchr(l, '.'));
	else if (*l == 'N' && *(l + 1) == 'O' && *(l + 2) == ' ' && *(l + 3))
		game->nopth = ft_strdup(ft_strchr(l, '.'));
	else if (*l == 'E' && *(l + 1) == 'A' && *(l + 2) == ' ' && *(l + 3))
		game->eapth = ft_strdup(ft_strchr(l, '.'));
	else if (*l == 'W' && *(l + 1) == 'E' && *(l + 2) == ' ' && *(l + 3))
		game->wepth = ft_strdup(ft_strchr(l, '.'));
	else if (*l == 'S')
		game->sprpth = ft_strdup(ft_strchr(l, '.'));
	else if (*l == '1' && l[ft_strlen(l) - 1] == '1')
		game->err = get_map(l, game, fd);
	else
		game->err = -1;
	return (game->err);
}

int		read_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	int		err;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((get_next_line(fd, &line)) > 0)
	{
		err = check_line(line, game, fd);
		if (err < 0)
			return (-1);
		free(line);
	}
	close(fd);
	if (line)
		free(line);
	return (1);
}
