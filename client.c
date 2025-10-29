/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 06:37:01 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/29 17:53:50 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf/libftprintf.h"

volatile sig_atomic_t	g_ack = 0;

void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	if (sig == SIGUSR2)
	{
		write(1, "Server busy\n", 12);
		exit(EXIT_SUCCESS);
	}
	// ft_printf("set g_ack to 1\n");
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	send_signal(char c, int j, char *server)
{
	g_ack = 0;
	// ft_printf("set g_ack to 0\n");
	if ((c & (1 << (7 - j))) != 0)
	{
		if (kill((pid_t)ft_atoi(server), SIGUSR2) == -1)
		{
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill((pid_t)ft_atoi(server), SIGUSR1) == -1)
		{
			ft_printf("Error\n");
			exit (EXIT_FAILURE);
		}
	}
	// ft_printf("sent bit, pausing\n");
	while (!g_ack)
		usleep(10);
	// ft_printf("ending pause\n");
}

int	main(int argc, char **argv)
{
	int					i;
	int					j;
	int					c;
	struct sigaction	sa;

	if (argc != 3 || ft_atoi(argv[1]) <= 0)
		return (ft_printf("Error\n"));
	sa.sa_flags = 0;
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	while (1)
	{
		c = argv[2][i];
		j = -1;
		while (++j < 8)
			send_signal(c, j, argv[1]);
		if (c == '\0')
			break ;
		i++;
	}
	write(1, "Server finished\n", 16);
	return (0);
}
