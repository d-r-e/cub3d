/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:30:43 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 19:42:19 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	inverse_color(int color)
{
	int r;
	int g;
	int b;

	r = 255 - ((color >> 16) & 0x00);
	g = 255 - ((color >> 8) & 0x00);
	b = 255 - ((color >> 0) & 0x00);
	return (rgb_int(r, g, b));
}

int
	gradient(int color, int i, t_game *game)
{
	int r;
	int g;
	int b;

	r = (color & 0x00FF0000) >> 16;
	g = (color & 0x0000FF00) >> 8;
	b = (color & 0x000000FF) >> 0;
	r -= r * i / game->hres;
	g -= g * i / game->hres;
	b -= b * i / game->hres;
	r = (r < 0) ? 0 : r;
	g = (g < 0) ? 0 : g;
	b = (g < 0) ? 0 : b;
	return (rgb_int(r, g, b));
}

int
	faded_color(int color, int dist)
{
	int r;
	int g;
	int b;

	if (dist < 0)
		dist = 0;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	r -= 5 * dist;
	g -= 5 * dist;
	b -= 5 * dist;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (rgb_int(r, g, b));
}

void
	put_mira(t_game *game)
{
	int x;
	int	y;
	int color;

	y = game->hres / 2 - 9;
	while (y < game->hres / 2 + 9)
	{
		x = game->wres / 2 - 9;
		while (x < game->wres / 2 + 9)
		{
			if (y == game->hres / 2 || x == game->wres / 2)
			{
				color = game->img->data[y * game->wres + x];
				color = inverse_color(color);
				pixelput(game, x, y, color);
			}
			x++;
		}
		y++;
	}
}
