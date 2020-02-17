/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:38:30 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 19:38:59 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	pixelput(t_game *game, int x, int y, int color)
{
	if (color < 0)
		color = 0;
	if (y < 0 || y >= game->hres)
		return ;
	game->img->data[y * game->wres + x] = color;
}

void
	new_frame(t_game *game)
{
	game->img = (t_img*)malloc(sizeof(t_img));
	game->img->ptr = mlx_new_image(game->mlx, game->wres, game->hres);
	game->img->data = (int*)mlx_get_data_addr(game->img->ptr, &game->img->bpp,
		&game->img->size_l, &game->img->endian);
	game->img->cdata = mlx_get_data_addr(game->img->ptr, &game->img->bpp,
		&game->img->size_l, &game->img->endian);
}

void
	ver_line(t_game *game, int x, int h, int color)
{
	int	i;
	int start;
	int	end;

	i = 0;
	start = game->hres / 2 - (h / 2);
	end = start + h;
	while (i <= start)
	{
		pixelput(game, x, i, game->ceil);
		i++;
	}
	while (i <= end)
	{
		pixelput(game, x, i, color);
		i++;
	}
	while (i < game->hres)
	{
		pixelput(game, x, i, gradient(game->floor, game->hres - i, game));
		i++;
	}
}

void
	putsq(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < game->scale - 1)
	{
		j = 0;
		while (j < game->scale - 1)
		{
			game->img->data[(y + i) * game->wres + (x + j)] = color;
			j++;
		}
		i++;
	}
}

void
	put_circle(t_game *game, t_circ c, int color)
{
	float	x;
	float	y;
	int		xmax;
	int		ymax;

	x = c.x - (sqrt(2) * c.r);
	xmax = x + (2 * c.r) > RES_W ? RES_W : x + (2 * c.r);
	x = x < 0 ? 0 : x;
	while (x < RES_W)
	{
		y = c.y - (sqrt(2) * c.y);
		ymax = y + (2 * c.r) > RES_H ? RES_H : y + (2 * c.r);
		y = y < 0 ? 0 : y;
		while (y < RES_H)
		{
			if ((pow(c.x - x, 2) + pow(c.y - y, 2) - pow(c.r, 2)) < 10)
				pixelput(game, x, y, color);
			y++;
		}
		x++;
	}
}
