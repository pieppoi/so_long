/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 07:08:56 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**create_map_copy(t_game *game)
{
	char	**copy;
	int		y;

	copy = ft_malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		copy[y] = ft_malloc(sizeof(char) * (game->map.width + 1));
		if (!copy[y])
		{
			ft_free_map_array(copy, y);
			return (NULL);
		}
		ft_memcpy(copy[y], game->map.grid[y], game->map.width);
		copy[y][game->map.width] = '\0';
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

