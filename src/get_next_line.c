/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:34:26 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 05:44:20 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	read_buffer(int fd, char *buffer, int *pos, int *bytes_read)
{
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	*pos = 0;
	return (*bytes_read > 0);
}

static char	*add_newline(char *line, int line_len)
{
	line = ft_realloc(line, line_len + 2);
	if (!line)
		return (NULL);
	line[line_len] = '\n';
	line[line_len + 1] = '\0';
	return (line);
}

static char	*process_line(char *line, int *line_len, char *buffer, int *pos)
{
	line = ft_realloc(line, *line_len + 2);
	if (!line)
		return (NULL);
	line[*line_len] = buffer[*pos];
	(*line_len)++;
	(*pos)++;
	return (line);
}

static char	*read_until_newline(int fd, char *buffer, int *pos, int *bytes_read)
{
	char	*line;
	int		line_len;

	line = NULL;
	line_len = 0;
	while (1)
	{
		if (*pos >= *bytes_read && !read_buffer(fd, buffer, pos, bytes_read))
			break ;
		if (buffer[*pos] == '\n')
		{
			line = add_newline(line, line_len);
			if (!line)
				return (NULL);
			(*pos)++;
			break ;
		}
		line = process_line(line, &line_len, buffer, pos);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	pos = 0;
	static int	bytes_read = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_until_newline(fd, buffer, &pos, &bytes_read));
}
