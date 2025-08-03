/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 19:42:10 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				has_pipes(t_command *cmd);
int				execute_pipeline(t_command *cmd);
static pid_t	pipe_loop(t_command *cmd, t_pipe *pipes);
static int		exec_pip_cmd(t_command *cmd, t_pipe *pipes, int cmd_index);
static int		wait_all_processes(t_pipe *pipes);
static void		close_parent_pipes(t_pipe *pipes, int current_index);
static int		handle_pipe_error(t_pipe *pipes);

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

static pid_t	pipe_loop(t_command *cmd, t_pipe *pipes)
{
	pid_t		pid;
	t_command	*current;
	int			i;

	current = cmd;
	i = 0;
	while (current && i < pipes->total_commands)
	{
		if (i < (pipes->total_commands - 1))
		{
			if (create_pipe(pipes->pipe_fds[i]) == -1)
				return (handle_pipe_error(pipes));
		}
		pid = exec_pip_cmd(current, pipes, i);
		if (pid == -1)
			return (handle_pipe_error(pipes));
		pipes->pids[i] = pid;
		close_parent_pipes(pipes, i);
		current = current->next;
		i++;
	}
	return (pipes->pids[pipes->total_commands - 1]);
}

static int	exec_pip_cmd(t_command *cmd, t_pipe *pipes, int cmd_index)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: error with fork ");
		g_exit_status = 1;
		return (-1);
	}
	else if (pid == 0)
	{
		setup_child_pipes(pipes, cmd_index);
		if (setup_redirections(cmd) != 0)
			exit(1);
		execute_child_command(cmd);
	}
	else
		pipes->pids[cmd_index] = pid;
	return (pid);
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

static void	close_parent_pipes(t_pipe *pipes, int current_index)
{
	if (current_index > 0 && pipes->pipe_fds[current_index - 1])
	{
		if (pipes->pipe_fds[current_index - 1][0] != -1)
		{
			close(pipes->pipe_fds[current_index - 1][0]);
			pipes->pipe_fds[current_index - 1][0] = -1;
		}
		if (pipes->pipe_fds[current_index - 1][1] != -1)
		{
			close(pipes->pipe_fds[current_index - 1][1]);
			pipes->pipe_fds[current_index - 1][1] = -1;
		}
	}
	if (current_index < (pipes->total_commands - 1)
		&& pipes->pipe_fds[current_index])
	{
		if (pipes->pipe_fds[current_index][1] != -1)
		{
			close(pipes->pipe_fds[current_index][1]);
			pipes->pipe_fds[current_index][1] = -1;
		}
	}
}

static int	handle_pipe_error(t_pipe *pipes)
{
	g_exit_status = 1;
	cleanup_pipeline(pipes);
	return (-1);
}
