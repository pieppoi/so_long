/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 06:49:41 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/25 17:06:19 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_map(t_game *game)
{
	ft_check_rectangle(game);
	ft_check_rows(game);
	ft_check_columns(game);
	ft_count_map_parameters(game);
	ft_verify_map_parameters(game);
	ft_check_reachability(game);
}

static int	ft_line_length(const char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

void	ft_check_rectangle(t_game *game)
{
	int	i;
	int	first_len;
	int	current_len;

	if (game->map.rows <= 0 || !game->map.full || !game->map.full[0])
		ft_error_msg("Invalid Map. Empty content.", game);
	first_len = ft_line_length(game->map.full[0]);
	if (first_len <= 0)
		ft_error_msg("Invalid Map. First line is empty.", game);
	i = 1;
	while (i < game->map.rows)
	{
		current_len = ft_line_length(game->map.full[i]);
		if (current_len != first_len)
			ft_error_msg("Invalid Map. The map is not rectangular.", game);
		i++;
	}
	game->map.columns = first_len;
}
