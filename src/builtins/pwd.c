/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/30 22:48:11 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	t_env	*env;

	env = *handle_t_env(NULL);
	while (env)
	{
		if (ft_strncmp(env->env_data, "PWD", 3) == 0)
			ft_printf("%s\n", ft_strchr(env->env_data, '/'));
		env = env->next;
	}
}
