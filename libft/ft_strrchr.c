/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:02 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:35:04 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (c > 255)
		c = c % 256;
	while (s[i])
	{
		if (ft_isascii(s[i]) == 0)
			return (0);
		if (s[i] == c)
		{
			s = &s[i];
			i = 0;
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		return (s);
	if (c == 0)
		return (s = &s[i]);
	return (0);
}
