/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:54:17 by luiza             #+#    #+#             */
/*   Updated: 2025/09/18 19:22:22 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**convert_env_to_array(void);
static t_env	*get_environment(void);
static int		count_env_vars(t_env *environ);
static char		**allocate_env_array(int env_length);
static char		**fill_env(char **env_array, t_env *environ, int env_length);

char	**convert_env_to_array(void)
{
	char	**env_array;
	t_env	*environ;
	int		env_length;

	environ = get_environment();
	if (!environ)
		return (NULL);
	env_length = count_env_vars(environ);
	env_array = allocate_env_array(env_length);
	if (!env_array)
		return (NULL);
	return (fill_env(env_array, environ, env_length));
}

static t_env	*get_environment(void)
{
	t_env	*environ;

	environ = *handle_t_env(NULL);
	if (!environ)
		(*handle_exit_status())->exit_status = 1;
	return (environ);
}

static int	count_env_vars(t_env *environ)
{
	t_env	*tmp;
	int		count;

	tmp = environ;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	**allocate_env_array(int env_length)
{
	char	**env_array;

	env_array = malloc(sizeof(char *) * (env_length + 1));
	if (!env_array)
		(*handle_exit_status())->exit_status = 1;
	return (env_array);
}

static char	**fill_env(char **env_array, t_env *environ, int env_length)
{
	t_env	*tmp;
	int		i;

	tmp = environ;
	i = 0;
	while (tmp && i < env_length)
	{
		env_array[i] = ft_strdup(tmp->env_data);
		if (!env_array[i])
			return (cleanup_failed_env_array(env_array, i));
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
