/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/08/04 17:15:56 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			process_var_name(char *input, t_token **token_lst, int start);
int			handle_special_vars(char *input, t_token **token_lst, int i);
int			is_assignment_with_quotes(char *input, int start);
int			has_adjacent_quotes(char *input, int start);
static int	token_length(char *input, int i);

int	process_var_name(char *input, t_token **token_lst, int start)
{
	int		i;
	int		len;
	char	*var_name;

	i = start + 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	len = i - start;
	var_name = ft_substr(input, start, len);
	if (!var_name)
		return (len);
	add_token(token_lst, var_name, VAR);
	free(var_name);
	return (len);
}

int	handle_special_vars(char *input, t_token **token_lst, int i)
{
	if (input[i + 1] == '?')
	{
		add_token(token_lst, "$?", VAR);
		return (2);
	}
	if (input[i + 1] == '$')
	{
		add_token(token_lst, "$$", VAR);
		return (2);
	}
	return (1);
}

int	is_assignment_with_quotes(char *input, int start)
{
	int	i;

	i = start;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	if (input[i] == '=' && (input[i + 1] == '"' || input[i + 1] == '\''))
		return (1);
	return (0);
}

int	has_adjacent_quotes(char *input, int start)
{
	int		i;

	i = start;
	if (i > 0 && !ft_isspace(input[i - 1])
		&& !ft_isop(input[i - 1]) && input[i - 1] != '\'')
		return (1);
	i = token_length(input, i);
	return (i > start + 2);
}

static int	token_length(char *input, int i)
{
	char	quote_char;

	while (input[i] && !ft_isspace(input[i])
		&& !ft_isop(input[i]) && input[i] != '\'')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_char = input[i];
			i++;
			while (input[i] && input[i] != quote_char)
				i++;
			if (input[i] == quote_char)
				i++;
		}
		else
			i++;
	}
	return (i);
}
