/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:38:15 by luiza             #+#    #+#             */
/*   Updated: 2025/07/25 20:27:31 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

int		execute_command(t_command *cmd);
int		execute_builtin(t_command *cmd);
int		execute_external_command(t_command *cmd);
void	handle_command_execution(t_command *cmd);
int		check_builtin(t_command *cmd);

/**
 * @brief Executa um único comando.
 *
 * Esta é a função central para a execução de um comando individual. Ela:
 * 1. Salva os descritores de arquivo padrão (stdin, stdout).
 * 2. Configura quaisquer redirecionamentos associados ao comando.
 * 3. Determina se o comando é um built-in ou um comando externo.
 * 4. Chama a função de execução apropriada (`execute_builtin`
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
	{
		g_exit_status = 1;
		return (0);
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_result = setup_redirections(cmd);
	if (redir_result != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (redir_result);
	}
	if (check_builtin(cmd))
		exec_result = execute_builtin(cmd);
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
int	execute_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	is_builtin(cmd);
	return (g_exit_status);
}

/**
 * @brief Executa um comando externo (não built-in) usando execve.
 *
 * Esta função cria um novo processo filho usando `fork()`.
 * No processo filho, resolve o path do comando usando `find_command_path()` e
 * chama execve().
 * No processo pai, espera pelo processo filho e captura seu status de saída.
 * Reporta erros de `fork` ou "comando não encontrado".
 *
 * @param cmd Um ponteiro para a estrutura `t_command` representando o comando.
 * @return O status de saída do comando externo (0 para sucesso, 127 para comando
 *         não encontrado, outros valores para erros ou sinais).
 */

//norminette: +25 lines: needs to be chopped
int	execute_external_command(t_command *cmd)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		g_exit_status = 1;
		return (g_exit_status);
	}
	else if (pid == 0)
		exit(execute_with_execve(cmd));
	else
	{
		waitpid(pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			return (WEXITSTATUS(g_exit_status));
		else if (WIFSIGNALED(g_exit_status))
			return (128 + WTERMSIG(g_exit_status));
	}
	return (g_exit_status);
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
	int		result;

	if (!cmd)
	{
		g_exit_status = 1;
		return ;
	}
	current = cmd;
	if (has_pipes(current))
	{
		result = execute_pipeline(current);
		g_exit_status = result;
	}
	else
	{
		result = execute_command(current);
		g_exit_status = result;
	}
}

/**
 * @brief Verifica se um comando é um built-in suportado.
 *
 * Compara cmd->args[0] com os nomes dos comandos built-in válidos.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando.
 * @return 1 se for um built-in, 0 se não.
 */

int	check_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		g_exit_status = 1;
		return (0);
	}
	if ((ft_strncmp(cmd->args[0], "echo", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		|| (ft_strncmp(cmd->args[0], "cd", 2) == 0 && ft_strlen(cmd->args[0]) == 2)
		|| (ft_strncmp(cmd->args[0], "pwd", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "export", 6) == 0 && ft_strlen(cmd->args[0]) == 6)
		|| (ft_strncmp(cmd->args[0], "unset", 5) == 0 && ft_strlen(cmd->args[0]) == 5)
		|| (ft_strncmp(cmd->args[0], "env", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "exit", 4) == 0 && ft_strlen(cmd->args[0]) == 4))
		return (1);
	else
		return (0);
}
