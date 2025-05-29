/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:32:48 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:32:50 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_converted;
	unsigned char		c_converted;
	unsigned int		i;

	i = 0;
	s_converted = (const unsigned char *)s;
	c_converted = (unsigned char)c;
	while (i < n)
	{
		if (s_converted[i] == c_converted)
			return ((unsigned char *)(s_converted = &s_converted[i]));
		i++;
	}
	return (0);
}
