/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:30:45 by luiza             #+#    #+#             */
/*   Updated: 2025/08/04 17:43:48 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_quote_end(char *input, int i, char quote_char);
int			quote_token(char *input, t_token **token_lst, int start, int end);
static int	is_valid_double_quote_end(char *input, int pos);
static void	add_quote_by_type(t_token **tkn_lst, char *content, char qte_char);

int	find_quote_end(char *input, int i, char quote_char)
{
	int	j;

	j = i + 1;
	while (input[j])
	{
		if (input[j] == quote_char)
		{
			if (quote_char == '"' && !is_valid_double_quote_end(input, j))
			{
				j++;
				continue ;
			}
			return (j + 1);
		}
		j++;
	}
	return (-1);
}

int	quote_token(char *input, t_token **token_lst, int start,
	int end_pos)
{
	char	*quoted_content;
	int		len;
	char	quote_char;

	len = end_pos - start;
	quote_char = input[start];
	quoted_content = ft_substr(input, start, len);
	if (!quoted_content)
		return (len);
	add_quote_by_type(token_lst, quoted_content, quote_char);
	free(quoted_content);
	return (len);
}

static int	is_valid_double_quote_end(char *input, int pos)
{
	int	quote_count;
	int	temp_j;

	quote_count = 1;
	temp_j = pos + 1;
	while (input[temp_j] && input[temp_j] != ' ' && input[temp_j] != '|')
	{
		if (input[temp_j] == '"')
			quote_count++;
		temp_j++;
	}
	return (quote_count % 2 == 0);
}

static void	add_quote_by_type(t_token **tkn_lst, char *content, char qte_char)
{
	if (qte_char == '\'')
		add_token(tkn_lst, content, SINGLE_QUOTE);
	else
		add_token(tkn_lst, content, DOUBLE_QUOTE);
}
