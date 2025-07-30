/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:31 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/30 17:03:31 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void);

/**
 * @brief Implementa o comando 'pwd'.
 *
 * Esta função imprime o diretório de trabalho atual para a saída padrão.
 * Obtém o diretório diretamente da variável de ambiente "PWD".
 */
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
