/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:12:38 by rheidary          #+#    #+#             */
/*   Updated: 2025/07/06 16:20:45 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *s, ...)
{
	int		i;
	int		remove;
	int		append;
	va_list	args;

	if (!s)
		return (-1);
	va_start (args, s);
	i = 0;
	remove = 0;
	append = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == ' ' || s[i + 1] == '\0')
				return (-1);
			append += for_spe_check(s[++i], args);
			remove += 2;
			i++;
			continue ;
		}
		write(1, &s[i++], 1);
	}
	return (va_end(args), i + append - remove);
}

int	for_spe_check(const char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (mem_to_str(va_arg(args, void *)));
	else if (c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_uputnbr(va_arg(args, int)));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(args, int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF"));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

// #include <stdio.h>
// #include <limits.h>
// int main()
// {
// 	int rv = ft_printf("%p\n", LONG_MIN);
// 	printf("\n%i\n", rv);
// 	rv = printf("%p\n", LONG_MIN);
// 	printf("\n%i\n", rv);
// 	return (0);
// }