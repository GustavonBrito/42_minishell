/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 07:44:53 by gserafio          #+#    #+#             */
/*   Updated: 2025/09/18 21:02:43 by lukorman         ###   ########.fr       */
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
		perror("minishell ");
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
		perror("minishell ");
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
		perror("minishell ");
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
	char	*delimiter;
	int		fd_heredoc;
	char	*tmp_heredoc;
	char	*itoa_agregator;

	itoa_agregator = ft_itoa((*handle_t_env(NULL))->fd_cat++);
	tmp_heredoc = ft_strjoin("heredoc", itoa_agregator);
	fd_heredoc = open(tmp_heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	delimiter = redir->file;
	(*handle_exit_status())->exit_status = 0;
	create_heredoc_file(delimiter, fd_heredoc, tmp_heredoc);
	free(tmp_heredoc);
	free(itoa_agregator);
	close(fd_heredoc);
	return ((*handle_exit_status())->exit_status);
}
