/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:20:01 by gserafio          #+#    #+#             */
/*   Updated: 2025/09/18 11:25:51 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_filtered_list(t_command *cmd, t_env *s_env);

t_env	*create_filtered_list(t_command *cmd, t_env *s_env)
{
	t_env	*head;
	t_env	*last;
	t_env	*tmp;

	head = NULL;
	last = NULL;
	while (s_env)
	{
		if (!verify_remove_env(cmd->args, s_env))
		{
			tmp = malloc(sizeof(t_env));
			if (!tmp)
				break ;
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
	return (head);
}
