/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:58:16 by rheidary          #+#    #+#             */
/*   Updated: 2025/06/10 19:26:38 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	char	nbholder;
	int		i;

	i = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		i += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		i += ft_putnbr(nb / 10);
	nbholder = nb % 10 + '0';
	i += write(1, &nbholder, 1);
	return (i);
}

int	ft_uputnbr(unsigned int nb)
{
	char				nbholder;
	unsigned int		i;

	i = 0;
	if (nb >= 10)
		i += ft_putnbr(nb / 10);
	nbholder = nb % 10 + '0';
	i += write(1, &nbholder, 1);
	return (i);
}

int	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	base_l;
	unsigned int	nbr2;
	int				count;

	count = 0;
	nbr2 = nbr;
	base_l = 16;
	if (nbr2 == 0)
	{
		count += ft_putchar(base[0]);
		return (count);
	}
	if (nbr2 >= base_l)
		count += ft_putnbr_base(nbr2 / base_l, base);
	count += ft_putchar(base[nbr2 % base_l]);
	return (count);
}
