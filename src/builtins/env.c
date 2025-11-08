/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 06:55:26 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			env(int is_export);
static int		has_someone_not_printed(t_env *head);
void			print_export(void);
static t_env	*find_and_mark_smallest(t_env *env);
static void		print_export_variable(t_env *node);

void	env(int is_export)
{
	t_env	**env_ptr;
	t_env	*env;
	int		i;

	if (is_export == 1)
		print_export();
	else
	{
		env_ptr = handle_t_env(NULL);
		env = *env_ptr;
		while (env)
		{
			i = 0;
			while (env->env_data[i])
			{
				if (env->env_data[i] == '=')
				{
					ft_printf("%s\n", env->env_data);
					break ;
				}
				i++;
			}
			env = env->next;
		}
	}
}

static int	has_someone_not_printed(t_env *head)
{
	while (head)
	{
		if (head->export_organize_flag == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

static t_env	*find_and_mark_smallest(t_env *env)
{
	t_env	*smallest;
	t_env	*current;

	smallest = NULL;
	current = env;
	while (current)
	{
		if (current->export_organize_flag == 0)
		{
			if (!smallest || ft_strncmp(smallest->env_data, current->env_data,
					ft_strlen(smallest->env_data)) > 0)
				smallest = current;
		}
		current = current->next;
	}
	if (smallest)
		smallest->export_organize_flag = 1;
	return (smallest);
}

static void	print_export_variable(t_env *node)
{
	char	**buffer;

	buffer = ft_split(node->env_data, '=');
	if (buffer[0][0] == '_' && buffer[0][1] == '\0')
	{
		ft_free_split(buffer);
		return ;
	}
	if (ft_strnstr(node->env_data, "=", ft_strlen(node->env_data)) == 0)
		ft_printf("declare -x %s\n", buffer[0]);
	else if (buffer[1] == NULL)
		ft_printf("declare -x %s=\"\"\n", buffer[0]);
	else
		ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
	ft_free_split(buffer);
}

void	print_export(void)
{
	t_env	*env;
	t_env	*smallest;

	env = *handle_t_env(NULL);
	while (env)
	{
		env->export_organize_flag = 0;
		env = env->next;
	}
	env = *handle_t_env(NULL);
	while (has_someone_not_printed(env) == 1)
	{
		smallest = find_and_mark_smallest(env);
		if (!smallest)
			break ;
		print_export_variable(smallest);
	}
}
