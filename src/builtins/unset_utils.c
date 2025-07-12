/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:43:13 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/11 12:56:33 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			break ;
		}
		i++;
	}
	return (skip_flag);
}
