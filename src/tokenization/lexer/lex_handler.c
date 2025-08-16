/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/08/10 22:54:21 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_quotes(char *input, t_token **token_lst, int i);
int		handle_var(char *input, t_token **token_lst, int i);
int		handle_word_quotes(char *input, t_token **token_lst, int i);
int		handle_att_quote(char *input, t_token **token_lst, int i);

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
	return (create_token(input, token_lst, start, len));
}

int	handle_att_quote(char *input, t_token **token_lst, int i)
{
	int		start;
	int		end;
	int		len;

	start = i;
	end = find_asg_end(input, i);
	len = end - start;
	return (create_token(input, token_lst, start, len));
}
