/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:38:15 by luiza             #+#    #+#             */
/*   Updated: 2025/06/24 17:46:47 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

int		execute_command(t_command *cmd);
int		execute_builtin_with_redirections(t_command *cmd);
int		execute_external_command(t_command *cmd);
void	handle_command_execution(t_command *cmd);
int		check_builtin(char *cmd);

/**
 * @brief Executa um único comando.
 *
 * Esta é a função central para a execução de um comando individual. Ela:
 * 1. Salva os descritores de arquivo padrão (stdin, stdout).
 * 2. Configura quaisquer redirecionamentos associados ao comando.
 * 3. Determina se o comando é um built-in ou um comando externo.
 * 4. Chama a função de execução apropriada (`execute_builtin_with_redirections`
 *    ou `execute_external_command`).
 * 5. Restaura os descritores de arquivo padrão.
 *
 * @param cmd Um ponteiro para a estrutura `t_command` a ser executada.
 * @return O status de saída do comando executado.
 */
int	execute_command(t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_result;
	int	exec_result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_result = setup_redirections(cmd);
	if (redir_result != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (redir_result);
	}
	if (check_builtin(cmd->args[0]))
		exec_result = execute_builtin_with_redirections(cmd);
	else
		exec_result = execute_external_command(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (exec_result);
}

/**
 * @brief Executa um comando built-in após a configuração de redirecionamentos.
 *
 * Esta função é um wrapper para `is_builtin`, garantindo que um comando built-in
 * seja chamado com seus argumentos apropriados *depois* que os redirecionamentos
 * de E/S tenham sido configurados pelo `execute_command`.
 *
 * @param cmd Um ponteiro para a estrutura `t_command` representando o built-in a
 *        ser executado.
 * @return 0 em caso de sucesso na execução, ou 1 se o comando ou seus argumentos
 *         forem inválidos.
 */
int	execute_builtin_with_redirections(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	is_builtin(cmd);
	return (0);
}

/**
 * @brief Executa um comando externo (não built-in).
 *
 * Esta função cria um novo processo filho usando `fork()`.
 * No processo filho, tenta executar o comando usando `execvp()`.
 * No processo pai, espera pelo processo filho e captura seu status de saída.
 * Reporta erros de `fork` ou "comando não encontrado".
 *
 * @param cmd Um ponteiro para a estrutura `t_command` representando o comando
 *        externo.
 * @return O status de saída do comando externo (0 para sucesso, 127 para comando
 *         não encontrado, outros valores para erros ou sinais).
 */

//norminette: +25 lines: needs to be chopped
int	execute_external_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	(void) cmd;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execvp(cmd->args[0], cmd->args) == -1)
		{
			ft_printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (0);
}

/**
 * @brief Gerencia a execução de uma lista de comandos.
 *
 * Itera sobre a lista de comandos e executa:
 * 1. Se o primeiro comando for uma variável (token VAR), imprime seu conteúdo.
 * 2. Se houver pipes, executa a pipeline.
 * 3. Caso contrário, executa o comando individual.
 * O status de saída do último comando executado é armazenado em `g_exit_status`.
 *
 * @param cmd O primeiro ponteiro para a lista de `t_command` a ser executada.
 */
void	handle_command_execution(t_command *cmd)
{
	t_command	*current;

	if (!cmd)
		return ;
	current = cmd;
	if (cmd->token_types[0] == VAR)
	{
		ft_printf("%s\n", current->args[0]);
		return ;
	}
	if (has_pipes(current))
		g_exit_status = execute_pipeline(current);
	else
		g_exit_status = execute_command(current);
}

int	check_builtin(char *cmd)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(cmd, " ");
	if (!trimmed)
		return (0);
	result = (ft_strncmp(trimmed, "echo", 4) == 0 && (trimmed[4] == ' '
				|| trimmed[4] == '\0'))
		|| (ft_strncmp(trimmed, "cd", 2) == 0 && (trimmed[2] == ' '
				|| trimmed[2] == '\0'))
		|| (ft_strncmp(trimmed, "pwd", 3) == 0 && (trimmed[3] == ' '
				|| trimmed[3] == '\0'))
		|| (ft_strncmp(trimmed, "export", 6) == 0 && (trimmed[6] == ' '
				|| trimmed[6] == '\0'))
		|| (ft_strncmp(trimmed, "unset", 5) == 0 && (trimmed[5] == ' '
				|| trimmed[5] == '\0'))
		|| (ft_strncmp(trimmed, "env", 3) == 0 && (trimmed[3] == ' '
				|| trimmed[3] == '\0'))
		|| (ft_strncmp(trimmed, "exit", 4) == 0 && (trimmed[4] == ' '
				|| trimmed[4] == '\0'));
	free(trimmed);
	return (result);
}
