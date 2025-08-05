/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:39:52 by luiza             #+#    #+#             */
/*   Updated: 2025/08/05 02:41:56 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_redir *redirs);
int		is_argument_token(t_token_type type);
int		is_redirection_token(t_token_type type);
int		handle_redirection_parsing(t_command *cmd, t_token **current);
void	add_redirection(t_command *cmd, t_token_type type, char *file);

void	free_redirections(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = temp;
	}
}

int	is_argument_token(t_token_type type)
{
	return (type == WORD || type == VAR || type == SINGLE_QUOTE
		|| type == DOUBLE_QUOTE);
}

int	is_redirection_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

int	handle_redirection_parsing(t_command *cmd, t_token **current)
{
	t_token_type	redir_type;
	t_token			*file_token;

	redir_type = (*current)->type;
	*current = (*current)->next;
	if (!*current)
	{
		report_error("syntax error near unexpected token 'newline'", 2);
		return (0);
	}
	file_token = *current;
	if (!is_argument_token(file_token->type))
	{
		report_error("syntax error: expected filename after redirection", 2);
		return (0);
	}
	add_redirection(cmd, redir_type, file_token->value);
	return (1);
}

void	add_redirection(t_command *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;
	char	*clean_file;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	clean_file = remove_quotes(file);
	if (!clean_file)
	{
		free(new_redir);
		return ;
	}
	new_redir->file = clean_file;
	new_redir->type = type;
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}
