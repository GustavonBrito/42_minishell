/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:07:14 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/16 21:58:01 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		allocate_pids_array(t_pipe *pipes);
int		allocate_pipe_fds_array(t_pipe *pipes);
void	close_pipe_fd(int *fd);
int		wait_single_process(t_pipe *pipes, int index);
int		get_exit_status_from_wait(int status);

int	allocate_pids_array(t_pipe *pipes)
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
	return (0);
}

int	allocate_pipe_fds_array(t_pipe *pipes)
{
	pipes->pipe_fds = malloc(sizeof(int *) * (pipes->total_commands - 1));
	if (!pipes->pipe_fds)
	{
		free(pipes->pids);
		pipes->pids = NULL;
		g_exit_status = 1;
		return (-1);
	}
	init_pipe_fds(pipes);
	return (0);
}

void	close_pipe_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	wait_single_process(t_pipe *pipes, int index)
{
	int	status;
	int	exit_status;

	waitpid(pipes->pids[index], &status, 0);
	exit_status = get_exit_status_from_wait(status);
	if (index == (pipes->total_commands - 1))
		return (exit_status);
	return (0);
}

int	get_exit_status_from_wait(int status)
{
	(*handle_t_env(NULL))->pipe_mode = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WIFEXITED(status))
		{
			(*(handle_t_env(NULL)))->cat_flag = 0;
			return (WEXITSTATUS(status));
		}
		if (WTERMSIG(status) == SIGQUIT && (*(handle_t_env(NULL)))->cat_flag == 1)
		{
			write(2, "Quit (core dumped)\n", 20);
			(*(handle_t_env(NULL)))->cat_flag = 0;
		}
		return (128 + WTERMSIG(status));
	}
	return (0);
}
