/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:41 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:35:42 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

static void	define_size_to_return(int number, int *bytes_counted)
{
	*bytes_counted = 0;
	if (number <= 0)
		*bytes_counted += 1;
}

static int	check_int_limit(int limit, int *bytes_counted)
{
	if (limit == -2147483648)
	{
		*bytes_counted = 11;
		return (1);
	}
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

int	ft_putnbr_printf(int n)
{
	char	number[11];
	int		size_number;
	int		result;
	int		bytes_counted;

	size_number = 0;
	define_size_to_return(n, &bytes_counted);
	if (check_int_limit(n, &bytes_counted) == 1)
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
	return (write_func(size_number, number, 1), bytes_counted += size_number);
}
