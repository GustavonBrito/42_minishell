/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 20:32:01 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cd(t_command *cmd);
static void	cd_to_home(void);
static void	cd_to_target(char *target_dir);

void	cd(t_command *cmd)
{
	if (cmd->args[2] != NULL)
	{
		write(2, " too many arguments", 19);
		exit(1);
	}
	if (!cmd->args[1])
	{
		cd_to_home();
		return ;
	}
	cd_to_target(cmd->args[1]);
}

static void	cd_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_printf("cd: HOME not set\n");
		return ;
	}
	chdir(home);
	update_pwd();
}

static void	cd_to_target(char *target_dir)
{
	if (chdir(target_dir) == -1)
	{
		write(2, " No such file or directory", 26);
		exit(1);
	}
	update_pwd();
}
