/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_hex_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:56 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:35:58 by gserafio         ###   ########.fr       */
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

int	ft_to_hex_printf(unsigned int n, int fd, int flag_definer)
{
	char			number_hex[12];
	char			number_10_hex;
	int				size_number;
	int				result;
	int				bytes_counted;

	size_number = 0;
	bytes_counted = 0;
	number_10_hex = 'a';
	if (flag_definer == 'X')
		number_10_hex = 'A';
	if (!n)
		return (write(fd, "0", 1), 1);
	while (n > 0)
	{
		result = n % 16;
		if (result >= 0 && result <= 9)
			number_hex[size_number] = result + '0';
		else
			number_hex[size_number] = result - 10 + number_10_hex;
		size_number++;
		n = n / 16;
	}
	return (write_func(size_number, number_hex, fd)
		, bytes_counted += size_number);
}
