/*
#include "minishell.h"

void debug_tokens(t_command *cmd)
{
	int i = 0;
	printf("DEBUG TOKENS - Command: %s\n", cmd->args[0]);
	while (cmd->args[i])
	{
		printf("  arg[%d]: '%s' (len=%zu)\n", i, cmd->args[i], strlen(cmd->args[i]));
		// Mostrar bytes em hex para caracteres especiais
		unsigned char *str = (unsigned char *)cmd->args[i];
		printf("  hex: ");
		for (int j = 0; str[j]; j++)
			printf("%02x ", str[j]);
		printf("\n");
		i++;
	}
	printf("  total args: %d\n", i);
}

void debug_command_list(t_command *cmd)
{
	t_command *current = cmd;
	int count = 0;

	printf("DEBUG: Command list structure:\n");
	while (current)
	{
		printf("  Command %d: %s\n", count, current->args[0]);
		if (current->next)
			printf("    -> has next\n");
		else
			printf("    -> no next (last)\n");
		current = current->next;
		count++;
	}
	printf("DEBUG: Total commands in list: %d\n", count);
}

// 5. Debug na expansão de variáveis para verificar o argumento do grep
void debug_variable_expansion(t_command *cmd)
{
	printf("DEBUG: Variable expansion for command: %s\n", cmd->args[0]);
	for (int i = 0; cmd->args[i]; i++)
	{
		printf("  Before expansion arg[%d]: '%s'\n", i, cmd->args[i]);
		// Se você tiver acesso ao valor antes da expansão, mostre também
	}
}

// 6. Teste específico para reproduzir o problema
void test_grep_pattern(void)
{
	// Teste se o padrão ");$ " é válido para grep
	printf("DEBUG: Testing grep pattern validity\n");

	// Criar um processo para testar grep com o padrão
	pid_t pid = fork();
	if (pid == 0)
	{
		// Redirecionar entrada para /dev/null para evitar que grep espere input
		int fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);

		// Testar execve com grep e o padrão problemático
		char *args[] = {"grep", ");$ ", NULL};
		char *env[] = {NULL};
		execve("/usr/bin/grep", args, env);
		exit(127);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("DEBUG: grep test exit status: %d\n", WEXITSTATUS(status));
	}
}

void test_original_command(void)
{
	printf("DEBUG: Testing original failing command\n");

	// Simular: cat minishell.h | grep ");$ "
	// Primeiro testar cat com arquivo inexistente
	pid_t pid1 = fork();
	if (pid1 == 0)
	{
		char *args[] = {"cat", "minishell.h", NULL};
		char *env[] = {NULL};
		execve("/usr/bin/cat", args, env);
		exit(127);
	}
	else if (pid1 > 0)
	{
		int status;
		waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			printf("DEBUG: cat minishell.h exit status: %d\n", WEXITSTATUS(status));
	}

	// Testar grep com entrada vazia (pipe quebrado)
	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		// Simular pipe quebrado - stdin fechado
		close(STDIN_FILENO);
		char *args[] = {"grep", ");$ ", NULL};
		char *env[] = {NULL};
		execve("/usr/bin/grep", args, env);
		exit(127);
	}
	else if (pid2 > 0)
	{
		int status;
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			printf("DEBUG: grep );$  with closed stdin exit status: %d\n", WEXITSTATUS(status));
	}
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	ft_printf("=== FT TESTER PRINT_TOKENS===\n");
	ft_printf("=== TOKENS ===\n");
	while (current)
	{
		ft_printf("Token: '%s' [%s]\n", current->value, get_token_type_name
			(current->type));
		current = current->next;
	}
	ft_printf("==============\n");
}

void	print_commands(t_command *cmd)
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
}

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

void	print_exit_status(void)
{
    ft_printf("=== FT TESTER EXIT_STATUS ===\n");
    ft_printf("Current g_exit_status: %d\n", g_exit_status);
    ft_printf("============================\n");
}
 */
