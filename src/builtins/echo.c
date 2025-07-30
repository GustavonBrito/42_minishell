/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:54:36 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/07/29 20:59:55 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo(t_command *cmd);
static int	process_flags(char **args);
static int	verify_flag(char *arg);
static void	print_args(t_command *cmd, int start);

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
	i = process_flags(cmd->args);
	flag = (i > 1);
	print_args(cmd, i);
	if (!flag)
		ft_printf("\n");
}

static int	process_flags(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && verify_flag(args[i]))
	{
		flag = 1;
		i++;
	}
	if (flag)
		return (i);
	return (1);
}

static int	verify_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

static void	print_args(t_command *cmd, int start)
{
	int	i;

	i = start;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i] && cmd->token_types[i - 1] != VAR)
			ft_printf(" ");
	}
}
