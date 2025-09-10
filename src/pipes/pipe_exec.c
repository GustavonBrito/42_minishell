/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:07:04 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/05 16:07:06 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		pipe_loop(t_command *cmd, t_pipe *pipes);
static int	exec_pip_cmd(t_command *cmd, t_pipe *pipes, int cmd_index);
void		execute_child_command(t_command *cmd);
static void	close_parent_pipes(t_pipe *pipes, int current_index);
static int	handle_builtin_in_pipe(t_command *cmd);

pid_t	pipe_loop(t_command *cmd, t_pipe *pipes)
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
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		flush_rsc_minishell(env, cmd, -1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: error with fork ");
		g_exit_status = 1;
		flush_rsc_minishell(env, cmd, -1);
	}
	else if (pid == 0)
	{
		setup_child_pipes(pipes, cmd_index);
		if (setup_redirections(cmd) != 0)
			flush_rsc_minishell(env, cmd, 1);
		execute_child_command(cmd);
	}
	else
		pipes->pids[cmd_index] = pid;
	return (pid);
}

void	execute_child_command(t_command *cmd)
{
	int		exit_code;
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd || !cmd->args || !cmd->args[0])
		flush_rsc_minishell(env, cmd, 127);
	if (check_builtin(cmd))
	{
		exit_code = handle_builtin_in_pipe(cmd);
		flush_rsc_minishell(env, cmd, exit_code);
	}
	exit_code = run_external(cmd);
	flush_rsc_minishell(env, cmd, exit_code);
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

static int	handle_builtin_in_pipe(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (127);
	}
	is_builtin(cmd);
	return (g_exit_status);
}
