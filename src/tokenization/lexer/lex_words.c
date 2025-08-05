/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:54:19 by luiza             #+#    #+#             */
/*   Updated: 2025/08/05 02:19:55 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_word_end(char *input, int i);
int		find_asg_end(char *input, int i);
int		create_token(char *input, t_token **tkn_lst, int start, int len);
int		find_escape_start(char *input);
char	*process_escape_chars(char *w_esc);

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

int	find_escape_start(char *input)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (input[++i])
	{
		if (ft_isspace(input[i]) && (ft_isalnum(input[i + 1])
				|| (unsigned char)input[i + 1] > 127) && flag == 0)
		{
			i++;
			flag = 1;
			return (i);
		}
	}
	return (i);
}

char	*process_escape_chars(char *w_esc)
{
	char	*new_word;
	int		i;
	int		j;

	new_word = malloc(sizeof(char) * (ft_strlen(w_esc) + 1));
	if (!new_word)
		return (NULL);
	i = -1;
	j = 0;
	while (w_esc[++i])
	{
		if (w_esc[i] != '\\' && w_esc[i] != '/')
		{
			new_word[j] = w_esc[i];
			j++;
		}
	}
	new_word[j] = '\0';
	return (new_word);
}
