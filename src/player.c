/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:34:48 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 03:56:13 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves(int moves)
{
	char	*str;
	size_t	len;

	str = ft_itoa(moves);
	if (!str)
		return ;
	len = ft_strlen(str);
	write(1, "Moves: ", 7);
	write(1, str, len);
	write(1, "\n", 1);
	free(str);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (game->game_over)
		return (0);
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	else if (keycode == KEY_ESC)
		handle_close(game);
	return (0);
}

static int	handle_collectible_and_exit(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == COLLECTIBLE)
	{
		game->player.collected++;
		game->map.collectibles--;
	}
	if (game->map.grid[new_y][new_x] == EXIT && game->map.collectibles == 0)
	{
		game->win_condition = 1;
		game->game_over = 1;
		return (1);
	}
	return (0);
}

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player.pos.x + dx;
	new_y = game->player.pos.y + dy;
	if (!is_valid_move(game, new_x, new_y))
		return (0);
	if (handle_collectible_and_exit(game, new_x, new_y))
		return (1);
	game->map.grid[game->player.pos.y][game->player.pos.x] = EMPTY;
	game->map.grid[new_y][new_x] = PLAYER;
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	game->player.moves++;
	print_moves(game->player.moves);
	return (1);
}

int	is_valid_move(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (0);
	if (game->map.grid[y][x] == WALL)
		return (0);
	if (game->map.grid[y][x] == EXIT && game->map.collectibles > 0)
		return (0);
	return (1);
}
