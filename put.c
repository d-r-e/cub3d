/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:35:09 by darodrig          #+#    #+#             */
/*   Updated: 2020/01/21 15:09:29 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        putsq(t_game *game, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            mlx_pixel_put(game->mlx, game->win, x + j, y + i, 0xEEEEEE);
            j++;
        }
        i++;
    }
}

void            put_circle(t_game *game, t_circ c, int color)
{
    float   x;
    float   y;
    int     xmax;
    int     ymax;

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
                mlx_pixel_put(game->mlx, game->win, x, y, color);
            y++;
        }
        x++;
    }
}
