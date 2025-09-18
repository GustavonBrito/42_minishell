/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:56:34 by gustavo           #+#    #+#             */
/*   Updated: 2025/09/18 05:49:53 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_minishell(t_command *cmd);
int			is_valid_number(char *str);
static int	count_args(char **args);
static int	ft_atoi_exit(char *str);
static int	calculate_exit_code(int code);

void	exit_minishell(t_command *cmd)
{
	int	arg_count;
	int	exit_code;

	ft_printf("exit\n");
	if (!cmd || !cmd->args)
		cleanup_and_exit(g_exit_status, cmd);
	arg_count = count_args(cmd->args);
	if (arg_count == 1)
	{
		(*(handle_t_env(NULL)))->cat_flag = 0;
		cleanup_and_exit(g_exit_status, cmd);
	}
	if (arg_count >= 2)
	{
		if (analyze_exit_args(cmd, arg_count) == 1)
			return ;
		exit_code = ft_atoi_exit(cmd->args[1]);
		exit_code = calculate_exit_code(exit_code);
		cleanup_and_exit(exit_code, cmd);
	}
	free_env_list(*handle_t_env(NULL));
}

int	is_valid_number(char *str)
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
