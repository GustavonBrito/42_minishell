/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:38:15 by luiza             #+#    #+#             */
/*   Updated: 2025/06/15 00:30:04 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_command(t_command *cmd);
int		execute_builtin_with_redirections(t_command *cmd);
int		execute_external_command(t_command *cmd);
void	handle_command_execution(t_command *cmd);
int		is_builtin_command(char *cmd);

int	execute_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_result;
	int	exec_result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_result = setup_redirections(cmd);
	if (redir_result != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (redir_result);
	}
	if (is_builtin_command(cmd->args[0]))
		exec_result = execute_builtin_with_redirections(cmd);
	else
		exec_result = execute_external_command(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (exec_result);
}

int	execute_builtin_with_redirections(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	is_builtin(cmd->args);
	return (0);
}

int	execute_external_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execvp(cmd->args[0], cmd->args) == -1)
		{
			ft_printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (0);
}

void	handle_command_execution(t_command *cmd)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		g_exit_status = execute_command(current);
		current = current->next;
		// TODO: implement pipes
	}
}

int	is_builtin_command(char *cmd)
{
	char *trimmed;
	int   result;

	trimmed = ft_strtrim(cmd, " ");
	if (!trimmed)
		return (0);

	result = (ft_strncmp(trimmed, "echo", 4) == 0 && (trimmed[4] == ' ' || trimmed[4] == '\0'))
		|| (ft_strncmp(trimmed, "cd", 2) == 0 && (trimmed[2] == ' ' || trimmed[2] == '\0'))
		|| (ft_strncmp(trimmed, "pwd", 3) == 0 && (trimmed[3] == ' ' || trimmed[3] == '\0'))
		|| (ft_strncmp(trimmed, "export", 6) == 0 && (trimmed[6] == ' ' || trimmed[6] == '\0'))
		|| (ft_strncmp(trimmed, "unset", 5) == 0 && (trimmed[5] == ' ' || trimmed[5] == '\0'))
		|| (ft_strncmp(trimmed, "env", 3) == 0 && (trimmed[3] == ' ' || trimmed[3] == '\0'))
		|| (ft_strncmp(trimmed, "exit", 4) == 0 && (trimmed[4] == ' ' || trimmed[4] == '\0'));

	free(trimmed);
	return (result);
}
