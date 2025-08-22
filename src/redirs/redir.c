/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:14:39 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 21:07:25 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirections(t_command *cmd);
int	handle_input_redirection(t_redir *redir);
int	handle_output_redirection(t_redir *redir);
int	handle_append_redirection(t_redir *redir);
int	handle_heredoc(t_redir *redir);

int	setup_redirections(t_command *cmd)
{
	t_redir	*current_redir;
	int		result;

	if (!cmd || !cmd->redirs)
		return (0);
	current_redir = cmd->redirs;
	while (current_redir)
	{
		if (current_redir->type != HEREDOC)
		{
			result = validate_redirection(current_redir);
			if (result != 0)
				return (result);
		}
		current_redir = current_redir->next;
	}
	current_redir = cmd->redirs;
	while (current_redir)
	{
		result = apply_redirection(current_redir);
		if (result != 0)
			return (result);
		current_redir = current_redir->next;
	}
	return (0);
}

int	handle_input_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("minishell: %s: ", redir->file);
		perror(" ");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 ");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("minishell: %s: ", redir->file);
		perror(" ");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 ");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_append_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("minishell: %s: ", redir->file);
		perror(" ");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 ");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(t_redir *redir)
{
	int		heredoc_fd;
	char	*delimiter;

	delimiter = redir->file;
	heredoc_fd = create_heredoc_file(delimiter);
	if (heredoc_fd == -1)
		return (1);
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 ");
		close(heredoc_fd);
		return (1);
	}
	close(heredoc_fd);
	return (0);
}
