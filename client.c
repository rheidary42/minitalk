/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 06:37:01 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/03 06:37:02 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define _POSIX_C_SOURCE 200809L // Docker specific
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t ack = 0;

void	ack_handler(int sig)
{
    (void)sig;
    ack = 1;
}

void	send_signal(char c, int j, char *server)
{
	ack = 0;
	if ((c & (1 << (7 - j))) != 0)
		kill((pid_t)atoi(server), SIGUSR2);
	else
		kill((pid_t)atoi(server), SIGUSR1);
	while (!ack)
		pause();
}

int atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

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
    return result * sign;
}

int	main(int argc, char **argv)
{
	int				i;
	int				j;
	char			c;
	struct sigaction s_sa;
	
	s_sa.sa_flags = 0;
	s_sa.sa_handler = ack_handler;
	sigemptyset(&s_sa.sa_mask);
	sigaction(SIGUSR1, &s_sa, NULL);
	i = 0;
	if (argc != 3)
		return (1);
	while (argv[2][i])
	{
		c = argv[2][i];
		j = -1;
		while (++j < 8)
			send_signal(c, j, argv[1]);
		i++;
	}
	return (0);
}
