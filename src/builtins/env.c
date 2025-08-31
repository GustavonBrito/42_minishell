/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/08/30 23:07:02 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(int is_export);
void	print_export(void);

void	env(int is_export)
{
	t_env	**env_ptr;
	t_env	*env;
	int		i;

	if (is_export == 1)
		print_export();
	else
	{
		env_ptr = handle_t_env(NULL);
		env = *env_ptr;
		while (env)
		{
			i = 0;
			while (env->env_data[i])
			{
				if(env->env_data[i] == '=')
				{
					ft_printf("%s\n", env->env_data);
					break;
				}
				i++;
			}
			env = env->next;
		}
	}
}

void	print_export(void)
{
	t_env		*env;
	char		**buffer;

	env = *handle_t_env(NULL);
	while (env)
	{
		buffer = ft_split(env->env_data, '=');
		if (ft_strnstr(env->env_data, "=", ft_strlen(env->env_data)) == 0)
			ft_printf("declare -x %s\n", buffer[0]);
		else if (buffer[1] == NULL)
			ft_printf("declare -x %s=\"\"\n", buffer[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
		ft_free_split(buffer);
		env = env->next;
	}
}
