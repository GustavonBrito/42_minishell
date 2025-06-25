/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:04:27 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/24 22:07:58 by luiza            ###   ########.fr       */
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

//norminette:+25 lines needs to be chopped
void	is_builtin(t_command *cmd)
{
	char	**argv;

	argv = cmd->args;
	if (!argv || !argv[0])
		return ;
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		echo(argv);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		cd(cmd);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		export(cmd);
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		unset(cmd);
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		env(0);
	else if (ft_strncmp(argv[0], "exit", 4) == 0)
		exit_minishell();
	else
		return ;
}
