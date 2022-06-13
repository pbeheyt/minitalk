/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/06/13 05:40:07 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_data g_data;

void    print_pid()
{
    g_data.pid_server = getpid();
    ft_putstr_fd("PID: ", 1);
    ft_putnbr_fd(g_data.pid_server, 1);
    ft_putchar_fd('\n', 1);
}


void    print_str(void)
{
    // printf("%c\n", g_data.char_received);
    g_data.output = ft_strjoin(g_data.output, g_data.char_received);
    if (g_data.char_received == 0)
    {
        ft_putstr_fd(g_data.output, 1);
        ft_putchar_fd('\n', 1);
        free(g_data.output);
        return ;
    }
    g_data.char_received = 0;
    g_data.bit_received = 0;
}

void    signal_handler(int signal, siginfo_t *siginfo, void *context)
{
    (void)context;
    g_data.pid_client = siginfo->si_pid;
    if (signal == SIGUSR1 && g_data.bit_received <= 7)
        g_data.char_received |= (1 << (7 - g_data.bit_received++));
    if (signal == SIGUSR2 && g_data.bit_received <= 7)
        g_data.char_received &= ~(1 << (7 - g_data.bit_received++));
    if (g_data.bit_received == 8)
        print_str();
    kill(g_data.pid_client, SIGUSR1);

}
int main(int ac, char **av)
{
    struct sigaction    sa;
    
    (void)ac;
    (void)av;
    g_data.signal_received = 0;
    g_data.bit_received = 0;
    g_data.output = malloc(sizeof(char));
    g_data.output[0] = 0;
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
    print_pid();
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
    {
        if (g_data.signal_received == 1)
        {
            // printf("cc");
            print_str();
        }
        usleep(100);
    }
    return (1);
}