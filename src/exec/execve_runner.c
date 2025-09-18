/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_runner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:06:54 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/18 07:36:02 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			run_external(t_command *cmd, t_command *first_cmd);
static char	*get_executable_path(t_command *cmd, char **env_array,
				t_command *first_cmd);
static int	is_empty_command(char *command);
static void	run_execve(t_command *cmd, char *cmd_path, char **env_array,
				t_command *first_cmd);
static char	**get_args_for_execution(t_command *cmd);

int	run_external(t_command *cmd, t_command *first_cmd)
{
	char	**env_array;
	char	*cmd_path;
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		if ((*handle_pipe_mode())->pipe_mode == 1)
			flush_rsc_minishell(env, first_cmd, 127);
		flush_rsc_minishell(env, cmd, 127);
	}
	env_array = convert_env_to_array();
	if (!env_array)
	{
		if ((*handle_pipe_mode())->pipe_mode == 1)
			flush_rsc_minishell(env, first_cmd, 1);
		flush_rsc_minishell(env, cmd, 1);
	}
	cmd_path = get_executable_path(cmd, env_array, first_cmd);
	run_execve(cmd, cmd_path, env_array, first_cmd);
	cleanup_n_exit(env_array, cmd_path);
	return (0);
}

static char	*get_executable_path(t_command *cmd, char **env_array,
				t_command *first_cmd)
{
	if (is_empty_command(cmd->args[0]) && cmd->args[1] == NULL)
	{
		free_env_array(env_array);
		close_dup_fds((*handle_t_env(NULL))->fd_stdin,
			(*handle_t_env(NULL))->fd_stdout);
		if ((*handle_pipe_mode())->pipe_mode == 1)
			flush_rsc_minishell(*(handle_t_env(NULL)), first_cmd, 0);
		flush_rsc_minishell(*(handle_t_env(NULL)), cmd, 0);
		exit(0);
	}
	if (is_empty_command(cmd->args[0]))
		return (find_command_path(cmd->args[1]));
	return (find_command_path(cmd->args[0]));
}

static int	is_empty_command(char *command)
{
	return (ft_strncmp(command, "", 1) == 0);
}

static void	run_execve(t_command *cmd, char *cmd_path, char **env_array,
				t_command *first_cmd)
{
	char	**args_to_use;
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd_path && !is_empty_command(cmd->args[0]))
	{
		if (g_exit_status == 0)
			g_exit_status = 127;
		free_env_array(env_array);
		write_err("minishell: command not found\n");
		close_dup_fds(env->fd_stdin, env->fd_stdout);
		if ((*handle_pipe_mode())->pipe_mode == 1)
			flush_rsc_minishell(env, first_cmd, g_exit_status);
		flush_rsc_minishell(env, cmd, g_exit_status);
	}
	args_to_use = get_args_for_execution(cmd);
	execve(cmd_path, args_to_use, env_array);
	perror("minishell: ");
	free_env_array(env_array);
	close_dup_fds(env->fd_stdin, env->fd_stdout);
	if ((*handle_pipe_mode())->pipe_mode == 1)
		flush_rsc_minishell(env, first_cmd, 126);
	flush_rsc_minishell(env, cmd, 126);
}

static char	**get_args_for_execution(t_command *cmd)
{
	if (is_empty_command(cmd->args[0]))
		return (&cmd->args[1]);
	return (cmd->args);
}
