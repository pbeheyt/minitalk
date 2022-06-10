/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:41:40 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/06/10 06:14:45 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void    print_pid()
{
    int     pid;

    pid = getpid();
    ft_putnbr_fd(pid, 1);
    ft_putchar_fd('\n', 1);
}

void    signal_handler(int signal, t_data *data)
{
    if (signal == SIGUSR1 && data->bit_received <= 7)
        data->char_received |= (1 << (7 - data->bit_received++));
    if (signal == SIGUSR2 && data->bit_received <= 7)
        data->char_received &= ~(1 << (7 - data->bit_received++));
    data->signal_received = 1;
}

void    print_str()
{
    
}

int main(int ac, char **av)
{
    t_data data;
    
    data.signal_received = 0;
    data.bit_received = 0;
    
    print_pid();
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    while (1)
        if (data.signal_received == 1)
            print_str();
        usleep(100);
    return (1);
}