/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:07:56 by gserafio          #+#    #+#             */
/*   Updated: 2025/09/18 09:18:47 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier_loop(char *arg, int *equal_passed, int *first_passed);

int	check_identifier_loop(char *arg, int *equal_passed, int *first_passed)
{
	int	j;

	j = 0;
	while (arg[j] && *equal_passed == 0)
	{
		if (*first_passed == 0 && (ft_isalnum(arg[j]) == 4))
			return (0);
		if (arg[j] == '=')
		{
			if (j > 0 && (ft_isalnum(arg[j - 1]) == 0 && arg[j - 1] != '_'))
				return (0);
			*equal_passed = 1;
		}
		else
		{
			if (ft_isalnum(arg[j]) == 0 && arg[j] != '_')
				return (0);
		}
		j++;
		*first_passed = 1;
	}
	return (1);
}
