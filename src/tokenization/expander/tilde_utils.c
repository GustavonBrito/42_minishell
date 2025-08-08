/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:11:11 by luiza             #+#    #+#             */
/*   Updated: 2025/08/08 19:17:21 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			append_remaining_path(const char *str, char **res, int i_cmd);
int			append_literal_tilde(char **res);
char		*process_quote_rm(char *str, char *result);
static int	is_quote_char(char c);
static int	skip_q_section(char *str, char *result, int *j, int i);

int	append_remaining_path(const char *str, char **res, int i_cmd)
{
	while (str[i_cmd] && str[i_cmd] != ' ' && str[i_cmd] != '\t')
	{
		*res = append_char(*res, str[i_cmd]);
		if (!*res)
			return (0);
		i_cmd++;
	}
	return (i_cmd);
}

int	append_literal_tilde(char **res)
{
	*res = append_char(*res, '~');
	if (!*res)
		return (0);
	return (1);
}

char	*process_quote_rm(char *str, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote_char(str[i]))
			i = skip_q_section(str, result, &j, i);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

static int	skip_q_section(char *str, char *result, int *j, int i)
{
	char	quote_char;

	quote_char = str[i];
	i++;
	while (str[i] && str[i] != quote_char)
		result[(*j)++] = str[i++];
	if (str[i] == quote_char)
		i++;
	return (i);
}
