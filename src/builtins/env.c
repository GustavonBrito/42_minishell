/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 20:27:42 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(int is_export);
void	print_export(void);

void	env(int is_export)
{
	t_env	**env_ptr;
	t_env	*env;

	if (is_export == 1)
		print_export();
	else
	{
		env_ptr = handle_t_env(NULL);
		env = *env_ptr;
		while (env)
		{
			ft_printf("%s\n", env->env_data);
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
		if (buffer[1] == NULL)
			ft_printf("declare -x %s\n", buffer[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
		ft_free_split(buffer);
		env = env->next;
	}
}
