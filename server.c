/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 06:37:05 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/29 17:45:14 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <signal.h>
#include <unistd.h>
#include "ft_printf/libftprintf.h"
#include <stdio.h>

#define MAX_MSG 131072

static volatile sig_atomic_t g_current_client = 0;

void	send_char(char c, char *s, int *index, siginfo_t *info)
{
	if (*index < MAX_MSG - 1)
	{
		s[*index] = c;
		(*index)++;
	}
	if (c == '\0' || *index >= MAX_MSG - 1)
	{
		write(2, s, *index);
		*index = 0;
		g_current_client = 0;
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		// printf("sending SIGUSR1 (bit): %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
		// printf("sent SIGUSR1 (bit): %d\n", info->si_pid);
	}
}

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		count = 0;
	static char		c = 0;
	static char		s[MAX_MSG];
	static int		index = 0;

	(void)ucontext;
	// printf("pid: %d\n", info->si_pid);
	if (g_current_client && info->si_pid != g_current_client)
	{
		// printf("sending SIGUSR2: %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR2);
		// printf("sent SIGUSR2: %d\n", info->si_pid);
		return ;
	}
	g_current_client = info->si_pid;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	count++;
	if (count == 8)
	{
		send_char(c, s, &index, info);
		count = 0;
		c = 0;
	}
	else
	{
		// printf("sending SIGUSR1 (received full byte): %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
		// printf("sent SIGUSR1 (received full byte): %d\n", info->si_pid);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		// printf("pausing\n");
		pause();
		// printf("ending pause\n");
	}
	return (0);
}
