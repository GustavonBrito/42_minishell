/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/09/01 21:59:09 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		export(t_command *cmd);
static void	process_export_arg(char *arg);

void	export(t_command *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		env(1);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->token_types[i] == WORD)
			process_export_arg(cmd->args[i]);
		i++;
	}
}

static void	process_export_arg(char *arg)
{
	char	*equal_sign;
	char	*verify_var;
	t_env	*found_env;

	equal_sign = ft_strchr(arg, '=');
	verify_var = ft_strdup(arg);
	if (validate_identifier(verify_var) == 0)
	{
		write(2, "minishell: not a valid identifier\n", 35);
		free(verify_var);
		g_exit_status = 1;
		return ;
	}
	free(verify_var);
	found_env = find_env_var(arg);
	if (equal_sign)
	{
		found_env = find_env_var(arg);
		*equal_sign = '\0';
		if (ft_strncmp(arg, found_env->env_data, ft_strlen(arg)) == 0)
			update_env_var(found_env, arg, equal_sign + 1);
		else
			create_new_var(found_env, arg, equal_sign + 1);
		*equal_sign = '=';
	}
	else if (ft_strncmp(found_env->env_data, arg, ft_strlen(arg)) != 0)
		create_new_var(found_env, arg, equal_sign);
}
