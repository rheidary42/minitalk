/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:01:24 by rheidary          #+#    #+#             */
/*   Updated: 2025/07/06 16:24:29 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		for_spe_check(const char c, va_list args);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int nb);
int		ft_uputnbr(unsigned int nb);
int		ft_putnbr_base(int nbr, char *base);
int		mem_to_str(void *mem);
char	*ft_skipzero(char *str);

#endif