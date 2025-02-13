/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:06:34 by njooris           #+#    #+#             */
/*   Updated: 2025/02/13 14:22:54 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	check = 0;

void	push_char_signal(char c, int pid_serv)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid_serv, SIGUSR1);
		else
			kill(pid_serv, SIGUSR2);
		usleep(500);
		i--;
	}
}

void	push_pid(int pid_serv)
{
	int	i;
	int	pid;

	i = 31;
	pid = getpid();
	while (i >= 0)
	{
		if ((pid >> i) & 1)
			kill(pid_serv, SIGUSR1);
		else
			kill(pid_serv, SIGUSR2);
		usleep(500);
		i--;
	}
}

void	push_len_signal(char *str, int pid_serv)
{
	int	i;
	int	len;

	i = 31;
	len = ft_strlen(str);
	while (i >= 0)
	{
		if ((len >> i) & 1)
			kill(pid_serv, SIGUSR1);
		else
			kill(pid_serv, SIGUSR2);
		usleep(500);
		i--;
	}
}

void	brows_str_signal(char *str, int pid_serv)
{
	int	i;

	i = 0;
	push_pid(pid_serv);
	usleep(500);
	push_len_signal(str, pid_serv);
	usleep(500);
	while (str[i])
	{
		push_char_signal(str[i], pid_serv);
		i++;
	}
	printf("Signal envoye !\n");
}
void	signal_handler(int sig)
{
	(void)sig;
	check = 1;
}

int	main(int argc, char **argv)
{
	int	pid_serv;

	(void)argc;
	if (!argv[1] || !argv[2] || argv[3])
		return (0);
	signal(SIGUSR1, signal_handler);
	pid_serv = ft_atoi(argv[1]);
	brows_str_signal(argv[2], pid_serv);
	while (!check)
		pause();
	printf("signal recu !\n");
	return (0);
}
