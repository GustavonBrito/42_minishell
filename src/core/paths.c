/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/07/29 21:10:01 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(void);
char	*find_command_path(char *command);
void	free_array(char **path_dirs);

void	update_pwd(void)
{
	t_command	*cmd;
	char		*new_dir;
	char		*actual_directory;

	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	cmd = init_command();
	if (!cmd || !allocate_command_arrays(cmd, 1))
	{
		free(actual_directory);
		if (cmd)
			free(cmd);
		return ;
	}
	new_dir = ft_strjoin("PWD=",actual_directory);
	if (!new_dir)
	{
		free(actual_directory);
		free_commands(cmd);
		return ;
	}
	cmd->args[1] = ft_strdup(new_dir);
	if (cmd->args[1])
		export(cmd);
	free(actual_directory);
	free(new_dir);
	free_commands(cmd);
}

char	*find_command_path(char *command)
{
	char	*path_env;
	char	**path_dirs;
	char	*full_path;
	char	*temp_path;
	int		i;

	if (!command || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (ft_strdup(command));
			return (ft_strdup(command));
		}
		return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = -1;
	while (path_dirs[++i])
	{
		if (path_dirs[i][0] == '\0')
			continue ;
		temp_path = ft_strjoin(path_dirs[i], "/");
		if (!temp_path)
		{
			free_array(path_dirs);
			return (NULL);
		}
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (!full_path)
		{
			free_array(path_dirs);
			return (NULL);
		}
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free_array(path_dirs);
			return (full_path);
		}
		free(full_path);
	}
	free_array(path_dirs);
	return (NULL);
}

void	free_array(char **path_dirs)
{
	int	i;

	i = -1;
	while (path_dirs[++i])
		free(path_dirs[i]);
	free(path_dirs);
}
