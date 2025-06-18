/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/06/18 10:55:32 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*process_input(char *input);
static t_token	*lex_token(char *input);
static int	handle_op(char *input, t_token **token_lst, int i);
static int	handle_word(char *input, t_token **token_lst, int i);

void	*process_input(char *input)
{
	t_token	*token_lst;
	if (!input || ft_strlen(input) == 0)
		return NULL;
	token_lst = lex_token(input);
	return (token_lst);
}

static t_token	*lex_token(char *input)
{
	int			i;
	t_token		*token_lst;

	i = 0;
	token_lst = NULL;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '\'' || input[i] == '"')
			i += handle_quotes(input, &token_lst, i);
		else if (input[i] == '$')
			i += handle_var(input, &token_lst, i);
		else if (ft_isop(input[i]))
			i += handle_op(input, &token_lst, i);
		else
			i += handle_word(input, &token_lst, i);
	}
	return (token_lst);
}

static int	handle_op(char *input, t_token **token_lst, int i)
{
	if (input[i] == '|')
	{
		add_token(token_lst, "|", PIPE);
		return (1);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			add_token(token_lst, "<<", HEREDOC);
			return (2);
		}
		add_token(token_lst, "<", REDIR_IN);
		return (1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			add_token(token_lst, ">>", REDIR_APPEND);
			return (2);
		}
		add_token(token_lst, ">", REDIR_OUT);
		return (1);
	}
	return (0);
}

static int	handle_word(char *input, t_token **token_lst, int i)
{
	int		start;
	char	*word;
	int		len;

	start = i;
	while (input[i] && !ft_isspace(input[i]) && !ft_isop(input[i])
			&& input[i] != '"' && input[i] != '$')
		i++;
	len = i - start;
	word = ft_substr(input, start, len);
	if (!word)
		return (len);
	add_token(token_lst, word, WORD);
	free (word);
	return (len);
}
//input[i] != '\''
