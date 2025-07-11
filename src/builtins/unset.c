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
	t_env	*s_env;
	t_env	*new_env;
	t_env	*head;
	t_env	*last;
	char	**buffer;
	int		i;
	int		skip;

	s_env = handle_t_env(NULL);
	head = NULL;
	last = NULL;
	
	while(s_env)
	{
		skip = 0;
		i = 1;
		while (argv[i])
		{
			//Verificar uma funcao na lib que filtra a palavra inteira para comparar com o argumento
			//buffer = ft_split(s_env->env_data, '=');

			if (ft_strncmp(buffer[0], argv[i], ft_strlen(buffer[0])) == 0 && argv[i])
			{
				printf("Test %s %s\n", s_env->env_data, argv[i]);
				skip = 1;
				break;
			}
			i++;
		}
		if (!skip)
		{
			new_env = malloc(sizeof(t_env));
			new_env->env_data = ft_strdup(s_env->env_data);
			new_env->next = NULL;
			
			if (!head)
				head = new_env;
			else
				last->next = new_env;
			
			last = new_env;
		}
		
		s_env = s_env->next;
	}
	handle_t_env(head);
}
