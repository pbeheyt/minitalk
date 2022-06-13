/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:47 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/06/13 06:07:58 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int g_signal_received;

static void signal_handler(int i)
{
    (void)i;
    g_signal_received = 1;
}

static int  check_input(int ac, char **av)
{
    int     i;
    char    *pid_client;
    char    *base;

    pid_client = av[1];
    base = "0123456789";

    if (ac != 3)
    {
        ft_putstr_fd("Error : not enough arguments\n", 1);
        return(0);
    }
    i = -1;
    while (pid_client[++i])
    {
        if (!ft_strchr(base, pid_client[i]))
        {
            ft_putstr_fd("Error : unvalid PID\n", 1);
            return(0);
        }
    }
    return (1);
}

static void send_input(unsigned char c, int pid_client)
{
    int i;
    int signal;
    
    i = 8;
    while(i--)
    {
        g_signal_received = 0;
        signal = c & (1 << i);
        if (signal)
            kill(pid_client,SIGUSR1);
        else
            kill(pid_client, SIGUSR2);
        while (!g_signal_received)
            pause();
    }
}

int main(int ac, char **av)
{
    int i;
    int     pid_client;
    char    *input;
    
    if (!check_input(ac, av))
        return (0);
    signal(SIGUSR1, signal_handler);
    pid_client = ft_atoi(av[1]);
    input = av[2];
    i = -1;
    while (input[++i])
        send_input(input[i], pid_client);
    send_input(0, pid_client);
    return (1);
}