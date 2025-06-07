
#include "../includes/minishell.h"
#include <stdio.h>

void				print_tokens(t_token *head);
//void				print_commands(t_command *cmd);
void				print_varsexp(t_command *cmd);
static const char	*get_token_type_name(t_token_type type);

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	ft_printf("=== FT TESTER PRINT_TOKENS===\n");
	ft_printf("=== TOKENS ===\n");
	while (current)
	{
		ft_printf("Token: '%s' [%s]\n", current->value, get_token_type_name(current->type));
		current = current->next;
	}
	ft_printf("==============\n");
}

/* void	print_commands(t_command *cmd)
{
	t_command	*current_command;
	t_redir	*current_redir;
	int		i;
	int		cmd_num;

	current_command = cmd;
	cmd_num = 1;
	ft_printf("=== FT TESTER PRINT_COMMANDS ===\n");
	while (current_command)
	{
		ft_printf("=== COMMAND %d ===\n", cmd_num);
		ft_printf("Args: ");
		if (current_command->args)
		{
			i = 0;
			while (current_command->args[i])
			{
				ft_printf("'%s' ", current_command->args[i]);
				i++;
			}
		}
		ft_printf("\n");
		current_redir = current_command->redirs;
		while (current_redir)
		{
			ft_printf("Redir: ");
			if (current_redir->type == REDIR_IN)
				ft_printf("< '%s'\n", current_redir->file);
			else if (current_redir->type == REDIR_OUT)
				ft_printf("> '%s'\n", current_redir->file);
			else if (current_redir->type == REDIR_APPEND)
				ft_printf(">> '%s'\n", current_redir->file);
			else if (current_redir->type == HEREDOC)
				ft_printf("<< '%s'\n", current_redir->file);
			current_redir = current_redir->next;
		}
		current_command = current_command->next;
		cmd_num++;
		if (current_command)
			ft_printf("   |\n   V\n");
	}
	ft_printf("================\n");
} */

void	print_varsexp(t_command *cmd)
{
	t_command	*current_command;
	int		i;
	int		cmd_num;

	current_command = cmd;
	cmd_num = 1;
	ft_printf("=== FT TESTER PRINT_VARSEXP ===\n");
	while (current_command)
	{
		ft_printf("=== COMMAND %d - AFTER VARIABLE EXPANSION ===\n", cmd_num);
		ft_printf("Expanded Args: ");
		if (current_command->args)
		{
			i = 0;
			while (current_command->args[i])
			{
				ft_printf("'%s' ", current_command->args[i]);
				i++;
			}
		}
		ft_printf("\n");
		current_command = current_command->next;
		cmd_num++;
		if (current_command)
			ft_printf("   |\n   V\n");
	}
	ft_printf("================\n");
}

static const char	*get_token_type_name(t_token_type type)
{
	switch (type)
	{
		case WORD:
			return "WORD";
		case PIPE:
			return "PIPE";
		case REDIR_IN:
			return "REDIR_IN";
		case REDIR_OUT:
			return "REDIR_OUT";
		case REDIR_APPEND:
			return "REDIR_APPEND";
		case HEREDOC:
			return "HEREDOC";
		case SINGLE_QUOTE:
			return "SINGLE_QUOTE";
		case DOUBLE_QUOTE:
			return "DOUBLE_QUOTE";
		case VAR:
			return "VAR";
		default:
			return "UNKNOWN";
	}
}
