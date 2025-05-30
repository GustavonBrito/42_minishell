/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:21:55 by luiza             #+#    #+#             */
/*   Updated: 2025/05/30 13:46:02 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		process_input(char *input);
static void	lex_token(char *input);
static int	handle_op(char *input, t_token **token_lst, int i);
static int	handle_word(char *input, t_token **token_lst, int i);

void	process_input(char *input)
{
	if (!input || ft_strlen(input) == 0)
		return ;
	lex_token(input);
}

static void	lex_token(char *input)
{
	int			i;
	t_token		*token_lst;
	t_command	*commands;

	i = 0;
	token_lst = NULL;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (ft_isop(input[i]))
			i += handle_op(input, &token_lst, i);
		else
			i += handle_word(input, &token_lst, i);
	}
	print_tokens(token_lst);
	commands = parse_tokens(token_lst);
	if (commands)
	{
		print_commands(commands);
		free_commands(commands);
	}
	free_tokens(token_lst);
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
	while (input[i] && !ft_isspace(input[i]) && !ft_isop(input[i]))
		i++;
	len = i - start;
	word = ft_substr(input, start, len);
	if (!word)
		return (len);
	add_token(token_lst, ft_substr(input, start, i - start), WORD);
	free (word);
	return (len);
}
