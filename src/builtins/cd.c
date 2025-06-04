/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:47:58 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/03 22:11:30 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void cd(char *argv, t_builtins **builtins)
{
	//Implementar um pouco dessa funcao, parei aqui
}

// Observações importantes

// chdir() retorna -1 em caso de erro → você deve tratar isso.

// getcwd() te dá o caminho real após o cd (resolvendo .., . etc).

// setenv() atualiza as variáveis visíveis no shell.

//	char *getenv(const char *name);