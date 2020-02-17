/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:17:28 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/16 15:32:04 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_isalpha(char c)
{
	if (c <= 'Z' && c >= 'A')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int
	rgb_int(int red, int green, int blue)
{
	int rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	pix_pos(int x, int y, t_game *game)
{
	return (x * 4 + 4 * game->wres * y);
}

char
	*ft_cutspaces(char *str)
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

void
	initial_values(t_game *game)
{
	game->offset = 0;
	game->textures = 0;
	game->floor = rgb_int(100, 100, 100);
	game->ceil = 0x003e2222;
	game->up = 0;
	game->down = 0;
	game->left = 0;
	game->right = 0;
	game->turnleft = 0;
	game->turnright = 0;
	game->mira = 1;
	game->minimap = 0;
	game->scale = 9;
	game->sprites = 0;
	game->wres = RES_W;
	game->hres = RES_H;
	game->nopth = NULL;
	game->sopth = NULL;
	game->eapth = NULL;
	game->wepth = NULL;
	game->sprite = 0;
	game->screenshot = 0;
}
