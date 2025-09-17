/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_no_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:28:22 by luiza             #+#    #+#             */
/*   Updated: 2025/09/16 21:15:04 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		create_heredoc_file(char *delimiter);
static void	heredoc_input_loop(struct termios original_termios, char *delimiter);
static char	*read_line_no_history(void);
static int	read_char_to_buffer(char **line, int *i, int *capacity);
static int	process_read_result(char **line, int i, int read_res);

void	create_heredoc_file(char *delimiter)
{
	struct termios	original_termios;

	tcgetattr(STDIN_FILENO, &original_termios);
	heredoc_input_loop(original_termios, delimiter);
}

static void	heredoc_input_loop(struct termios original_termios, char *delimiter)
{
	char			*line;
	int				line_count;
	int				delimiter_len;
	struct termios	new_termios;

	line_count = 1;
	delimiter_len = ft_strlen(delimiter);
	setup_heredoc_signals();
	new_termios = original_termios;
	new_termios.c_lflag &= ~(ECHOCTL);
	new_termios.c_lflag |= ISIG;
	new_termios.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	while (1)
	{
		ft_printf("> ");
		line = read_line_no_history();
		if (line == NULL)
		{
			if (g_exit_status == 130)
			{
				tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
				restore_normal_signals();
				return ;
			}
			if ((*handle_t_env(NULL))->cat_flag == 1)
			{
				(*handle_t_env(NULL))->cat_flag = 0;
				ft_printf("minishell: warning: here-document at line 1");
				ft_printf(" delimited by end-of-file (wanted `EOF')\n");
			}
			else
			{
				ft_printf("\nminishell: warning: here-document ");
				ft_printf("at line %d delimited by end-of-file (wanted `%s')\n",
					line_count, delimiter);
			}
			break ;
		}
		if (ft_strncmp(line, delimiter, delimiter_len) == 0
			&& ft_strlen(line) == (size_t)delimiter_len)
		{
			free(line);
			break ;
		}
		line_count++;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
	restore_normal_signals();
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
		if (read_res == -2 && line)
		{
			free(line);
			return (NULL);
		}
		if (process_read_result(&line, i, read_res))
			break ;
	}
	if (i == 0 && read_res == 0)
	{
		free(line);
		return (NULL);
	}
	if (line)
		line[i] = '\0';
	return (line);
}

static int	read_char_to_buffer(char **line, int *i, int *capacity)
{
	char	buffer[1];
	int		read_res;

	read_res = read(STDIN_FILENO, buffer, 1);
	if (read_res == -1 && errno == EINTR)
		return (-2);
	if (read_res <= 0)
		return (0);
	if (buffer[0] == '\n')
		return (-1);
	if (buffer[0] == 28)
		return (1);
	if (*i >= *capacity - 1)
	{
		*capacity *= 2;
		*line = ft_realloc(*line, *i, *capacity);
		if (!*line)
			return (0);
	}
	if (buffer[0] >= 32 && buffer[0] < 127)
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
