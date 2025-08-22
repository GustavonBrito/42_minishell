/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_no_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:28:22 by luiza             #+#    #+#             */
/*   Updated: 2025/08/08 23:28:37 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			create_heredoc_file(char *delimiter);
static void	heredoc_input_loop(int pipe_fd, char *delimiter);
static char	*read_line_no_history(void);
static int	read_char_to_buffer(char **line, int *i, int *capacity);
static int	process_read_result(char **line, int i, int read_res);

int	create_heredoc_file(char *delimiter)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe ");
		return (-1);
	}
	heredoc_input_loop(pipe_fd[1], delimiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static void	heredoc_input_loop(int pipe_fd, char *delimiter)
{
	char	*line;

	ft_printf("> ");
	line = read_line_no_history();
	while (line != NULL)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
		ft_printf("> ");
		line = read_line_no_history();
	}
}

static char	*read_line_no_history(void)
{
	char	*line;
	int		i;
	int		capacity;
	int		read_res;

	capacity = 128;
	line = malloc(capacity);
	if (!line)
		return (NULL);
	i = 0;
	while (1)
	{
		read_res = read_char_to_buffer(&line, &i, &capacity);
		if (process_read_result(&line, i, read_res))
			break ;
	}
	if (line)
		line[i] = '\0';
	return (line);
}

static int	read_char_to_buffer(char **line, int *i, int *capacity)
{
	char	buffer[1];

	if (read(STDIN_FILENO, buffer, 1) <= 0)
		return (0);
	if (buffer[0] == '\n')
		return (-1);
	if (*i >= *capacity - 1)
	{
		*capacity *= 2;
		*line = ft_realloc(*line, *i, *capacity);
		if (!*line)
			return (0);
	}
	(*line)[(*i)++] = buffer[0];
	return (1);
}

static int	process_read_result(char **line, int i, int read_res)
{
	if (read_res == -1)
		return (1);
	if (read_res == 0)
	{
		if (i == 0)
		{
			free(*line);
			*line = NULL;
			return (1);
		}
		return (1);
	}
	return (0);
}
