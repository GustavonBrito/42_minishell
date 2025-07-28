/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/27 23:57:01 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FILE HAS NORMINETTE ERRORS -> NOTES B4 FTS WITH ERRORS

void	echo(t_command *cmd);

/**
 * @brief Implementa o comando 'echo'.
 *
 * Esta função simula o comportamento do comando 'echo' do shell.
 * Ela imprime os args fornecidos para a saída padrão, separados por espaços.
 * Se nenhum argumento for fornecido, imprime uma nova linha.
 * Suporta a flag '-n' para suprimir a nova linha final.
 *
 * @param cmd Estrutura contendo os argumentos e informações do comando 'echp'.
 */

//norminette:+25 lines needs to be chopped
void	echo(t_command *cmd)
{
	int	i;
	int	flag;

	if (!cmd || !cmd->args)
		return ;
	if (cmd->args[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	i = 1;
	flag = 0;
	while (cmd->args[i] && verify_flag(cmd->args[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i] && cmd->token_types[i - 1] != VAR)
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
}
