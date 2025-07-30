/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:59:26 by luiza             #+#    #+#             */
/*   Updated: 2025/07/29 21:50:10 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				update_pwd(void);
static void			execute_pwd_export(char *actual_directory);
static t_command	*setup_export_command(void);

void	update_pwd(void)
{
	char	*actual_directory;

	actual_directory = getcwd(NULL, 0);
	if (!actual_directory)
		return ;
	execute_pwd_export(actual_directory);
	free(actual_directory);
}

static void	execute_pwd_export(char *actual_directory)
{
	t_command	*cmd;
	char		*new_dir;

	cmd = setup_export_command();
	if (!cmd)
		return ;
	new_dir = ft_strjoin("PWD=", actual_directory);
	if (!new_dir)
	{
		free_commands(cmd);
		return ;
	}
	cmd->args[1] = ft_strdup(new_dir);
	if (cmd->args[1])
		export(cmd);
	free(new_dir);
	free_commands(cmd);
}

static t_command	*setup_export_command(void)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd || !allocate_command_arrays(cmd, 1))
	{
		if (cmd)
			free(cmd);
		return (NULL);
	}
	return (cmd);
}
