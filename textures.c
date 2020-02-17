/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:07:25 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 15:26:18 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex
	*load_txt(t_game *game, char *path, t_tex *tx)
{
	if (path)
	{
		tx = (t_tex*)malloc(sizeof(t_tex));
		if (!(tx->ptr = mlx_xpm_file_to_image(game->mlx, path, &tx->w, &tx->h)))
			return (NULL);
		tx->data = (int*)mlx_get_data_addr(tx->ptr, &tx->bpp, &tx->size_l,
				&tx->endian);
	}
	else
		return (NULL);
	return (tx);
}

int
	load_textures(t_game *game)
{
	int err;

	err = 0;
	if (!game->nopth || !game->sopth || !game->eapth || !game->wepth ||
		!game->sprpth)
	{
		ft_putstr("No textures loaded\n");
		game->textures = 0;
		return (0);
	}
	game->no = load_txt(game, game->nopth, game->no);
	game->so = load_txt(game, game->sopth, game->so);
	game->ea = load_txt(game, game->eapth, game->ea);
	game->we = load_txt(game, game->wepth, game->we);
	game->sprite = load_txt(game, game->sprpth, game->sprite);
	game->hud = load_txt(game, "./pics/lifebar.xpm", game->hud->ptr);
	game->sky = load_txt(game, "./pics/sky.xpm", game->sky->ptr);
	if (!game->no || !game->so || !game->ea || !game->we || !game->sprite)
		err--;
	if (err == 0)
		game->textures = 1;
	if (game->sprite != NULL)
		game->sprites = 1;
	return (err);
}
