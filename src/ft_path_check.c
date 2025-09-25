/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:22:41 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/25 17:27:51 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**ft_dup_map(char **src, int rows)
{
	char	**dup;
	int		i;

	dup = (char **)ft_calloc(rows + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dup[i] = ft_strdup(src[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[rows] = NULL;
	return (dup);
}

static void	ft_free_dup_map(char **map, int rows)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	ft_is_walkable(char c)
{
	return (c == FLOOR || c == COINS || c == PLAYER);
}

static void	ft_flood_fill(t_ff ctx, int y, int x)
{
	if (y < 0 || y >= ctx.rows || x < 0 || x >= ctx.cols)
		return ;
	if (!ft_is_walkable(ctx.grid[y][x]))
		return ;
	if (ctx.grid[y][x] == COINS)
		(*ctx.coins)++;
	ctx.grid[y][x] = 'V';
	ft_flood_fill(ctx, y - 1, x);
	ft_flood_fill(ctx, y + 1, x);
	ft_flood_fill(ctx, y, x - 1);
	ft_flood_fill(ctx, y, x + 1);
}

void	ft_check_reachability(t_game *game)
{
	char	**dup;
	int		reachable_coins;
	t_ff	ctx;

	dup = ft_dup_map(game->map.full, game->map.rows);
	if (!dup)
		ft_error_msg("Memory allocation failed during path check.", game);
	reachable_coins = 0;
	ctx.grid = dup;
	ctx.rows = game->map.rows;
	ctx.cols = game->map.columns;
	ctx.coins = &reachable_coins;
	ft_flood_fill(ctx, game->map.player.y, game->map.player.x);
	ft_free_dup_map(dup, game->map.rows);
	if (reachable_coins < game->map.coins)
		ft_error_msg("Invalid Map. There are unreachable Coins!", game);
}
