/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:38:15 by luiza             #+#    #+#             */
/*   Updated: 2025/07/30 17:22:54 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_command(t_command *cmd);
int		execute_builtin(t_command *cmd);
int		execute_external_command(t_command *cmd);
void	handle_command_execution(t_command *cmd);
int		check_builtin(t_command *cmd);

int	execute_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_result;
	int	exec_result;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (0);
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_result = setup_redirections(cmd);
	if (redir_result != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (redir_result);
	}
	if (check_builtin(cmd))
		exec_result = execute_builtin(cmd);
	else
		exec_result = execute_external_command(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (exec_result);
}

int	execute_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	is_builtin(cmd);
	return (g_exit_status);
}

int	execute_external_command(t_command *cmd)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork ");
		g_exit_status = 1;
		return (g_exit_status);
	}
	else if (pid == 0)
		exit(execute_with_execve(cmd));
	else
	{
		waitpid(pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			return (WEXITSTATUS(g_exit_status));
		else if (WIFSIGNALED(g_exit_status))
			return (128 + WTERMSIG(g_exit_status));
	}
	return (g_exit_status);
}

void	handle_command_execution(t_command *cmd)
{
	t_command	*current;
	int			result;

	if (!cmd)
	{
		g_exit_status = 1;
		return ;
	}
	current = cmd;
	if (has_pipes(current))
	{
		result = execute_pipeline(current);
		g_exit_status = result;
	}
	else
	{
		result = execute_command(current);
		g_exit_status = result;
	}
}

int	check_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (0);
	}
	if ((ft_strncmp(cmd->args[0], "echo", 4) == 0
			&& ft_strlen(cmd->args[0]) == 4)
		|| (ft_strncmp(cmd->args[0], "cd", 2) == 0
			&& ft_strlen(cmd->args[0]) == 2)
		|| (ft_strncmp(cmd->args[0], "pwd", 3) == 0
			&& ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "export", 6) == 0
			&& ft_strlen(cmd->args[0]) == 6)
		|| (ft_strncmp(cmd->args[0], "unset", 5) == 0
			&& ft_strlen(cmd->args[0]) == 5)
		|| (ft_strncmp(cmd->args[0], "env", 3) == 0
			&& ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "exit", 4) == 0
			&& ft_strlen(cmd->args[0]) == 4))
		return (1);
	else
		return (0);
}
