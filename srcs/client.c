/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:47 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/06/13 05:01:43 by pbeheyt          ###   ########.fr       */
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
    char    *pid;
    char    *base;

    pid = av[1];
    base = "0123456789";

    if (ac != 3)
    {
        ft_putstr_fd("Error : not enough arguments\n", 1);
        return(0);
    }
    i = -1;
    while (pid[++i])
    {
        if (!ft_strchr(base, pid[i]))
        {
            ft_putstr_fd("Error : unvalid PID\n", 1);
            return(0);
        }
    }
    return (1);
}

static void send_input(unsigned char c, int pid)
{
    int i;
    int signal;
    
    i = 8;
    while(i--)
    {
        g_signal_received = 0;
        signal = c & (1 << i);
        if (signal)
            kill(pid,SIGUSR1);
        else
            kill(pid, SIGUSR2);
        while (!g_signal_received)
            pause();
    }
}

int main(int ac, char **av)
{
    int     pid;
    char    *input;
    
    if (!check_input(ac, av))
        return (0);
    signal(SIGUSR1, signal_handler);
    pid = ft_atoi(av[1]);
    input = av[2];
    while (*input)
    {
        send_input(*input, pid);
        input++;
    }    
    send_input(0, pid);
    return (1);
}