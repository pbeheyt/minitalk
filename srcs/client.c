/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:47 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/06/10 04:49:14 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "client.h"

static int  check_input(int ac, char **av)
{
    int     i;
    char    *input;
    char    *base;

    input = av[1];
    base = "123456789";

    if (ac != 3)
    {
        ft_putstr_fd("Error : not enough arguments\n", 1);
        return(0);
    }
    i = -1;
    while (input[++i])
    {
        if (!ft_strchr(base, input[i]))
        {
            ft_putstr_fd("Error : unvalid PID\n", 1);
            return(0);
        }
    }
    return (1);
}

void send_input(unsigned char c, int pid)
{
    int i;
    int signal;
    
    i = -1;
    while(++i <= 7)
    {
        signal = c & (1 << 7);
        if (signal)
            kill(pid,SIGUSR1);
        else if (!signal)
            kill(pid, SIGUSR2);
        c = c >> 1;
    }
}

int main(int ac, char **av)
{
    int     pid;
    char    *input;
    
    if (!check_input(ac, av))
        return (0);
    pid = ft_atoi(av[1]);
    if (pid <= 0)
    {
        ft_putstr_fd("Error : unvalid PID\n", 1);
        return (0);
    }
    input = av[2];
    while (*input)
        send_input(*input, pid);
    return (1);
}