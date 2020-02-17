/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:29:46 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/13 14:40:05 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	itoc(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static void
	fill_header(t_game *game, int fd, int pad)
{
	int				filesize;
	int				i;
	int				tmp;
	unsigned char	header[54];

	i = 0;
	while (i < 54)
		header[i++] = (unsigned char)(0);
	filesize = 54 + (3 * ((int)game->wres + pad) * (int)game->hres);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	itoc(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	tmp = game->wres;
	itoc(header + 18, tmp);
	tmp = game->hres;
	itoc(header + 22, tmp);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	write(fd, header, 54);
}

static	void
	fill_data_img(t_game *game, int fd, int pad)
{
	int				x;
	int				y;
	int				res;

	y = 0;
	res = game->wres * game->hres;
	while (y < game->hres)
	{
		x = 0;
		while (x < game->wres)
		{
			write(fd, &game->img->data[res - (y * game->wres + game->wres - x)],
					3);
			if (pad > 0)
				write(fd, "\0\0\0\0", pad);
			x++;
		}
		y++;
	}
}

int
	screenshot(t_game *game)
{
	int	fd;
	int	pad;

	fd = 0;
	pad = (4 - (game->wres * 3) % 4) % 4;
	if (game->screenshot == 1)
		fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND);
	if (fd == -1)
		return (-1);
	fill_header(game, fd, pad);
	fill_data_img(game, fd, pad);
	close(fd);
	game->screenshot = 0;
	return (0);
}
