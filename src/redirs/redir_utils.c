/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:35:22 by luiza             #+#    #+#             */
/*   Updated: 2025/09/18 01:16:54 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		create_heredoc_file(char *delimiter);
void		restore_std_fds(int saved_stdin, int saved_stdout);
int			validate_redirection(t_redir *redir);
static int	validate_input_redir(t_redir *redir);
int			apply_redirection(t_redir *redir);

void	create_heredoc_file(char *delimiter)
{
	char			*line;
	int				line_count;
	int				delimiter_len;
	t_env			*env;

	line_count = 1;
	delimiter_len = ft_strlen(delimiter);
	env= *handle_t_env(NULL);
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			if (line)
				free(line);
			restore_normal_signals();
			return ;
		}
		if (line == NULL)
		{
			if (g_exit_status != 130)
			{
				ft_printf("\nminishell: warning: here-document ");
				ft_printf("at line %d delimited by end-of-file (wanted `%s')\n",
					line_count, delimiter);
			}
			restore_normal_signals();
			return ;
		}
		if (ft_strncmp(line, delimiter, delimiter_len) == 0
			&& ft_strlen(line) == (size_t)delimiter_len)
			{
				free(line);
				break ;
			}
		free(line);
		line_count++;
	}
	restore_normal_signals();
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	validate_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
		return (validate_input_redir(redir));
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
	{
		if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell ");
			return (1);
		}
		close(fd);
	}
	return (0);
}

static int	validate_input_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell ");
		return (1);
	}
	close(fd);
	return (0);
}

int	apply_redirection(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (handle_input_redirection(redir));
	else if (redir->type == REDIR_OUT)
		return (handle_output_redirection(redir));
	else if (redir->type == REDIR_APPEND)
		return (handle_append_redirection(redir));
	else if (redir->type == HEREDOC)
		return (handle_heredoc(redir));
	return (0);
}

