/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:33:53 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 05:33:55 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_close(t_game *game)
{
	ft_cleanup(game);
	exit(0);
}

int	game_loop(t_game *game)
{
	render_game(game);
	if (game->win_condition && game->game_over)
		handle_close(game);
	return (0);
}
