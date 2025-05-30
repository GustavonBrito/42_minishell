
#include "../includes/minishell.h"
#include <stdio.h>

void	print_tokens(t_token *head);
void	print_commands(t_command *cmd);

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		ft_printf("Token: %s\n", current->value);
		current = current->next;
	}
}

void	print_commands(t_command *cmd)
{
	t_command	*current_command;
	t_redir	*current_redir;
	int		i;
	int		cmd_num;

	current_command = cmd;
	cmd_num = 1;

	while (current_command)
	{
		printf("=== COMMAND %d ===\n", cmd_num);
		printf("Args: ");
		if (current_command->args)
		{
			i = 0;
			while (current_command->args[i])
			{
				printf("'%s' ", current_command->args[i]);
				i++;
			}
		}
		printf("\n");

		current_redir = current_command->redirs;
		while (current_redir)
		{
			printf("Redir: ");
			if (current_redir->type == REDIR_IN)
				printf("< '%s'\n", current_redir->file);
			else if (current_redir->type == REDIR_OUT)
				printf("> '%s'\n", current_redir->file);
			else if (current_redir->type == REDIR_APPEND)
				printf(">> '%s'\n", current_redir->file);
			else if (current_redir->type == HEREDOC)
				printf("<< '%s'\n", current_redir->file);
			current_redir = current_redir->next;
		}

		current_command = current_command->next;
		cmd_num++;

		if (current_command)
			printf("   |\n   V\n");
	}
	printf("================\n");
}
