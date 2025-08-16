/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:35:22 by luiza             #+#    #+#             */
/*   Updated: 2025/08/08 19:31:13 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		restore_std_fds(int saved_stdin, int saved_stdout);
int			validate_redirection(t_redir *redir);
static int	validate_input_redir(t_redir *redir);
int			apply_redirection(t_redir *redir);
char		*ft_realloc(char *ptr, int old_size, int new_size);

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
			perror(" ");
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
		perror(" ");
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

char	*ft_realloc(char *ptr, int old_size, int new_size)
{
	char	*new_ptr;
	int		i;

	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	i = 0;
	while (i < old_size && i < new_size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
