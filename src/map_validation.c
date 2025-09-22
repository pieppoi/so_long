/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 02:44:28 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	process_tile_and_count(char c, t_game *game)
{
	if (c == PLAYER)
		game->map.players++;
	else if (c == EXIT)
		game->map.exits++;
	else if (c == COLLECTIBLE)
		game->map.collectibles++;
	else if (c != WALL && c != EMPTY)
	{
		ft_error(ERR_MAP_INVALID);
		return (0);
	}
	return (1);
}

static int	count_elements(t_game *game)
{
	int		x;
	int		y;
	char	c;

	game->map.players = 0;
	game->map.exits = 0;
	game->map.collectibles = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!process_tile_and_count(c, game))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	validate_elements(t_game *game)
{
	if (game->map.players != 1)
	{
		ft_error(ERR_MAP_PLAYER);
		return (0);
	}
	if (game->map.exits != 1)
	{
		ft_error(ERR_MAP_EXIT);
		return (0);
	}
	if (game->map.collectibles < 1)
	{
		ft_error(ERR_MAP_COLLECTIBLE);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_basic_validation(game))
		return (0);
	if (!count_elements(game))
		return (0);
	if (!validate_elements(game))
		return (0);
	if (!check_valid_path(game))
		return (0);
	return (1);
}
