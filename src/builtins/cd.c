/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/27 23:55:49 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	cd(t_command *cmd);

/**
 * @brief Implementa o comando 'cd'.
 *
 * Esta função muda o diretório de trabalho atual do shell.
 * Se nenhum arg for fornecido, tenta mudar para o diretório HOME do usuário.
 * Se um argumento for fornecido, tenta mudar para o diretório especificado.
 * Em caso de sucesso, atualiza a variável de ambiente PWD.
 * Reporta erros se o dir HOME não estiver definido ou se o diretório de dest
 * não existir ou não puder ser acessado.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando 'cd'.
 */

//norminette:+25 lines needs to be chopped
void	cd(t_command *cmd)
{
	char	*home;
	char	*target_dir;

	if (cmd->args[2] != NULL)
	{
		write(2, " too many arguments", 19);
		exit(1);
	}
	if (!cmd->args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
		chdir(home);
		update_pwd();
		return ;
	}
	target_dir = cmd->args[1];
	if (chdir(target_dir) == -1)
	{
		write(2," No such file or directory", 26);
		exit(1);
		return ;
	}
	update_pwd();
}
