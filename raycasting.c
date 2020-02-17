/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:35:41 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/17 09:57:48 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	ft_caster3(t_game *game, t_ray *r)
{
	r->camerax = 2 * (r->x / (double)game->wres) - 1;
	r->raydirx = r->dirx + r->planex * r->camerax;
	r->raydiry = r->diry + r->planey * r->camerax;
	r->mapx = (int)(r->posx);
	r->mapy = (int)(r->posy);
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
	r->hit = 0;
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (r->posx - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - r->posx) * r->deltadistx;
	}
	if (r->raydiry < 0 && (r->stepy = -1))
		r->sidedisty = (r->posy - r->mapy) * r->deltadisty;
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - r->posy) * r->deltadisty;
	}
}

static void
	ft_caster2(t_game *game, t_ray *r)
{
	while (r->stripe < r->drawendx)
	{
		r->texx = (int)(256 * (r->stripe - (-r->spritewidth /
				2 + r->spritescreenx)) * TEXW / r->spritewidth) / 256;
		if (r->transformy > 0 && r->stripe > 0 && r->stripe < game->wres &&
				r->transformy < r->zbuffer[r->stripe])
			r->y = r->drawstarty;
		while (r->y < r->drawendy)
		{
			r->d = (r->y) * 256 - game->hres * 128 + r->spriteheight * 128;
			r->texy = ((r->d * TEXW) / r->spriteheight) / 256;
			r->color = game->sprite->data[TEXW * r->texy + r->texx];
			if ((r->color) != 0)
				pixelput(game, r->stripe, r->y, faded_color(r->color,
						r->zbuffer[r->stripe] - 6));
			r->y++;
		}
		r->stripe++;
	}
	r->counter++;
}

static void
	ft_caster1(t_game *game, t_ray *r)
{
	render_dist(game);
	bubble_texture(game);
	r->spritex = game->locations[r->counter].x + 1 - r->posx;
	r->spritey = game->locations[r->counter].y + 1 - r->posy;
	r->inv = 1.0 / (r->planex * r->diry - r->dirx * r->planey);
	r->transformx = r->inv * (r->diry * r->spritex - r->dirx * r->spritey);
	r->transformy = r->inv * (-r->planey * r->spritex + r->planex * r->spritey);
	r->spritescreenx = ((game->wres / 2) * (1 + r->transformx / r->transformy));
	r->spriteheight = abs((int)(game->hres / (r->transformy)));
	r->drawstarty = -r->spriteheight / 2 + game->hres / 2;
	if (r->drawstarty < 0)
		r->drawstarty = 0;
	r->drawendy = r->spriteheight / 2 + game->hres / 2;
	if (r->drawendy >= game->hres)
		r->drawendy = game->hres - 1;
	r->spritewidth = abs((int)(game->hres / (r->transformy)));
	r->drawstartx = -r->spritewidth / 2 + r->spritescreenx;
	if (r->drawstartx < 0)
		r->drawstartx = 0;
	r->drawendx = r->spritewidth / 2 + r->spritescreenx;
	if (r->drawendx >= game->wres)
		r->drawendx = game->wres - 1;
	r->stripe = r->drawstartx;
}

static void
	ft_caster8(t_game *game, t_ray *r)
{
	ft_caster3(game, r);
	ft_caster4(game, r);
	ft_caster5(game, r);
	if (game->textures == 0)
		ver_line(game, r->x, r->lineheight, r->color);
	else
	{
		ft_caster6(game, r);
		ft_caster7(game, r);
	}
	r->zbuffer[r->x] = r->perpwalldist;
	r->x++;
}

int
	ft_caster(t_game *game)
{
	t_ray	*r;

	r = malloc(sizeof(t_ray));
	ft_caster_init(game, r);
	r->x = 0;
	while (r->x < game->wres)
		ft_caster8(game, r);
	r->counter = 0;
	delete_objects(game);
	while (game->sprites == 1 && r->counter < game->numsprites)
	{
		ft_caster1(game, r);
		ft_caster2(game, r);
	}
	if (game->screenshot == 1)
		screenshot(game);
	free(r->zbuffer);
	free(r);
	return (0);
}
