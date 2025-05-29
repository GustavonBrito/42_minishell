/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:11 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:36:12 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"

char	*extract_line(char **buffer)
{
	char	*new_line;
	char	*line;
	int		line_length;

	if (*buffer == NULL || **buffer == '\0')
		return (NULL);
	new_line = ft_strchr_gnl(*buffer, '\n');
	if (!new_line)
	{
		line = ft_strdup_gnl(*buffer);
		if (!line)
			return (NULL);
		(*buffer)[0] = '\0';
		return (line);
	}
	line_length = new_line - *buffer;
	line = malloc(sizeof(char) * (line_length + 2));
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(line, *buffer, line_length + 2);
	ft_strlcpy_gnl(*buffer, new_line + 1, ft_strlen_gnl(new_line));
	return (line);
}

char	*find_newline_in_buffer(char **buffer, int fd)
{
	ssize_t	bytes_read;
	char	*tmp;
	char	*read_buffer;

	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	while (!ft_strchr_gnl(*buffer, '\n'))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buffer), NULL);
		if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = '\0';
		tmp = *buffer;
		*buffer = ft_strjoin_gnl(*buffer, read_buffer);
		free(tmp);
		if (!*buffer)
			return (free(read_buffer), NULL);
	}
	free(read_buffer);
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	if (!find_newline_in_buffer(&buffer, fd))
	{
		free(buffer);
		return (buffer = NULL, buffer);
	}
	line = extract_line(&buffer);
	if (!line || (line[0] == '\0' && buffer[0] == '\0'))
		return (free(line), free(buffer), buffer = NULL, NULL);
	return (line);
}
