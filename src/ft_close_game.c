/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 06:49:56 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/25 17:06:33 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_victory(t_game *game)
{
	printf(GREEN"congratulations!\n"RESET);
	printf(CYAN"Movements: %d\n"RESET, ++game->movements);
	ft_free_all_allocated_memory(game);
	exit (EXIT_SUCCESS);
}

int	ft_close_game(t_game *game)
{
	printf(CYAN"Movements: %d\n"RESET, game->movements);
	ft_free_all_allocated_memory(game);
	printf(GREY"CLOSED\n"RESET);
	exit (EXIT_SUCCESS);
}

int	ft_error_msg(char *message, t_game *game)
{
	if (game->map_alloc == true)
		ft_free_map(game);
	free(game);
	printf(RED"Error\n"GREY"%s\n"RESET, message);
	exit (EXIT_FAILURE);
}
