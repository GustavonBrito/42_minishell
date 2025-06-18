/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:32:26 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:32:29 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	index;
	int	sign;
	int	result;

	index = 0;
	sign = 1;
	result = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || nptr[index] == ' ')
	{
		index++;
	}
	if (nptr[index] == '+')
		index++;
	else if (nptr[index] == '-')
	{
		sign = -1 * sign;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
	{
		result = 10 * result + (nptr[index] - '0');
		index++;
	}
	return (result * sign);
}
