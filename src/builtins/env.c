/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 03:57:55 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env(int is_export);
void		print_export(void);

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

void	print_export(void)
{
	t_env	*env;
	t_env	*head;
	t_env	*second_head;
	char	**buffer;

	env = *handle_t_env(NULL);
	while (env)
	{
		env->export_organize_flag = 0;
		env = env->next;
	}
	env = *handle_t_env(NULL);
	head = env;
	while (has_someone_not_printed(env) == 1)
	{
		second_head = env;
		head = NULL;
		while (second_head)
		{
			if (second_head->export_organize_flag == 0)
			{
				if (!head || ft_strncmp(head->env_data, second_head->env_data,
						ft_strlen(head->env_data)) > 0)
					head = second_head;
			}
			second_head = second_head->next;
		}
		head->export_organize_flag = 1;
		buffer = ft_split(head->env_data, '=');
		if (buffer[0][0] == '_' && buffer[0][1] == '\0')
		{
			ft_free_split(buffer);
			continue ;
		}
		else if (ft_strnstr(head->env_data, "=",
				ft_strlen(head->env_data)) == 0)
			ft_printf("declare -x %s\n", buffer[0]);
		else if (buffer[1] == NULL)
			ft_printf("declare -x %s=\"\"\n", buffer[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
		ft_free_split(buffer);
	}
}
