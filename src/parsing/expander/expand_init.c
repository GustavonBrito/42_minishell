/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/06/15 01:48:58 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				expand_variables(t_command *cmd);
char			*expand_str(const char *str, int expand_check);
int				handle_dollar_expansion(const char *str, char **res, int i_cmd);
static int		handle_lone_dollar(char **res);

int	expand_variables(t_command *cmd)
{
	int		i;
	char	*expand;
	int		expand_check;

	i = 0;
	while (cmd->args[i])
	{
		expand_check = (cmd->token_types && cmd->token_types[i]
				!= SINGLE_QUOTE);
		expand = expand_str(cmd->args[i], expand_check);
		if (!expand)
			return (report_error("memory allocation error", 1));
		free(cmd->args[i]);
		cmd->args[i] = expand;
		i++;
	}
	return (0);
}

char	*expand_str(const char *str, int expand_check)
{
	char	*res;
	int		i_cmd;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i_cmd = 0;
	while (str[i_cmd])
	{
		if (str[i_cmd] == '$' && expand_check)
			i_cmd += handle_dollar_expansion(str, &res, i_cmd);
		else
			i_cmd += handle_regular_char(str, &res, i_cmd);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	handle_dollar_expansion(const char *str, char **res, int i_cmd)
{
	i_cmd++;
	if (str[i_cmd] == '?')
		return (expand_exit_status(res) + 1);
	else if (str[i_cmd] == '$')
		return (expand_process_id(res) + 1);
	else if (str[i_cmd] && (ft_isalpha(str[i_cmd]) || str[i_cmd] == '_'))
		return (expand_env_var(str, res, i_cmd) + 1);
	else
		return (handle_lone_dollar(res));
}

static int	handle_lone_dollar(char **res)
{
	*res = append_char(*res, '$');
	if (!*res)
		return (0);
	return (1);
}
