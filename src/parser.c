/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:35:32 by luiza             #+#    #+#             */
/*   Updated: 2025/06/05 17:30:20 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command			*parse_tokens(t_token *tokens);
static t_command	*parse_command(t_token **current);
static void			add_argument(t_command *cmd, char *arg, int arg_index);
static void			add_redirection(t_command *cmd, t_token_type type, char *file);
static int			count_args(t_token *start);

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*first_command;
	t_command	*current_command;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	current_token = tokens;
	first_command = parse_command(&current_token);
	if (!first_command)
		return (NULL);
	current_command = first_command;
	while (current_token && current_token->type == PIPE)
	{
		current_token = current_token->next;
		if (!current_token)
		{
			ft_printf("minishell: syntax error near unexpected token 'newline'\n");
			free_commands(first_command);
			return (NULL);
		}
		current_command->next = parse_command(&current_token);
		if (!current_command->next)
		{
			free_commands(first_command);
			return (NULL);
		}
		current_command = current_command->next;
	}
	return (first_command);
}

static t_command	*parse_command(t_token **current)
{
	t_command	*cmd;
	int		arg_count;
	int		arg_index;
	int		i;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	arg_count = count_args(*current);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i <= arg_count)
	{
		cmd->args[i] = NULL;
		i++;
	}
	arg_index = 0;
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == WORD)
		{
			add_argument(cmd, (*current)->value, arg_index);
			arg_index++;
		}
		else if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT ||
				(*current)->type == REDIR_APPEND || (*current)->type == HEREDOC)
		{
			t_token_type redir_type = (*current)->type;
			*current = (*current)->next;
			if (!*current || ((*current)->type != WORD
				&& (*current)->type != SINGLE_QUOTE
				&& (*current)->type != DOUBLE_QUOTE))
			{
				ft_printf("minishell: syntax error near unexpected token\n");
				free_commands(cmd);
				return (NULL);
			}
			add_redirection(cmd, redir_type, (*current)->value);
		}
		*current = (*current)->next;
	}
	cmd->args[arg_count] = NULL;
	return (cmd);
}

static void	add_argument(t_command *cmd, char *arg, int arg_index)
{
	cmd->args[arg_index] = ft_strdup(arg);
	if (!cmd->args[arg_index])
	{
		free_commands(cmd);
		return ;
	}
}

static void	add_redirection(t_command *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;

	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
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

static int	count_args(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type != PIPE)
	{
		if (start->type == WORD)
			count++;
		else if (start->type == REDIR_IN || start->type == REDIR_OUT ||
				start->type == REDIR_APPEND || start->type == HEREDOC)
		{
			start = start->next;
			if (start)
				start = start->next;
			continue ;
		}
		start = start->next;
	}
	return (count);
}
