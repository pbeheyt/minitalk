/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/06/14 01:45:19 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_data	g_data;

static	void	print_pid(void)
{
	g_data.pid_server = getpid();
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(g_data.pid_server, 1);
	ft_putchar_fd('\n', 1);
}

static	void	gather_chars_and_print_output(siginfo_t *siginfo)
{
	g_data.output = ft_strjoin(g_data.output, g_data.char_received);
	if (g_data.char_received == 0)
	{
		ft_putstr_fd(g_data.output, 1);
		ft_putchar_fd('\n', 1);
		free(g_data.output);
		kill(siginfo->si_pid, SIGUSR2);
	}
	g_data.bits_received = 0;
	g_data.char_received = 0;
}

static	void	signal_handler(int signum, siginfo_t *siginfo, void *oldact)
{
	(void)oldact;
	if (signum == SIGUSR1 && g_data.bits_received <= 7)
		g_data.char_received |= (1 << (7 - g_data.bits_received++));
	if (signum == SIGUSR2 && g_data.bits_received <= 7)
		g_data.char_received &= ~(1 << (7 - g_data.bits_received++));
	if (g_data.bits_received == 8)
		gather_chars_and_print_output(siginfo);
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)ac;
	(void)av;
	g_data.bits_received = 0;
	g_data.output = malloc(sizeof(char));
	if (!g_data.output)
		return (0);
	g_data.output[0] = 0;
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	print_pid();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (1);
}
