/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:28 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/08/30 21:43:22 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		export(t_command *cmd);
static void	process_export_arg(char *arg);

void	export(t_command *cmd)
{
	int		i;

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
		write(2, "minishell: export: not a valid identifier\n", 43);
		free_env_list(*handle_t_env(NULL));
		rl_clear_history();
		free(verify_var);
		exit(1);
	}
	free(verify_var);
	if (equal_sign)
	{
		*equal_sign = '\0';
		found_env = find_env_var(arg);
		if (found_env && found_env->env_data[ft_strlen(arg)] == '=')
			update_env_var(found_env, arg, equal_sign + 1);
		else
			create_new_var(found_env, arg, equal_sign + 1);
		*equal_sign = '=';
	}
}
