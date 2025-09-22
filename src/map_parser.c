/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:25:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 07:06:09 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	parse_map_lines(t_game *game, char *content);

static char	*read_file_content(int fd)
{
	char	*line;
	char	*map_content;
	char	*temp;

	map_content = ft_strdup("");
	if (!map_content)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = map_content;
		map_content = ft_strjoin(map_content, line);
		free(temp);
		free(line);
		if (!map_content)
			return (NULL);
	}
	return (map_content);
}

static char	*read_map_file(char *map_file)
{
	int		fd;
	char	*map_content;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_error(ERR_FILE);
		return (NULL);
	}
	map_content = read_file_content(fd);
	close(fd);
	return (map_content);
}

int	parse_map(t_game *game, char *map_file)
{
	char	*map_content;

	map_content = read_map_file(map_file);
	if (!map_content)
		return (0);
	if (!parse_map_lines(game, map_content))
	{
		free(map_content);
		return (0);
	}
	free(map_content);
	if (!validate_map(game))
		return (0);
	return (1);
}

static int	allocate_map_grid(t_game *game, char **lines)
{
	int	i;

	game->map.grid = ft_malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
	{
		ft_free_array(lines);
		return (0);
	}
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(lines[i]);
		if (!game->map.grid[i])
		{
			ft_free_array(game->map.grid);
			ft_free_array(lines);
			return (0);
		}
		i++;
	}
	game->map.grid[i] = NULL;
	return (1);
}

int	parse_map_lines(t_game *game, char *content)
{
	char	**lines;

	lines = ft_split(content, '\n');
	if (!lines)
		return (0);
	game->map.height = 0;
	while (lines[game->map.height])
		game->map.height++;
	if (game->map.height == 0)
	{
		ft_free_array(lines);
		return (0);
	}
	game->map.width = ft_strlen(lines[0]);
	if (!allocate_map_grid(game, lines))
		return (0);
	ft_free_array(lines);
	return (1);
}
