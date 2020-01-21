/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:04:16 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/21 15:51:26 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_r(char *line, t_game *game)
{
	game->wres = 0;
	game->hres = 0;
	if (ft_strlen(line) < 5 || *(line + 1) != ' ')
		return (-1);
	line += 2;
	while (*line >= '0' && *line <= '9')
	{
		game->wres = game->wres * 10 + (*line - '0');
		line++;
	}
	if (*line++ != ' ')
		return (-1);
	while (*line >= '0' && *line <= '9')
	{
		game->hres = game->hres * 10 + (*line - '0');
		line++;
	}
	if (game->wres == 0 || game->hres == 0)
		return (-1);
	if (game->hres > 2880 / 2 || game->wres > 5120 / 2)
	{
		game->hres = RES_H;
		game->wres = RES_W;
	}
	return (0);
}

int		check_f(char *line, t_game *game)
{
	int rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (ft_strlen(line) < 7 || *(line + 1) != ' ' || !ft_isnum(*(line + 2)))
		return (-1);
	line += 2;
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
	game->floorcolor = rgb_int(rgb[0], rgb[1], rgb[2]);
	return (0);
}

int		check_c(char *line, t_game *game)
{
	int		rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (ft_strlen(line) < 7 || *(line + 1) != ' ' || !ft_isnum(*(line + 2)))
		return (-1);
	line += 2;
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
	game->ceilcolor = rgb_int(rgb[0], rgb[1], rgb[2]);
	return (0);
}

char	*ft_cutspaces(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (' ' != str[i])
			len++;
		i++;
	}
	new = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
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
		if (*ln == '\n')
			break ;
		tmp = ft_strjoin(game->mapstr, ln);
		free(game->mapstr);
		free(ln);
		game->mapstr = tmp;
	}
	tmp = ft_cutspaces(game->mapstr);
	free(game->mapstr);
	game->mapstr = tmp;
	game->mapw = maplen;
	return (0);
}

int		check_line(char *l, t_game *game, int fd)
{
	int err;

	err = 0;
	if (*l == '\0')
		err = 0;
	else if (*l == 'R')
		err = check_r(l, game);
	else if (*l == 'F')
		err = check_f(l, game);
	else if (*l == 'C')
		err = check_c(l, game);
	else if (*l == 'S' && *(l + 1) == 'O' && *(l + 2) == ' ' && *(l + 3))
		game->sopth = ft_strdup(&(*(l + 3)));
	else if (*l == 'N' && *(l + 1) == 'O' && *(l + 2) == ' ' && *(l + 3))
		game->nopth = ft_strdup(&(*(l + 3)));
	else if (*l == 'E' && *(l + 1) == 'A' && *(l + 2) == ' ' && *(l + 3))
		game->eapth = ft_strdup(l + 3);
	else if (*l == 'W' && *(l + 1) == 'E' && *(l + 2) == ' ' && *(l + 3))
		game->wepth = ft_strdup(l + 3);
	else if (*l == '1')
		err = get_map(l, game, fd);
	else
		err = -1;
	return (err);
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
	free(line);
	return (1);
}
