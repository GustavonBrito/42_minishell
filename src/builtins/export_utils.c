/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 20:54:18 by luiza            ###   ########.fr       */
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
	int	j;
	int	equal_passed;
	int	first_passed;

	j = 0;
	equal_passed = 0;
	first_passed = 0;
	while (arg[j] && equal_passed == 0)
	{
		if (ft_isalnum(arg[j]) == 4 && first_passed == 0)
			return (0);
		if (arg[j] == '=')
			equal_passed = 1;
		if (ft_isalnum(arg[j]) == 0 && (arg[j] != '=' || arg[j + 1] == '\0'))
			return (0);
		j++;
		first_passed = 1;
	}
	return (1);
}

t_env	*find_env_var(char *var_name)
{
	t_env	*s_env;
	int		len;

	s_env = *handle_t_env(NULL);
	len = ft_strlen(var_name);
	while (s_env)
	{
		if (ft_strncmp(s_env->env_data, var_name, len) == 0
			&& s_env->env_data[len] == '=')
			return (s_env);
		if (!s_env->next)
			break ;
		s_env = s_env->next;
	}
	return (s_env);
}

void	update_env_var(t_env *env, char *var_name, char *value)
{
	free(env->env_data);
	env->env_data = ft_strdup(var_name);
	env->env_data = ft_strjoin_free(env->env_data, "=");
	env->env_data = ft_strjoin_free(env->env_data, value);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	create_new_var(t_env *last_env, char *var_name, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	new_var->env_data = ft_strdup(var_name);
	new_var->env_data = ft_strjoin_free(new_var->env_data, "=");
	new_var->env_data = ft_strjoin_free(new_var->env_data, value);
	new_var->next = NULL;
	if (last_env)
		last_env->next = new_var;
	else
		handle_t_env(new_var);
}
