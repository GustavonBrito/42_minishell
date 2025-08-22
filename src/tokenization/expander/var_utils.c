/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:57:36 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:04:44 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				process_single_argument(t_command *cmd, int index);
t_token_type	get_token_type(t_command *cmd, int index);
int				updt_arg(t_command *cmd, int index, char *expand, char *arg);

int	process_single_argument(t_command *cmd, int index)
{
	t_token_type	token_type;
	int				expand_check;
	char			*expand;
	char			*arg;

	token_type = get_token_type(cmd, index);
	expand_check = should_expand_variables(cmd->args[index], token_type);
	expand = expand_str(cmd->args[index], expand_check);
	if (!expand)
		return (report_error("memory allocation error", 1));
	arg = remove_quotes(expand);
	if (!arg)
		return (handle_expand_error(expand));
	return (updt_arg(cmd, index, expand, arg));
}

t_token_type	get_token_type(t_command *cmd, int index)
{
	if (cmd->token_types)
		return (cmd->token_types[index]);
	return (WORD);
}

int	updt_arg(t_command *cmd, int index, char *expand, char *final_arg)
{
	free(cmd->args[index]);
	cmd->args[index] = final_arg;
	if (final_arg != expand)
		free(expand);
	return (0);
}
