/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 06:29:37 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_flood_fill *ff)
{
	char	original;

	if (ff->x < 0 || ff->x >= ff->width || ff->y < 0 || ff->y >= ff->height)
		return ;
	if (ff->map[ff->y][ff->x] == WALL || ff->map[ff->y][ff->x] == 'V')
		return ;
	original = ff->map[ff->y][ff->x];
	ff->map[ff->y][ff->x] = 'V';
	if (original == COLLECTIBLE)
		(*ff->collectibles)++;
	else if (original == EXIT)
		(*ff->exit_found)++;
	ff->x++;
	flood_fill(ff);
	ff->x -= 2;
	flood_fill(ff);
	ff->x++;
	ff->y++;
	flood_fill(ff);
	ff->y -= 2;
	flood_fill(ff);
	ff->y++;
}

