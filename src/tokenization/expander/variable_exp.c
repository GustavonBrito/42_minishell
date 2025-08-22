/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:22:59 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			expand_variables(t_command *cmd);
char		*expand_str(const char *str, int expand_check);
int			expand_env_var(const char *str, char **res, int i_cmd);
int			should_expand_variables(char *str, t_token_type token_type);
static int	is_single_quoted_only(char *str);

int	expand_variables(t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (process_single_argument(cmd, i) != 0)
			return (1);
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
			i_cmd += handle_dollar_exp(str, &res, i_cmd);
		else if (str[i_cmd] == '~' && expand_check
			&& (i_cmd == 0 || str[i_cmd - 1] == ' '))
			i_cmd += handle_tilde_expansion(str, &res, i_cmd);
		else
			i_cmd += handle_regular_char(str, &res, i_cmd);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	expand_env_var(const char *str, char **res, int i_cmd)
{
	char	var_input[256];
	int		i_var;
	char	*temp;
	int		start;

	start = i_cmd;
	i_var = 0;
	while (str[i_cmd] && (ft_isalnum(str[i_cmd]) || str[i_cmd] == '_'))
		var_input[i_var++] = str[i_cmd++];
	var_input[i_var] = '\0';
	temp = get_env_val(var_input);
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	return (i_cmd - start);
}

int	should_expand_variables(char *str, t_token_type token_type)
{
	if (token_type == SINGLE_QUOTE)
		return (0);
	if (is_single_quoted_only(str))
		return (0);
	return (1);
}

static int	is_single_quoted_only(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] != '\'' || str[len - 1] != '\'')
		return (0);
	i = 1;
	while (i < len - 1)
	{
		if (str[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}
