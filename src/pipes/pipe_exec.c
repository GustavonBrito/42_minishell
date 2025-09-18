/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:07:04 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/18 05:29:32 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		pipe_loop(t_command *cmd, t_pipe *pipes);
static int	exec_pip_cmd(t_command *cmd_crr, t_pipe *pipes, int cmd_index,
				t_command *cmd);
void		execute_child_command(t_command *cmd_crr, t_command *cmd);
static void	close_parent_pipes(t_pipe *pipes, int current_index);
static int	handle_builtin_in_pipe(t_command *cmd);

pid_t	pipe_loop(t_command *cmd, t_pipe *pipes)
{
	pid_t		pid;
	int			i;
	t_command	*first_cmd;

	(*handle_pipe_mode())->pipe_mode = 1;
	first_cmd = cmd;
	i = 0;
	while (cmd && i < pipes->total_commands)
	{
		if (i < (pipes->total_commands - 1))
		{
			if (create_pipe(pipes->pipe_fds[i]) == -1)
				return (handle_pipe_error(pipes));
		}
		pid = exec_pip_cmd(cmd, pipes, i, first_cmd);
		if (pid == -1)
			return (handle_pipe_error(pipes));
		pipes->pids[i] = pid;
		close_parent_pipes(pipes, i);
		cmd = cmd->next;
		i++;
	}
	return (pipes->pids[pipes->total_commands - 1]);
}

static int	exec_pip_cmd(t_command *cmd_crr, t_pipe *pipes, int cmd_index,
				t_command *first_cmd)
{
	pid_t	pid;
	t_env	*env;

	if (validate_pre_fork(cmd_crr, first_cmd) == -1)
		return (-1);
	env = (*handle_t_env(NULL));
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: error with fork ");
		g_exit_status = 1;
		flush_rsc_minishell(env, cmd_crr, -1);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		setup_child_pipes(pipes, cmd_index);
		if (setup_redirections(cmd_crr) != 0)
			flush_rsc_minishell(env, first_cmd, 1);
		execute_child_command(cmd_crr, first_cmd);
	}
	else
		pipes->pids[cmd_index] = pid;
	return (pid);
}

void	execute_child_command(t_command *cmd_crr, t_command *first_cmd)
{
	int		exit_code;
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd_crr || !cmd_crr->args || !cmd_crr->args[0])
		flush_rsc_minishell(env, first_cmd, 127);
	if (check_builtin(cmd_crr))
	{
		exit_code = handle_builtin_in_pipe(cmd_crr);
		flush_rsc_minishell(env, first_cmd, exit_code);
	}
	exit_code = run_external(cmd_crr, first_cmd);
	flush_rsc_minishell(env, first_cmd, exit_code);
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
