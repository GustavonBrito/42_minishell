/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/06/23 23:27:22 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		update_pwd(void);

void	update_pwd(void)
{
	char	*actual_directory;

	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	setenv("PWD", actual_directory, 1);
	free(actual_directory);
}
