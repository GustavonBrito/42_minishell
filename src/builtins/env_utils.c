/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:09:14 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/11 21:52:57 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_env	**handle_t_env(t_env *head)
{
	static t_env	*env;

	if (head != NULL)
		env = head;
	return (&env);
}

void	handle_store_env(char **system_env)
{
	int		i;
	t_env	*env_struct;
	t_env	*head;
	t_env	*tmp;
	t_env	*next;

	i = -1;
	head = malloc(sizeof(t_env));
	if (!head)
		return ;
	*handle_t_env(head) = head;
	env_struct = head;
	while (system_env[++i])
	{
		env_struct->env_data = ft_strdup(system_env[i]);
		if (!env_struct->env_data)
			return ;
		if (system_env[i + 1])
		{
			env_struct->next = malloc(sizeof(t_env));
			if (!env_struct->next)
			{
				tmp = head;
				while (tmp)
				{
					next = tmp->next;
					free(tmp->env_data);
					free(tmp);
					tmp = next;
				}
				return ;
			}
			env_struct = env_struct->next;
			env_struct->next = NULL;
		}
		else
			env_struct->next = NULL;
	}
}
