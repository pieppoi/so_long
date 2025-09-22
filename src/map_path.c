/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 02:44:28 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_valid_path(t_game *game)
{
	char	**copy;
	int		collectibles_found;
	int		exit_found;

	copy = create_map_copy(game);
	if (!copy)
		return (0);
	collectibles_found = 0;
	exit_found = 0;
	find_player_and_flood(game, copy, &collectibles_found, &exit_found);
	if (collectibles_found != game->map.collectibles || exit_found != 1)
	{
		ft_free_map_array(copy, game->map.height);
		ft_error(ERR_MAP_PATH);
		return (0);
	}
	ft_free_map_array(copy, game->map.height);
	return (1);
}
