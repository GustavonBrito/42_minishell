/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/07/30 17:12:34 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*find_command_path(char *command);
static char	*check_absolute_path(char *command);
static char	*build_full_path(char *dir, char *command);
static char	*search_in_path_dirs(char **path_dirs, char *command);
static void	free_array(char **path_dirs);

char	*find_command_path(char *command)
{
	char	*path_env;
	char	**path_dirs;
	char	*full_path;

	if (!command || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
		return (check_absolute_path(command));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	full_path = search_in_path_dirs(path_dirs, command);
	free_array(path_dirs);
	return (full_path);
}

static char	*check_absolute_path(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (ft_strdup(command));
	}
	return (NULL);
}

static char	*build_full_path(char *dir, char *command)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(dir, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin(temp_path, command);
	free(temp_path);
	return (full_path);
}

static char	*search_in_path_dirs(char **path_dirs, char *command)
{
	char	*full_path;
	int		i;

	i = -1;
	while (path_dirs[++i])
	{
		if (path_dirs[i][0] == '\0')
			continue ;
		full_path = build_full_path(path_dirs[i], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static void	free_array(char **path_dirs)
{
	int	i;

	i = -1;
	while (path_dirs[++i])
		free(path_dirs[i]);
	free(path_dirs);
}
