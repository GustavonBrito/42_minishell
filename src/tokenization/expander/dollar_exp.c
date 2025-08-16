/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:03:33 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 21:52:25 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_dollar_exp(const char *str, char **res, int i_cmd);
static int	handle_lone_dollar(char **res);
int			expand_exit_status(char **res);
int			expand_process_id(char **res);
char		*itoa_exit_status(void);

int	handle_dollar_exp(const char *str, char **res, int i_cmd)
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

int	expand_exit_status(char **res)
{
	char	*temp;

	temp = itoa_exit_status();
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	if (!*res)
		return (0);
	return (1);
}

int	expand_process_id(char **res)
{
	char	*temp;

	temp = itoa_process_id();
	if (!temp)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	*res = append_str(*res, temp);
	free(temp);
	if (!*res)
		return (0);
	return (1);
}

char	*itoa_exit_status(void)
{
	return (ft_itoa(g_exit_status));
}
