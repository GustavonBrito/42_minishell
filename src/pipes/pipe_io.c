/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:08 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 20:30:38 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		setup_child_pipes(t_pipe *pipes, int cmd_index);
static void	close_unused_pipes(t_pipe *pipes, int cmd_index);
void		free_pipe_fds(t_pipe *pipes);
static void	close_and_free_single_pipe(t_pipe *pipes, int index);
void		free_partial_fds(t_pipe *pipes, int max_index);

void	setup_child_pipes(t_pipe *pipes, int cmd_index)
{
	if (cmd_index > 0)
	{
		if (pipes->pipe_fds[cmd_index - 1][0] != -1)
		{
			if (dup2(pipes->pipe_fds[cmd_index - 1][0], STDIN_FILENO) == -1)
				exit(1);
		}
	}
	if (cmd_index < pipes->total_commands - 1)
	{
		if (pipes->pipe_fds[cmd_index][1] != -1)
		{
			if (dup2(pipes->pipe_fds[cmd_index][1], STDOUT_FILENO) == -1)
				exit(1);
		}
	}
	close_unused_pipes(pipes, cmd_index);
}

static void	close_unused_pipes(t_pipe *pipes, int cmd_index)
{
	int	i;

	i = 0;
	while (i < (pipes->total_commands - 1))
	{
		if (i != (cmd_index - 1))
		{
			if (pipes->pipe_fds[i][0] != -1)
			{
				close(pipes->pipe_fds[i][0]);
				pipes->pipe_fds[i][0] = -1;
			}
		}
		if (i != cmd_index)
		{
			if (pipes->pipe_fds[i][1] != -1)
			{
				close(pipes->pipe_fds[i][1]);
				pipes->pipe_fds[i][1] = -1;
			}
		}
		i++;
	}
}

void	free_pipe_fds(t_pipe *pipes)
{
	int	i;

	if (!pipes->pipe_fds)
		return ;
	i = 0;
	while (i < (pipes->total_commands - 1))
	{
		close_and_free_single_pipe(pipes, i);
		i++;
	}
	free(pipes->pipe_fds);
	pipes->pipe_fds = NULL;
}

static void	close_and_free_single_pipe(t_pipe *pipes, int index)
{
	if (!pipes->pipe_fds[index])
		return ;
	close_pipe_fd(&pipes->pipe_fds[index][0]);
	close_pipe_fd(&pipes->pipe_fds[index][1]);
	free(pipes->pipe_fds[index]);
	pipes->pipe_fds[index] = NULL;
}

void	free_partial_fds(t_pipe *pipes, int max_index)
{
	int	i;

	if (!pipes->pipe_fds)
		return ;
	i = 0;
	while (i < max_index)
	{
		if (pipes->pipe_fds[i])
		{
			free(pipes->pipe_fds[i]);
			pipes->pipe_fds[i] = NULL;
		}
		i++;
	}
	free(pipes->pipe_fds);
	pipes->pipe_fds = NULL;
	if (pipes->pids)
	{
		free(pipes->pids);
		pipes->pids = NULL;
	}
}
