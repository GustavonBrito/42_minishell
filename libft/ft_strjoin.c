/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:34:12 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:34:13 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	k;
	unsigned int	i;
	unsigned int	j;
	char			*pointer_malloc;

	if (s1 && s2)
	{
		i = ft_strlen(s1);
		j = ft_strlen(s2);
		k = -1;
		pointer_malloc = (char *)malloc(sizeof(char) * (i + j + 1));
		if (pointer_malloc == ((void *)0))
			return ((void *)0);
		while (s1[++k])
			pointer_malloc[k] = s1[k];
		k = -1;
		while (s2[++k])
		{
			pointer_malloc[i] = s2[k];
			i++;
		}
		pointer_malloc[i] = '\0';
		return (pointer_malloc);
	}
	return ((void *)0);
}
