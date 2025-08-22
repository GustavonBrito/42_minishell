/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:08 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 20:22:43 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			init_pipeline(t_pipe *pipes, t_command *cmd);
static int	init_pipe_arrays(t_pipe *pipes);
void		init_pipe_fds(t_pipe *pipes);
int			create_pipe(int pipe_fd[2]);
void		cleanup_pipeline(t_pipe *pipes);

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

static int	init_pipe_arrays(t_pipe *pipes)
{
	if (allocate_pids_array(pipes) != 0)
		return (-1);
	if (pipes->total_commands == 1)
	{
		pipes->pipe_fds = NULL;
		return (0);
	}
	return (allocate_pipe_fds_array(pipes));
}

void	init_pipe_fds(t_pipe *pipes)
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
