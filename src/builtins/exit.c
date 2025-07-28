/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:26 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/26 10:30:12 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				exit_minishell(t_command *cmd);
static int			is_valid_number(char *str);
static int			count_args(char **args);
static int			ft_atoi_exit(char *str);

/**
 * @brief Implementa o comando 'exit'.
 *
 * Esta função encerra a execução do programa minishell.
 * Atualmente, sempre sai com o status de sucesso (0).
 */
void	exit_minishell(t_command *cmd)
{
	int	arg_count;
	int	exit_code;
	int	final_exit_code;

	ft_printf("exit\n");
	if (!cmd || !cmd->args)
	{
		exit(g_exit_status);
		return ;
	}
	arg_count = count_args(cmd->args);
	if (arg_count == 1)
	{
		exit(g_exit_status);
		return ;
	}
	if (arg_count >= 2)
	{
		if (!is_valid_number(cmd->args[1]))
		{
			write(2, " numeric argument required", 26);
			exit(2);
			return ;
		}
		if (arg_count > 2)
		{
			write(2, " too many arguments", 19);
			g_exit_status = 1;
			return ;
		}
		exit_code = ft_atoi_exit(cmd->args[1]);
		final_exit_code = exit_code % 256;
		if (final_exit_code < 0)
			final_exit_code += 256;
		exit(final_exit_code);
	}
}

/**
 * @brief Verifica se uma string é um número válido para o comando exit.
 *
 * @param str String a ser verificada
 * @return 1 se é um número válido, 0 caso contrário
 */
static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] != '\0')
				return (0);
			break ;
		}
		i++;
	}

	return (1);
}

/**
 * @brief Conta o número de argumentos em cmd->args.
 *
 * @param args Array de argumentos
 * @return Número de argumentos
 */
static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

static int	ft_atoi_exit(char *str)
{
	int	result;
	int	sign;
	int	i;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
