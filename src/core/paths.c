/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/09/13 10:09:50 by gustavo          ###   ########.fr       */
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
	t_env	*env;
	char	*path_env;
	char	**path_dirs;
	char	*full_path;

	path_env = NULL;
	env = *handle_t_env(NULL);
	if (!command || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
		return (check_absolute_path(command));
	while (env)
	{
		if (ft_strncmp(env->env_data, "PATH", 4) == 0)
			path_env = env->env_data;
		env = env->next;
	}
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
	struct stat st;
	if (access(command, F_OK) == 0)
	{
		if (stat(command, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				g_exit_status = 126;
				return (NULL);
			}
		}
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
