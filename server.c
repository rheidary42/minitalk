/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 06:37:05 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/23 19:19:38 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf/libftprintf.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_char(char *s, char c)
{
	int		i;
	char	*new;
	if (!s)
	{
		new = malloc(2);
		if (!new)
			return (NULL);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	new = malloc(ft_strlen(s) + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(s);
	return (new);
}

void	send_char(char c, char **s, siginfo_t *info)
{
	char	*temp;

	temp = ft_strjoin_char(*s, c);
	if (!temp)
	{
		free(*s);
		exit(EXIT_FAILURE);
	}
	*s = temp;
	if (c == '\0')
	{
		write(1, *s, ft_strlen(*s));
		free(*s);
		*s = NULL;
		kill(info->si_pid, SIGUSR2);
	}
	else
		kill(info->si_pid, SIGUSR1);
}

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		count = 0;
	static char		c = 0;
	static char		*s = NULL;

	(void)ucontext;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	count++;
	if (count == 8)
	{
		send_char(c, &s, info);
		count = 0;
		c = 0;
	}
	else
		kill(info->si_pid, SIGUSR1);
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
		pause();
	return (0);
}
