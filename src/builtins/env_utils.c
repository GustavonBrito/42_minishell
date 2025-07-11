/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:09:14 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/06 23:46:08 by gustavo-lin      ###   ########.fr       */
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

void	*handle_t_env(t_env *head)
{
	static t_env	env;

	(void)head;
	if (head != NULL)
	{
		env = *head;
		return NULL;
	}
	else
		return (&env);
}

void	handle_store_env(char **system_env)
{
	int		i;
	t_env	*env_struct;
	t_env	*head;
	t_env	*tmp;

	i = -1;
	env_struct = handle_t_env(NULL);
	head = NULL;
	while (system_env[++i])
	{
		env_struct->env_data = ft_strdup(system_env[i]);
		if (!env_struct->env_data)
		{
			return ;
		}
		if (system_env[i + 1])
		{
			env_struct->next = malloc(sizeof(t_env));
			if (!env_struct->next)
			{
				while (head)
				{
					tmp = head->next;
					free(head->env_data);
					free(head);
					head = tmp;
				}
			}
			env_struct = env_struct->next;
			env_struct->next = NULL;
		}
		else
		{
			env_struct->next = NULL;
		}
	}
}
