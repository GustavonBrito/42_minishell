/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:17 by gserafio          #+#    #+#             */
/*   Updated: 2025/04/17 12:36:18 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		ft_putchar_fd_printf(char c, int fd);
int		ft_putstr_fd_printf(char *s, int fd);
int		ft_putptr_fd_printf(uintptr_t n, int fd);
int		ft_putnbr_printf(int n);
int		ft_unsigned_printf(unsigned int n);
int		ft_to_hex_printf(unsigned int n, int fd, int flag_definer);
int		ft_printf(const char *char_array, ...);

#endif