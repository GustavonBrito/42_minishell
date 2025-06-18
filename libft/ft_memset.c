/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:33:09 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:33:11 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_unsigned;
	unsigned int	c_unsigned;
	unsigned int	i;

	s_unsigned = s;
	c_unsigned = c;
	i = 0;
	if (n == 0)
		return (s_unsigned);
	while (i < n)
	{
		s_unsigned[i] = c_unsigned;
		i++;
	}
	return (s_unsigned);
}
