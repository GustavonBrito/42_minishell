/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:33:26 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:33:28 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"
#include <stdio.h>

static int	check_int_limit(int limit)
{
	if (limit == -2147483648)
		return (1);
	return (0);
}

static int	write_func(int size_number, char number[], int fd)
{
	while (size_number - 1 >= 0)
	{
		write(fd, &number[size_number - 1], 1);
		size_number--;
	}
	return (size_number);
}

int	ft_putnbr(int n)
{
	char	number[11];
	int		size_number;
	int		result;
	int		size_to_return;

	size_number = 0;
	size_to_return = 0;
	if (check_int_limit(n) == 1)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	else if (n == 0)
		write(1, "0", 1);
	while (n > 0)
	{
		result = n % 10;
		number[size_number] = result + '0';
		n = n / 10;
		size_number++;
	}
	return (write_func(size_number, number, 1), size_to_return += size_number);
}
