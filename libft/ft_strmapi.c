/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:34:41 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:34:45 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	a;
	char			*str_with_func_applied;

	a = 0;
	if (s == (void *)0 || f == (void *)0)
		return ((void *)0);
	str_with_func_applied = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (str_with_func_applied == (void *)0)
		return ((void *)0);
	while (s[a])
	{
		str_with_func_applied[a] = f(a, s[a]);
		a++;
	}
	str_with_func_applied[a] = '\0';
	return (str_with_func_applied);
}
