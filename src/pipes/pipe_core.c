/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 20:07:44 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				has_pipes(t_command *cmd);
int				execute_pipeline(t_command *cmd);
int				count_commands(t_command *cmd);
static int		wait_all_processes(t_pipe *pipes);
int				handle_pipe_error(t_pipe *pipes);

int	has_pipes(t_command *cmd)
{
	if (!cmd)
	{
		g_exit_status = 1;
		return (0);
	}
	return (cmd->next != NULL);
}

int	execute_pipeline(t_command *cmd)
{
	pid_t		last_pid;
	t_pipe		pipes;
	int			result;

	if (!cmd)
	{
		g_exit_status = 1;
		return (0);
	}
	if (!cmd->next)
		return (execute_command(cmd));
	if (init_pipeline(&pipes, cmd) != 0)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	last_pid = pipe_loop(cmd, &pipes);
	if (last_pid == -1)
	{
		cleanup_pipeline(&pipes);
		g_exit_status = 1;
		return (g_exit_status);
	}
	result = wait_all_processes(&pipes);
	return (result);
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

static int	wait_all_processes(t_pipe *pipes)
{
	int	status;
	int	i;
	int	exit_status;
	int	last_exit_status;

	i = 0;
	last_exit_status = 0;
	while (i < pipes->total_commands)
	{
		if (pipes->pids[i] != -1)
		{
			waitpid(pipes->pids[i], &status, 0);
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (i == (pipes->total_commands - 1))
					last_exit_status = exit_status;
			}
			else if (WIFSIGNALED(status))
			{
				exit_status = 128 + WTERMSIG(status);
				if (i == (pipes->total_commands - 1))
					last_exit_status = exit_status;
			}
		}
		i++;
	}
	g_exit_status = last_exit_status;
	cleanup_pipeline(pipes);
	return (g_exit_status);
}

int	handle_pipe_error(t_pipe *pipes)
{
	g_exit_status = 1;
	cleanup_pipeline(pipes);
	return (-1);
}
