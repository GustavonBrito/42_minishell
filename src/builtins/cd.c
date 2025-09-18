/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/17 11:16:03 by gustavo          ###   ########.fr       */
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
		write(2, "minishell: cd: too many arguments\n", 34);
		g_exit_status = 1;
		return ;
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
	t_env	*env;
	char	*home;

	env = *handle_t_env(NULL);
	home = NULL;
	while (env)
	{
		if (ft_strncmp(env->env_data, "HOME", 4) == 0)
		{
			home = env->env_data;
			home = ft_strrchr(home, '=');
			home++;
		}
		env = env->next;
	}
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
		write(2, "minishell: cd: No such file or directory\n", 41);
		g_exit_status = 1;
		return ;
	}
	update_pwd();
}
