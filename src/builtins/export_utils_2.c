/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 23:08:48 by gserafio          #+#    #+#             */
/*   Updated: 2025/09/17 23:11:47 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_identifier_loop(char *arg, int j, int *equal_passed, int *first_passed);

int	process_identifier_loop(char *arg, int j, int *equal_passed, int *first_passed)
{
	while (arg[j] && *equal_passed == 0)
	{
		if (ft_isalnum(arg[j]) == 4 && *first_passed == 0)
			return (0);
		if (arg[j] == '=')
		{
			if (ft_isalnum(arg[j - 1] == 4) || ft_isalnum(arg[j - 1] == ' '))
				return (0);
			*equal_passed = 1;
		}
		if (ft_isalnum(arg[j]) == 0 && arg[j] != '_' && (arg[j] != '='
				|| arg[j + 1] == '\0'))
			return (0);
		j++;
		*first_passed = 1;
	}
	return (1);
}