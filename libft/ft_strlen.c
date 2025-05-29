/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:34:35 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:34:36 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	s_length;

	s_length = 0;
	while (*s)
	{
		s_length++;
		s++;
	}
	return (s_length);
}
