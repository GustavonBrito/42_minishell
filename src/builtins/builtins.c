/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/27 23:55:13 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	is_builtin(t_command *cmd);

/**
 * @brief Verifica e executa um comando built-in.
 *
 * Esta função recebe uma estrutura `t_command` e verifica se o primeiro
 * argumento (o nome do comando) corresponde a um comando built-in suportado
 * (echo, cd, pwd, export, unset, env, exit).
 * Se houver uma correspondência, a ft correspondente do built-in é invocada,
 * Se não, retorna para a execution() {em exec/execution.c} seguindo o fluxo
 * para chamar execve;
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando.
 */

void	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && ft_strlen(cmd->args[0]) == 2)
		cd(cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		pwd();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0 && ft_strlen(cmd->args[0]) == 6)
		export(cmd);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0 && ft_strlen(cmd->args[0]) == 5)
		unset(cmd);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		env(0);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		exit_minishell(cmd);
}
