/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:09:14 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/08/04 00:19:52 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handle_store_env(char **system_env);
static t_env	*create_env_node(char *env_data);
t_env			**handle_t_env(t_env *head);
void			free_env_list(t_env *head);
void			ft_free_split(char **array);

void	handle_store_env(char **system_env)
{
	int		i;
	t_env	*head;
	t_env	*env_struct;

	if (!system_env || !system_env[0])
		return ;
	head = create_env_node(system_env[0]);
	if (!head)
		return ;
	*handle_t_env(head) = head;
	env_struct = head;
	i = 0;
	while (system_env[++i])
	{
		env_struct->next = create_env_node(system_env[i]);
		if (!env_struct->next)
		{
			free_env_list(head);
			return ;
		}
		env_struct = env_struct->next;
	}
}

static t_env	*create_env_node(char *env_data)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(new_node);
		return (NULL);
	}
	new_node->env_data = ft_strdup(env_data);
	if (!new_node->env_data)
	{
		free(new_node);
		return (NULL); 
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	**handle_t_env(t_env *head)
{
	static t_env	*env;

	if (head != NULL)
		env = head;
	return (&env);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;
	t_env	*next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->env_data);
		free(tmp);
		tmp = next;
	}
}

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
