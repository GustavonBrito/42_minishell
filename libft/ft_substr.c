/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:16 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:35:18 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

static char	*ft_malloc_to_return(void)
{
	char	*pointer_malloc;

	pointer_malloc = (char *)malloc(1 * sizeof(char));
	if (pointer_malloc == (void *)0)
		return ((void *)0);
	pointer_malloc[0] = '\0';
	return (pointer_malloc);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*pointer_malloc;
	unsigned int	i;
	size_t			string_size;

	string_size = ft_strlen(s);
	i = 0;
	if (start > string_size)
		return (ft_malloc_to_return());
	if (start + len > string_size)
		len = string_size - start;
	pointer_malloc = (char *)malloc((len + 1) * sizeof(char));
	if (pointer_malloc == ((void *)0))
		return (((void *)0));
	while (i < len)
	{
		pointer_malloc[i] = s[start];
		start++;
		i++;
	}
	pointer_malloc[len] = '\0';
	return ((char *)(pointer_malloc));
}
