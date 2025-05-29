/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:51 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:35:53 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_putstr_fd_printf(char *s, int fd)
{
	int	a;

	a = 0;
	if (!s)
	{
		write(fd, "(null)", 6);
		a = 6;
		return (a);
	}
	if (fd < 0)
		fd = -fd;
	while (s[a])
	{
		write(fd, &s[a], 1);
		a++;
	}
	return (a);
}
