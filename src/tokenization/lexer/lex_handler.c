/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/08/03 22:33:29 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_quotes(char *input, t_token **token_lst, int i);
int			handle_var(char *input, t_token **token_lst, int i);
static int	process_var_name(char *input, t_token **token_lst, int start);
static int	handle_special_vars(char *input, t_token **token_lst, int i);
int			handle_word_with_quotes(char *input, t_token **token_lst, int i);

int	handle_quotes(char *input, t_token **token_lst, int i)
{
	char	quote_char;
	int		start;
	int		j;
	char	*quoted_content;
	int		len;
	int		quote_count;
	int		temp_j;

	quote_char = input[i];
	start = i;
	j = i + 1;
	while (input[j])
	{
		if (input[j] == quote_char)
		{
			if (quote_char == '"')
			{
				quote_count = 1;
				temp_j = j + 1;
				while (input[temp_j] && input[temp_j] != ' ' && input[temp_j] != '|')
				{
					if (input[temp_j] == '"')
						quote_count++;
					temp_j++;
				}
				if (quote_count % 2 == 0)
					break ;
			}
			else
				break ;
		}
		j++;
	}
	if (input[j] != quote_char)
		return (1);
	j++;
	len = j - start;
	quoted_content = ft_substr(input, start, len);
	if (!quoted_content)
		return (len);
	if (quote_char == '\'')
		add_token(token_lst, quoted_content, SINGLE_QUOTE);
	else
		add_token(token_lst, quoted_content, DOUBLE_QUOTE);
	free(quoted_content);
	return (len);
}

int	handle_var(char *input, t_token **token_lst, int i)
{
	int	start;

	start = i;
	i++;
	if (input[i] == '?' || input[i] == '$')
		return (handle_special_vars(input, token_lst, i - 1));
	if (!ft_isalpha(input[i]) && input[i] != '_')
	{
		add_token(token_lst, "$", WORD);
		return (1);
	}
	return (process_var_name(input, token_lst, start));
}

static int	process_var_name(char *input, t_token **token_lst, int start)
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

static int	handle_special_vars(char *input, t_token **token_lst, int i)
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

int	handle_word_with_quotes(char *input, t_token **token_lst, int i)
{
	int		start;
	int		j;
	char	*full_word;
	int		len;
	char	quote_char;

	start = i;
	j = i;
	while (input[j] && !ft_isspace(input[j]) && !ft_isop(input[j]))
	{
		if (input[j] == '\'' || input[j] == '"')
		{
			quote_char = input[j];
			j++;
			while (input[j] && input[j] != quote_char)
				j++;
			if (input[j] == quote_char)
				j++;
		}
		else
			j++;
	}
	len = j - start;
	full_word = ft_substr(input, start, len);
	if (!full_word)
		return (len);
	add_token(token_lst, full_word, WORD);
	free(full_word);
	return (len);
}
