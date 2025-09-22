/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 03:47:56 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_player_found(t_game *game, char **copy, int x, int y,
		int *collectibles, int *exit_found)
{
	t_flood_fill	ff;

	ff.map = copy;
	ff.x = x;
	ff.y = y;
	ff.width = game->map.width;
	ff.height = game->map.height;
	ff.collectibles = collectibles;
	ff.exit_found = exit_found;
	flood_fill(&ff);
}

void	find_player_and_flood(t_game *game, char **copy,
		int *collectibles, int *exit_found)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (copy[y][x] == PLAYER)
			{
				process_player_found(game, copy, x, y, collectibles, exit_found);
				return ;
			}
			x++;
		}
		y++;
	}
}
