/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/17 23:18:50 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*process_unset_loop(t_command *cmd, t_env *s_env, t_env **last);
void		unset(t_command *cmd);
static int	verify_remove_env(char **argv, t_env *s_env);

t_env	*process_unset_loop(t_command *cmd, t_env *s_env, t_env **last)
{
	t_env	*head;
	t_env	*tmp;

	head = NULL;
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
				(*last)->next = tmp;
			*last = tmp;
		}
		s_env = s_env->next;
	}
	return (head);
}

void	unset(t_command *cmd)
{
	t_env	*first_node;
	t_env	*s_env;
	t_env	*head;
	t_env	*last;

	s_env = *handle_t_env(NULL);
	first_node = s_env;
	head = NULL;
	last = NULL;
	head = process_unset_loop(cmd, s_env, &last);
	free_env_list(first_node);
	handle_t_env(head);
}

// void	unset(t_command *cmd)
// {
// 	t_env	*first_node;
// 	t_env	*s_env;
// 	t_env	*tmp;
// 	t_env	*head;
// 	t_env	*last;

// 	s_env = *handle_t_env(NULL);
// 	first_node = s_env;
// 	head = NULL;
// 	last = NULL;
// 	tmp = NULL;
// 	while (s_env)
// 	{
// 		if (!verify_remove_env(cmd->args, s_env))
// 		{
// 			tmp = malloc(sizeof(t_env));
// 			if (!tmp)
// 				break ;
// 			tmp->env_data = ft_strdup(s_env->env_data);
// 			tmp->next = NULL;
// 			if (!head)
// 				head = tmp;
// 			else
// 				last->next = tmp;
// 			last = tmp;
// 		}
// 		s_env = s_env->next;
// 	}
// 	free_env_list(first_node);
// 	handle_t_env(head);
// }

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
