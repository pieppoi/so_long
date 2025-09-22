/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 06:10:54 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_rectangle(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if ((int)ft_strlen(game->map.grid[y]) != game->map.width)
		{
			ft_error(ERR_MAP_RECTANGLE);
			return (0);
		}
		y++;
	}
	return (1);
}

static int	check_horizontal_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->map.width)
	{
		if (game->map.grid[0][x] != WALL ||
			game->map.grid[game->map.height - 1][x] != WALL)
		{
			ft_error(ERR_MAP_WALLS);
			return (0);
		}
		x++;
	}
	return (1);
}

static int	check_vertical_walls(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != WALL ||
			game->map.grid[y][game->map.width - 1] != WALL)
		{
			ft_error(ERR_MAP_WALLS);
			return (0);
		}
		y++;
	}
	return (1);
}

int	check_basic_validation(t_game *game)
{
	if (!check_rectangle(game))
		return (0);
	if (!check_horizontal_walls(game))
		return (0);
	if (!check_vertical_walls(game))
		return (0);
	return (1);
}
