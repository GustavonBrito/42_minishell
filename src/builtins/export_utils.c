/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 09:19:26 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		validate_identifier(char *arg);
t_env	*find_env_var(char *var_name);
void	update_env_var(t_env *env, char *var_name, char *value);
char	*ft_strjoin_free(char *s1, char *s2);
void	create_new_var(t_env *last_env, char *var_name, char *value);

int	validate_identifier(char *arg)
{
	int	equal_passed;
	int	first_passed;
	int	result;

	equal_passed = 0;
	first_passed = 0;
	if (arg[ft_strlen(arg) - 1] == '=' && arg[ft_strlen(arg)] == '\0'
		&& ft_isalnum(arg[0]) != 0)
		return (2);
	result = check_identifier_loop(arg, &equal_passed, &first_passed);
	if (result == 0)
		return (0);
	return (1);
}

t_env	*find_env_var(char *var_name)
{
	t_env	*s_env;
	char	**var_to_compare;
	char	**env_to_compare;

	var_to_compare = NULL;
	s_env = *handle_t_env(NULL);
	var_to_compare = ft_split(var_name, '=');
	while (s_env)
	{
		env_to_compare = ft_split(s_env->env_data, '=');
		if (ft_strcmp(var_to_compare[0], env_to_compare[0]) == 0)
		{
			ft_free_split(env_to_compare);
			ft_free_split(var_to_compare);
			return (s_env);
		}
		if (!s_env->next)
			break ;
		ft_free_split(env_to_compare);
		s_env = s_env->next;
	}
	ft_free_split(env_to_compare);
	ft_free_split(var_to_compare);
	return (s_env);
}

void	update_env_var(t_env *env, char *var_name, char *value)
{
	free(env->env_data);
	if (value != NULL)
	{
		env->env_data = ft_strdup(var_name);
		env->env_data = ft_strjoin_free(env->env_data, "=");
		env->env_data = ft_strjoin_free(env->env_data, value);
	}
	else
		env->env_data = ft_strdup(var_name);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (joined == ((void *)0))
	{
		free(s1);
		return (((void *)0));
	}
	free(s1);
	return (joined);
}

void	create_new_var(t_env *last_env, char *var_name, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (value != NULL)
	{
		new_var->env_data = ft_strdup(var_name);
		new_var->env_data = ft_strjoin_free(new_var->env_data, "=");
		new_var->env_data = ft_strjoin_free(new_var->env_data, value);
	}
	else
		new_var->env_data = ft_strdup(var_name);
	new_var->export_organize_flag = 0;
	new_var->next = NULL;
	if (last_env)
		last_env->next = new_var;
	else
		handle_t_env(new_var);
}
