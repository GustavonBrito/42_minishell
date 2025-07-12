/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/11 22:02:35 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_command *cmd);

/**
 * @brief Implementa o comando 'unset'.
 *
 * Esta função remove variáveis de ambiente do ambiente atual do shell.
 * Percorre a estrutura `t_command`, e para cada um, tenta remover a variável
 * de ambiente correspondente usando `unsetenv`.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando 'unset'.
 */
void	unset(t_command *cmd)
{
	t_env	*s_env;
	t_env	*new_env;
	t_env	*head;
	t_env	*last;

	s_env = *handle_t_env(NULL);
	head = NULL;
	last = NULL;
	while (s_env)
	{
		if (!verify_remove_env(cmd->args, s_env))
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
