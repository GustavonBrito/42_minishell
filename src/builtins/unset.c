/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:34 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/18 05:27:00 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset(t_command *cmd);
int			verify_remove_env(char **argv, t_env *s_env);

void	unset(t_command *cmd)
{
	t_env	*first_node;
	t_env	*s_env;
	t_env	*filtered_list;

	s_env = *handle_t_env(NULL);
	first_node = s_env;
	filtered_list = create_filtered_list(cmd, s_env);
	free_env_list(first_node);
	handle_t_env(filtered_list);
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

int	verify_remove_env(char **argv, t_env *s_env)
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
