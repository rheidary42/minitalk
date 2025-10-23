/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:39:39 by rheidary          #+#    #+#             */
/*   Updated: 2025/07/06 16:19:16 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// HARD CODED FOR GLIBC 2.35
#include "libftprintf.h"

char	*ft_skipzero(char *str)
{
	char	*skippedstr;
	int		i;

	skippedstr = str;
	i = 0;
	while (skippedstr[i] == '0')
		i -= -1;
	return (skippedstr + i);
}

int	mem_to_str(void *mem)
{
	int			i;
	uintptr_t	tmp;
	char		str[17];

	tmp = (uintptr_t) mem;
	if (tmp == 0)
		return (ft_putstr("(nil)"));
	i = 15;
	str[16] = '\0';
	ft_putstr("0x");
	while (i >= 0)
	{
		if ((tmp & 15) < 10)
			str[i--] = '0' + (tmp & 15);
		else
			str[i--] = 'a' + ((tmp & 15) - 10);
		tmp >>= 4;
	}
	return (ft_putstr(ft_skipzero(str)) + 2);
}

// int main() {
// 	close(1);
// 	int ret = printf("x");
// 	dprintf(2, "%d\n", ret);
// }
// int main()
// {
// 	char *str = "128";
// 	//printf("%d\n", mem_to_str(&str));
// 	mem_to_str(&str);
// 	printf("\n");
// 	printf("%p\n", &str);
// 	//printf("%d\n", i);
// 	return 0;
// }
