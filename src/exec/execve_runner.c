/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_runner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:06:54 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/12 11:22:52 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			run_external(t_command *cmd);
static char	*get_executable_path(t_command *cmd, char **env_array);
static int	is_empty_command(char *command);
static void	run_execve(t_command *cmd, char *cmd_path, char **env_array);
static char	**get_args_for_execution(t_command *cmd);

int	run_external(t_command *cmd)
{
	char	**env_array;
	char	*cmd_path;
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd || !cmd->args || !cmd->args[0])
		flush_rsc_minishell(env, cmd, 127);
	env_array = convert_env_to_array();
	if (!env_array)
		flush_rsc_minishell(env, cmd, 1);
	cmd_path = get_executable_path(cmd, env_array);
	run_execve(cmd, cmd_path, env_array);
	cleanup_n_exit(env_array, cmd_path);
	return (0);
}

static char	*get_executable_path(t_command *cmd, char **env_array)
{
	if (is_empty_command(cmd->args[0]) && cmd->args[1] == NULL)
	{
		free_env_array(env_array);
		close_dup_fds((*handle_t_env(NULL))->fd_stdin, (*handle_t_env(NULL))->fd_stdout);
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

static void	run_execve(t_command *cmd, char *cmd_path, char **env_array)
{
	char	**args_to_use;
	t_env	*env;

	env = (*handle_t_env(NULL));
	if (!cmd_path && !is_empty_command(cmd->args[0]))
	{
		free_env_array(env_array);
		write(2, "minishell: command not found\n", 29);
		close_dup_fds(env->fd_stdin, env->fd_stdout);
		flush_rsc_minishell(env, cmd, 127);
	}
	args_to_use = get_args_for_execution(cmd);
	execve(cmd_path, args_to_use, env_array);
	perror("minishell: ");
	free_env_array(env_array);
	close_dup_fds(env->fd_stdin, env->fd_stdout);
	flush_rsc_minishell(env, cmd, 126);
}

static char	**get_args_for_execution(t_command *cmd)
{
	if (is_empty_command(cmd->args[0]))
		return (&cmd->args[1]);
	return (cmd->args);
}
