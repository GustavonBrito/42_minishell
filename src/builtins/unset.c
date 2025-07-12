/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/11 17:58:23 by gustavo-lin      ###   ########.fr       */
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

	*subsequentes são os nomes das variáveis de ambiente a serem removidas.
 */
void	unset(char **argv)
{
	t_env	*s_env;
	t_env	*tmp;
	t_env	*head;
	t_env	*last;

	s_env = handle_t_env(NULL);
	head = NULL;
	last = NULL;
	while (s_env)
	{
		if (!verify_remove_env(argv, s_env))
		{
			tmp = malloc(sizeof(t_env));
			tmp->env_data = ft_strdup(s_env->env_data);
			tmp->next = NULL;
			if (!head)
				head = tmp;
			else
				last->next = tmp;
			last = tmp;
		}
		s_env = s_env->next;
	}
	handle_t_env(head);
}
