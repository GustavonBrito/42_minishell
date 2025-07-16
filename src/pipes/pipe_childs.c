/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:04 by luiza             #+#    #+#             */
/*   Updated: 2025/07/05 16:11:26 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		setup_child_pipes(t_pipe *pipes);
void		execute_child_command(t_command *cmd);

/**
 * @brief Configura pipes no processo filho
 *
 * @param pipes Estrutura de controle de pipes
 */
void	setup_child_pipes(t_pipe *pipes)
{
	if (pipes->prev_pipe_read != -1)
	{
		dup2(pipes->prev_pipe_read, STDIN_FILENO);
		close(pipes->prev_pipe_read);
	}
	if (pipes->cmd_index < pipes->total_commands - 1)
	{
		dup2(pipes->curr_pipe[1], STDOUT_FILENO);
		close(pipes->curr_pipe[1]);
		close(pipes->curr_pipe[0]);
	}
}

/**
 * @brief Executa comando no processo filho
 *
 * @param cmd Comando a ser executado
 */
void	execute_child_command(t_command *cmd)
{
	char	**actual_env_var;
	t_env	*environ;
	t_env	*tmp;
	char	*cmd_path;
	int		env_length;
	int		i;		

	environ = *handle_t_env(NULL);
	tmp = environ;
	i = 0;
	while (environ)
	{
		env_length++;
		environ = environ->next;
	}
	actual_env_var = malloc(sizeof(char *) * (env_length + 1));
	while(tmp)
	{
		actual_env_var[i] = ft_strdup(tmp->env_data);
		tmp = tmp->next;
		i++;
	}
	actual_env_var[i] = NULL;
	if (check_builtin(cmd))
	{
		is_builtin(cmd);
		exit(g_exit_status);
	}
	else
	{
		cmd_path = find_command_path(cmd->args[0]);
		if (!cmd_path)
		{
			ft_printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		if (execve(cmd_path, cmd->args, actual_env_var) == -1)
		{
			ft_printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
	}
}
