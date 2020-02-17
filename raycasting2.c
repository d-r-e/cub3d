/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:13:24 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 19:40:51 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ft_caster_init(t_game *game, t_ray *r)
{
	r->posx = game->map->x;
	r->posy = game->map->y;
	r->dirx = game->map->dirx;
	r->diry = game->map->diry;
	r->planex = game->map->planex;
	r->planey = game->map->planey;
	r->zbuffer = malloc(sizeof(double) * game->wres);
}

void
	ft_caster7(t_game *game, t_ray *r)
{
	while (r->y < r->drawend)
	{
		r->texy = (int)r->texpos & (TEXW - 1);
		r->texpos += r->step;
		r->color = r->tx->data[TEXW * r->texy + r->texx];
		if (r->side == 1)
			r->color = (r->color >> 1) & 8355711;
		pixelput(game, r->x, r->y, faded_color(r->color, r->perpwalldist));
		r->y++;
	}
	r->y = r->drawend;
	while (r->y < game->hres)
		pixelput(game, r->x, r->y++, gradient(game->floor, game->hres - r->y,
				game));
}

void
	ft_caster6(t_game *game, t_ray *r)
{
	r->tx = game->ea;
	if (r->side == 0)
		r->tx = game->we;
	if (r->side == 0)
		r->wallx = r->posy + r->perpwalldist * r->raydiry;
	else
		r->wallx = r->posx + r->perpwalldist * r->raydirx;
	r->wallx -= floor((r->wallx));
	r->texx = (int)(r->wallx * TEXW);
	if (r->side == 0 && r->raydirx > 0)
		r->texx = TEXW - r->texx - 1;
	if (r->side == 1 && r->raydiry < 0)
		r->texx = TEXW - r->texx - 1;
	r->step = 1.0 * TEXW / r->lineheight;
	r->drawstart = game->hres / 2 - r->lineheight / 2;
	r->drawend = game->hres / 2 + r->lineheight / 2;
	r->texpos = (r->drawstart - game->hres / 2 + r->lineheight / 2) * r->step;
	r->y = 0;
	while (r->y <= r->drawstart)
		pixelput(game, r->x, r->y++, game->sky->data[r->y * game->wres + r->x +
				game->offset]);
	r->y = r->drawstart;
}

void
	ft_caster5(t_game *game, t_ray *r)
{
	if (r->side == 0)
		r->perpwalldist = (r->mapx - r->posx + (1 - r->stepx) / 2) / r->raydirx;
	else
		r->perpwalldist = (r->mapy - r->posy + (1 - r->stepy) / 2) / r->raydiry;
	r->lineheight = (int)(game->hres / r->perpwalldist);
	r->color = WHITE;
	if (r->side == 1)
		r->color = r->color * 0.8;
}

void
	ft_caster4(t_game *game, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (game->map->walls[r->mapy][r->mapx] == 1)
			r->hit = 1;
	}
}
