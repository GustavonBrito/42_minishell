/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:32:59 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:33:01 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_unsigned;
	const unsigned char	*src_unsigned;
	unsigned int		i;

	i = 0;
	dest_unsigned = dest;
	src_unsigned = src;
	if (dest == (void *)0 && src == (void *)0)
		return ((void *)0);
	while (i < n)
	{
		dest_unsigned[i] = src_unsigned[i];
		i++;
	}
	return ((unsigned char *)(dest_unsigned));
}
