/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 06:37:05 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/03 06:44:32 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define _POSIX_C_SOURCE 200809L // Docker specific
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	count = 0;
	static char		c = 0;

	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	count++;
	if (count == 8)
	{
		write (1, &c, 1);
		count = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction	s_sa;
	
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = sig_handler;
	sigemptyset(&s_sa.sa_mask);  
	sigaddset(&s_sa.sa_mask, SIGUSR1);
	sigaddset(&s_sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
