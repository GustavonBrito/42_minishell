/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 05:16:57 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset(t_command *cmd);
static int	verify_remove_env(char **argv, t_env *s_env);
void		free_split(char **buffer);

void	unset(t_command *cmd)
{
	t_env	*first_node;
	t_env	*s_env;
	t_env	*tmp;
	t_env	*head;
	t_env	*last;

	s_env = *handle_t_env(NULL);
	first_node = s_env;
	head = NULL;
	last = NULL;
	tmp = NULL;
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
	free_env_list(first_node);
	handle_t_env(head);
}


static int	verify_remove_env(char **argv, t_env *s_env)
{
	char	**buffer;
	int		skip_flag;
	int		i;

	skip_flag = 0;
	i = 0;
	while (argv[i])
	{
		buffer = ft_split(s_env->env_data, '=');
		if (ft_strncmp(buffer[0], argv[i], ft_strlen(argv[i])) == 0 && argv[i]
		&& buffer[0][ft_strlen(argv[i])] == '\0')
		{
			skip_flag = 1;
			free_split(buffer);
			break ;
		}
		i++;
		free_split(buffer);
	}
	return (skip_flag);
}

void	free_split(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}
