/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:35:22 by luiza             #+#    #+#             */
/*   Updated: 2025/09/18 20:56:38 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc_line(char *delimiter, int line_count, int fd_archive);
void		create_heredoc_file(char *delimiter, int archive_fd, char *tmp_heredoc);
int			validate_redirection(t_redir *redir);
static int	validate_input_redir(t_redir *redir);
int			apply_redirection(t_redir *redir);

static int	read_heredoc_line(char *delimiter, int line_count, int fd_archive)
{
	char	*line;
	int		delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	line = readline("> ");
	if ((*handle_exit_status())->exit_status == 130)
	{
		if (line)
			free(line);
		return (1);
	}
	if (line == NULL)
	{
		ft_printf("\nminishell: warning: here-document ");
		ft_printf("at line %d delimited by end-of-file (wanted `%s')\n",
			line_count, delimiter);
		return (2);
	}
	if (ft_strncmp(line, delimiter, delimiter_len) == 0
		&& ft_strlen(line) == (size_t)delimiter_len)
		return (free(line), 3);
	ft_putendl_fd(line, fd_archive);
	return (free(line), 0);
}

void	create_heredoc_file(char *delimiter, int archive_fd, char *tmp_heredoc)
{
	int	line_count;
	int	status;

	line_count = 1;
	setup_heredoc_signals();
	while (1)
	{
		status = read_heredoc_line(delimiter, line_count, archive_fd);
		if (status == 1 || status == 2)
		{
			restore_normal_signals();
			return ;
		}
		if (status == 3)
		{
			close(archive_fd);
			int fd_open = open(tmp_heredoc, O_RDONLY);
			dup2(fd_open, STDIN_FILENO);
			close(fd_open);
			return ;
		}
		line_count++;
	}
	restore_normal_signals();
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
