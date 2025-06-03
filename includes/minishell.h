/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:22 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/06/02 22:47:20 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../libft/headers/libft.h"
#include "../libft/headers/get_next_line.h"
#include "../libft/headers/ft_printf.h"

typedef struct s_builtins
{
	char	*name; // nome do builtin
	int		flag;
	void* (*function)(char **args); // ponteiro para a funcao
}	t_builtins;

void	shell_loop(void); // Loop principal aonde o minishell roda
void	check_exit_condition(char *buffer_received); // funcao para checar se exit foi escrito no terminal.
void	signal_handler(int signal); // Lida com os sinais UNIX como ctrl c, ctrl d
void	is_builtin(char *builtin); //Verifica qual builtin foi passado como argumento
void	echo(char *builtin, t_builtins **builtins); // Funcao para implementar a funcao echo
void	verify_flag(char *argv_splited, t_builtins **builtins); // Verifica se a flag é valida
void	printf_without_n(char **buffer); // Funcao para printar echo quando tem flag

#endif