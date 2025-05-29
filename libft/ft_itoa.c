/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:32:44 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:32:45 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

static char	*ft_convert_number(int n, char *convert_buff, int count_digit)
{
	int	temp_int;
	int	i;

	i = count_digit;
	if (n < 0)
	{
		convert_buff[0] = '-';
		n = -n;
	}
	if (n == 0)
		return (convert_buff);
	temp_int = n % 10;
	ft_convert_number(n / 10, convert_buff, i - 1);
	convert_buff[i - 1] = temp_int + '0';
	return (convert_buff);
}

static int	ft_count_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*buffer_converted;
	int		digits_counted;

	if (n == -2147483648)
	{
		buffer_converted = (char *)malloc(sizeof(char) * (11 + 1));
		if (buffer_converted == (void *)0)
			return ((void *)0);
		ft_strlcpy(buffer_converted, "-2147483648", 12);
		buffer_converted[11] = '\0';
		return (buffer_converted);
	}
	digits_counted = ft_count_digits(n);
	buffer_converted = (char *)malloc(sizeof(char) * (digits_counted + 1));
	if (buffer_converted == (void *)0)
		return ((void *)0);
	if (n == 0)
	{
		ft_strlcpy(buffer_converted, "0", 2);
		buffer_converted[1] = '\0';
		return (buffer_converted);
	}
	ft_convert_number(n, buffer_converted, digits_counted);
	buffer_converted[digits_counted] = '\0';
	return (buffer_converted);
}
