/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:54:19 by luiza             #+#    #+#             */
/*   Updated: 2025/08/05 02:11:47 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_word_end(char *input, int i);
int			find_asg_end(char *input, int i);
static int	skip_quoted_section(char *input, int j);
int			create_token(char *input, t_token **tkn_lst, int start, int len);

int	find_word_end(char *input, int i)
{
	int	j;

	j = i;
	while (input[j] && !ft_isspace(input[j]) && !ft_isop(input[j]))
	{
		if (input[j] == '\'' || input[j] == '"')
			j = skip_quoted_section(input, j);
		else
			j++;
	}
	return (j);
}

int	find_asg_end(char *input, int i)
{
	int	j;

	j = i;
	while (input[j] && !ft_isspace(input[j]) && !ft_isop(input[j])
		&& input[j] != '$')
	{
		if (input[j] == '\'' || input[j] == '"')
			j = skip_quoted_section(input, j);
		else
			j++;
	}
	return (j);
}

static int	skip_quoted_section(char *input, int j)
{
	char	quote_char;

	quote_char = input[j];
	j++;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
		j++;
	return (j);
}

int	create_token(char *input, t_token **tkn_lst, int start, int len)
{
	char	*full_word;

	full_word = ft_substr(input, start, len);
	if (!full_word)
		return (len);
	add_token(tkn_lst, full_word, WORD);
	free(full_word);
	return (len);
}
