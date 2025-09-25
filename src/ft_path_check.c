/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:22:41 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/25 17:22:41 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**ft_dup_map(char **src, int rows)
{
    char    **dup;
    int     i;

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
    int i;

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

static void	ft_flood_fill(char **grid, int rows, int cols, int y, int x, int *coins)
{
    if (y < 0 || y >= rows || x < 0 || x >= cols)
        return ;
    if (!ft_is_walkable(grid[y][x]))
        return ;
    if (grid[y][x] == COINS)
        (*coins)++;
    grid[y][x] = 'V';
    ft_flood_fill(grid, rows, cols, y - 1, x, coins);
    ft_flood_fill(grid, rows, cols, y + 1, x, coins);
    ft_flood_fill(grid, rows, cols, y, x - 1, coins);
    ft_flood_fill(grid, rows, cols, y, x + 1, coins);
}

void	ft_check_reachability(t_game *game)
{
    char	**dup;
    int		reachable_coins;

    dup = ft_dup_map(game->map.full, game->map.rows);
    if (!dup)
        ft_error_msg("Memory allocation failed during path check.", game);
    reachable_coins = 0;
    ft_flood_fill(dup, game->map.rows, game->map.columns,
        game->map.player.y, game->map.player.x, &reachable_coins);
    ft_free_dup_map(dup, game->map.rows);
    if (reachable_coins < game->map.coins)
        ft_error_msg("Invalid Map. There are unreachable Coins!", game);
}

