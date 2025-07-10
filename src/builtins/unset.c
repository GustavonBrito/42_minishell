/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/09 23:18:13 by gustavo-lin      ###   ########.fr       */
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
	//t_env	*tmp;
	t_env	*env;
	t_env	*new_env;
	t_env	*head;
	t_env	*tmp;	
	int	i;
	int skip;
	//int	flag_var_already_exists;

	//flag_var_already_exists = 0;
	env = get_t_env();
	//tmp = env;
	new_env = NULL;
	head = NULL;
	skip = 0;
	//head = malloc(sizeof(t_env));
	while(env)
	{
		i = 1;
		while (argv[i])
		{
			if (ft_strncmp(env->env_data, argv[i], ft_strlen(argv[i])) == 0 && argv[i])
			{
				skip = 1;
				break;
			}
			i++;
		}
		new_env = malloc(sizeof(t_env));
		new_env->env_data = ft_strdup(env->env_data);
		new_env->next = NULL;
		if (!head)
			head = new_env;
		env = env->next;
		new_env = new_env->next;
	}
	env = head;
}
