/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:08 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 19:42:48 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			init_pipeline(t_pipe *pipes, t_command *cmd);
static int	init_pipe_arrays(t_pipe *pipes);
static void	init_pipe_fds(t_pipe *pipes);
int			count_commands(t_command *cmd);
int			create_pipe(int pipe_fd[2]);
void		cleanup_pipeline(t_pipe *pipes);
static void	free_pipe_fds(t_pipe *pipes);
static void	free_partial_fds(t_pipe *pipes, int max_index);

int	init_pipeline(t_pipe *pipes, t_command *cmd)
{
	if (!pipes || !cmd)
	{
		g_exit_status = 1;
		return (-1);
	}
	ft_memset(pipes, 0, sizeof(t_pipe));
	pipes->total_commands = count_commands(cmd);
	if (pipes->total_commands <= 0)
	{
		g_exit_status = 1;
		return (-1);
	}
	return (init_pipe_arrays(pipes));
}

int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*current;

	if (!cmd)
	{
		g_exit_status = 1;
		return (0);
	}
	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	init_pipe_arrays(t_pipe *pipes)
{
	int	i;

	pipes->pids = malloc(sizeof(pid_t) * pipes->total_commands);
	if (!pipes->pids)
	{
		g_exit_status = 1;
		return (-1);
	}
	i = 0;
	while (i < pipes->total_commands)
	{
		pipes->pids[i] = -1;
		i++;
	}
	if (pipes->total_commands == 1)
	{
		pipes->pipe_fds = NULL;
		return (0);
	}
	pipes->pipe_fds = malloc(sizeof(int *) * (pipes->total_commands - 1));
	if (!pipes->pipe_fds)
	{
		free(pipes->pids);
		g_exit_status = 1;
		pipes->pids = NULL;
		return (-1);
	}
	init_pipe_fds(pipes);
	return (0);
}

static void	init_pipe_fds(t_pipe *pipes)
{
	int	i;

	i = 0;
	while (i < (pipes->total_commands - 1))
	{
		pipes->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!pipes->pipe_fds[i])
		{
			free_partial_fds(pipes, i);
			g_exit_status = 1;
			return ;
		}
		pipes->pipe_fds[i][0] = -1;
		pipes->pipe_fds[i][1] = -1;
		i++;
	}
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		g_exit_status = 1;
		perror("minishell: pipeline creation failed ");
		return (-1);
	}
	return (0);
}

void	cleanup_pipeline(t_pipe *pipes)
{
	if (!pipes)
		return ;
	free_pipe_fds(pipes);
	if (pipes->pids)
	{
		free(pipes->pids);
		pipes->pids = NULL;
	}
	pipes->total_commands = 0;
}

static void	free_pipe_fds(t_pipe *pipes)
{
	int	i;

	if (!pipes->pipe_fds)
		return ;
	i = 0;
	while (i < (pipes->total_commands - 1))
	{
		if (pipes->pipe_fds[i])
		{
			if (pipes->pipe_fds[i][0] != -1)
			{
				close(pipes->pipe_fds[i][0]);
				pipes->pipe_fds[i][0] = -1;
			}
			if (pipes->pipe_fds[i][1] != -1)
			{
				close(pipes->pipe_fds[i][1]);
				pipes->pipe_fds[i][1] = -1;
			}
			free(pipes->pipe_fds[i]);
			pipes->pipe_fds[i] = NULL;
		}
		i++;
	}
	free(pipes->pipe_fds);
	pipes->pipe_fds = NULL;
}

static void	free_partial_fds(t_pipe *pipes, int max_index)
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
