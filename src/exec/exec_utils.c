/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:54:17 by luiza             #+#    #+#             */
/*   Updated: 2025/07/25 18:52:25 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			execute_with_execve(t_command *cmd);
static char	**convert_env_to_array(void);
static void	free_env_array(char **env_array);

int	execute_with_execve(t_command *cmd)
{
	char	**env_array;
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		exit(127);
	}
	env_array = convert_env_to_array();
	if (!env_array)
	{
		exit(1);
	}
	cmd_path = find_command_path(cmd->args[0]);
	if (!cmd_path)
	{
		free_env_array(env_array);
		exit(127);
	}
	execve(cmd_path, cmd->args, env_array);
	perror("execve");
	free_env_array(env_array);
	free(cmd_path);
	exit(127);
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
