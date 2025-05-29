/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:01 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:36:03 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

static int	write_func(int size_number, char number[], int fd)
{
	while (size_number - 1 >= 0)
	{
		write(fd, &number[size_number - 1], 1);
		size_number--;
	}
	return (size_number);
}

int	ft_unsigned_printf(unsigned int n)
{
	char	number[10];
	int		size_number;
	int		result;
	int		bytes_count;

	size_number = 0;
	bytes_count = 0;
	number[0] = '\0';
	if (n == 0)
	{
		write (1, "0", 1);
		bytes_count = 1;
	}
	while (n > 0)
	{
		result = n % 10;
		number[size_number] = result + '0';
		n = n / 10;
		size_number++;
	}
	return (write_func(size_number, number, 1), bytes_count += size_number);
}
