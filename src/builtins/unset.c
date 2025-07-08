/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/07 23:25:43 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementa o comando 'unset'.
 *
 * Esta função remove variáveis de ambiente do ambiente atual do shell.
 * Percorre a lista de argumentos e para cada um, tenta remover a variável
 * de ambiente correspondente usando `unsetenv`.
 *
 * @param argv Um array de strings, onde argv é "unset" e os elementos
 *             subsequentes são os nomes das variáveis de ambiente a serem removidas.
 */
void	unset(char **argv)
{
	t_env	*tmp;
	t_env	*env;
	t_env	*new_env;
	//int	i;
	int	flag_var_already_exists;

	//i = 1;
	flag_var_already_exists = 0;
	env = get_t_env();
	tmp = env;
	new_env = env;
	while(env)
	{
		if (ft_strncmp(env->env_data, argv[1], ft_strlen(argv[1])) == 0)
		{
			flag_var_already_exists	= 1;
			return;
		}
		env = env->next;
	}
	if (flag_var_already_exists == 1)
	{
		while(tmp)
		{
			if (ft_strncmp(tmp->env_data, argv[1], ft_strlen(argv[1])) != 0)
			{
				ft_printf("entrei\n");
				new_env->env_data = ft_strdup(tmp->env_data);
				new_env->next = malloc(sizeof(t_env));
			}
			tmp = tmp->next;
		}
	}
}
