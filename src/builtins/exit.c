/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:26 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 19:05:49 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				exit_minishell(t_command *cmd);
static int			is_valid_number(char *str);
static int			count_args(char **args);
static int			ft_atoi_exit(char *str);
static int			calculate_exit_code(int code);

void	exit_minishell(t_command *cmd)
{
	int	arg_count;
	int	exit_code;

	ft_printf("exit\n");
	arg_count = count_args(cmd->args);
	if (!cmd || !cmd->args || arg_count == 1)
		exit(g_exit_status);
	if (arg_count >= 2)
	{
		if (!is_valid_number(cmd->args[1]))
		{
			write(2, "minishell: exit: numeric argument required", 42);
			exit(2);
		}
		if (arg_count > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			g_exit_status = 1;
			return ;
		}
		exit_code = ft_atoi_exit(cmd->args[1]);
		exit(calculate_exit_code(exit_code));
	}
}

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

static int	calculate_exit_code(int code)
{
	int	final_code;

	final_code = code % 256;
	if (final_code < 0)
		final_code += 256;
	return (final_code);
}
