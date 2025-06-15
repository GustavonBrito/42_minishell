/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/15 01:25:51 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(void)
{
	extern char	**environ;
	char		**buffer;
	int			i;
	int			is_upper_char = 64;
	int			is_lower_char = 96;
	char		*temp;

	temp = malloc(sizeof(char) * 2);
	while (++is_upper_char <= 90 && ++is_lower_char <= 122)
	{
		i = -1;
		while (environ[++i])
		{
			ft_strlcpy(temp, environ[i], 2);
			if (temp[0] == is_upper_char || temp[0] == is_lower_char)
			{
				buffer = ft_split(environ[i], '=');
				if (buffer[1] == NULL)
					ft_printf("declare -x %s\n", buffer[0]);
				else
					ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
			}
		}
	}
	i = -1;
	while (environ[++i])
	{
		ft_strlcpy(temp, environ[i], 2);
		if (ft_isalpha(temp[0]) == 0)
		{
			buffer = ft_split(environ[i], '=');
			if (buffer[1] == NULL)
				ft_printf("declare -x %s\n", buffer[0]);
			else
				ft_printf("declare -x %s=\"%s\"\n", buffer[0], buffer[1]);
		}
	}
}

void	env(int is_export)
{
	extern char	**environ;
	int			i;

	i = -1;
	if (is_export == 1)
		print_export();
	else
	{
		while (environ[++i])
			ft_printf("%s\n", environ[i]);
	}
}
