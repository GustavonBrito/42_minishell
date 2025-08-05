/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/08/05 02:00:01 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_quotes(char *input, t_token **token_lst, int i);
int		handle_var(char *input, t_token **token_lst, int i);
int		handle_word_quotes(char *input, t_token **token_lst, int i);
int		handle_att_quote(char *input, t_token **token_lst, int i);
int		handle_escape(char *input, t_token **token_lst);

int	handle_quotes(char *input, t_token **token_lst, int i)
{
	char	quote_char;
	int		start;
	int		end;

	quote_char = input[i];
	start = i;
	end = find_quote_end(input, i, quote_char);
	if (end == -1)
		return (1);
	return (quote_token(input, token_lst, start, end));
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

int	handle_word_quotes(char *input, t_token **token_lst, int i)
{
	int		start;
	int		end;
	int		len;

	start = i;
	end = find_word_end(input, i);
	len = end - start;
	return (create_w_token(input, token_lst, start, len));
}

int	handle_att_quote(char *input, t_token **token_lst, int i)
{
	int		start;
	int		j;
	char	*full_word;
	int		len;
	char	quote_char;

	start = i;
	j = i;
	while (input[j] && !ft_isspace(input[j]) && !ft_isop(input[j])
		&& input[j] != '$')
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

int	handle_escape(char *input, t_token **token_lst)
{
	char	*w_esc;
	int		j;
	int		a;
	int		final_escape_i;
	int		first_escape_i;
	int		flag;
	size_t	size;
	char	*new_word;

	j = -1;
	first_escape_i = 0;
	flag = 0;
	while (input[++j])
	{
		if (ft_isspace(input[j]) && (ft_isalnum(input[j + 1])
				|| (unsigned char)input[j + 1] > 127) && flag == 0)
		{
			j++;
			flag = 1;
			first_escape_i = j;
		}
	}
	final_escape_i = j;
	w_esc = ft_substr(input, first_escape_i, first_escape_i - final_escape_i);
	size = ft_strlen(w_esc);
	new_word = malloc(sizeof(char) * (size + 1));
	j = -1;
	a = 0;
	while (w_esc[++j])
	{
		if (w_esc[j] != '\\' && w_esc[j] != '/')
		{
			new_word[a] = w_esc[j];
			a++;
		}
	}
	new_word[a] = '\0';
	add_token(token_lst, new_word, DOUBLE_QUOTE);
	free(w_esc);
	free(new_word);
	return (0);
}
