/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:54:01 by luiza             #+#    #+#             */
/*   Updated: 2025/08/05 02:00:01 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_op(char *input, t_token **token_lst, int i);
int			handle_quote_token(char *input, t_token **token_lst, int i);
int			handle_word_token(char *input, t_token **token_lst, int i);
static int	handle_input_redir(char *input, t_token **token_lst, int i);
static int	handle_output_redir(char *input, t_token **token_lst, int i);

int	handle_op(char *input, t_token **token_lst, int i)
{
	if (input[i] == '|')
	{
		add_token(token_lst, "|", PIPE);
		return (1);
	}
	else if (input[i] == '<')
		return (handle_input_redir(input, token_lst, i));
	else if (input[i] == '>')
		return (handle_output_redir(input, token_lst, i));
	return (0);
}

int	handle_quote_token(char *input, t_token **token_lst, int i)
{
	int	res;

	res = handle_quotes(input, token_lst, i);
	if (res == 1)
	{
		free_tokens(*token_lst);
		return (-1);
	}
	return (i + res);
}

int	handle_word_token(char *input, t_token **token_lst, int i)
{
	if (is_assignment_with_quotes(input, i))
		return (i + handle_att_quote(input, token_lst, i));
	else
		return (i + handle_word_quotes(input, token_lst, i));
}

static int	handle_input_redir(char *input, t_token **token_lst, int i)
{
	if (input[i + 1] == '<')
	{
		add_token(token_lst, "<<", HEREDOC);
		return (2);
	}
	add_token(token_lst, "<", REDIR_IN);
	return (1);
}

static int	handle_output_redir(char *input, t_token **token_lst, int i)
{
	if (input[i + 1] == '>')
	{
		add_token(token_lst, ">>", REDIR_APPEND);
		return (2);
	}
	add_token(token_lst, ">", REDIR_OUT);
	return (1);
}
