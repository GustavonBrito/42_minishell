/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:54:17 by luiza             #+#    #+#             */
/*   Updated: 2025/07/28 22:25:55 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			execute_with_execve(t_command *cmd);
static char	**convert_env_to_array(void);
static void	free_env_array(char **env_array);

void write_on_stderr(char *err_message)
{
	int i;

	i = 0;
	while (err_message[i])
	{
		write(2, &err_message[i], 1);
		i++;
	}
}

int	execute_with_execve(t_command *cmd)
{
	char	**env_array;
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	env_array = convert_env_to_array();
	if (!env_array)
		exit(1);
	cmd_path = find_command_path(cmd->args[0]);
	if (ft_strncmp(cmd->args[0], "", 1) == 0 && cmd->args[1] == NULL)
		exit(0);
	else if(!cmd_path && ft_strncmp(cmd->args[0], "", 1) != 0)
	{
		free_env_array(env_array);
		perror(" ");
		//write_on_stderr(cmd->args[0]);
		//write(2, " command not found\n", 20);
		exit(127);
	}
	else if(ft_strncmp(cmd->args[0], "", 1) == 0)
	{
		cmd_path = find_command_path(cmd->args[1]);
		execve(cmd_path, &cmd->args[1], env_array);
	}
	if (execve(cmd_path, cmd->args, env_array) == -1)
	{
		perror(" ");
	}
	free_env_array(env_array);
	free(cmd_path);
	exit(126);
}

static char	**convert_env_to_array(void)
{
	char	**env_array;
	t_env	*environ;
	t_env	*tmp;
	int		env_length;
	int		i;

	environ = *handle_t_env(NULL);
	if (!environ)
	{
		g_exit_status = 1;
		return (NULL);
	}
	tmp = environ;
	env_length = 0;
	while (tmp)
	{
		env_length++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (env_length + 1));
	if (!env_array)
	{
		g_exit_status = 1;
		return (NULL);
	}
	tmp = environ;
	i = 0;
	while (tmp && i < env_length)
	{
		env_array[i] = ft_strdup(tmp->env_data);
		if (!env_array[i])
		{
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

static void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
