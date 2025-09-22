/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:31:21 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 05:33:07 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_error(ERR_ARGS);
	if (!game_init(&game, argv[1]))
		return (1);
	render_game(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	ft_cleanup(&game);
	return (0);
}
