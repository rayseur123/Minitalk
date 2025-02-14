/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:06:39 by njooris           #+#    #+#             */
/*   Updated: 2025/02/14 14:16:20 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	char_manage(int sig, int *count_char, char *str)
{
	int			bin;
	static int	count;
	static int	val;

	bin = 0;
	val = val << 1;
	if (sig == SIGUSR1)
		bin = 1;
	if (sig == SIGUSR2)
		bin = 0;
	val += bin;
	count++;
	if (count == 8)
	{
		str[*count_char] = val;
		(*count_char)++;
		val = 0;
		count = 0;
	}
}

int	len_manage(int sig, int *count)
{
	int			bin;
	static int	val;
	int			len;

	bin = 0;
	val = val << 1;
	len = val;
	if (sig == SIGUSR1)
		bin = 1;
	if (sig == SIGUSR2)
		bin = 0;
	val += bin;
	(*count)++;
	if (*count == 32)
	{
		len = val;
		val = 0;
	}
	return (len);
}

void	reset_values(int *count, int *count_char, int *len, char **str)
{
	*count = 0;
	*count_char = 0;
	*len = 0;
	free(*str);
	*str = NULL;
}

void	signal_handler(int sig)
{
	static int	count;
	static int	count_char;
	static char	*str;
	static int	len;

	if (count < 32)
		len = len_manage(sig, &count);
	else
	{
		if (str == NULL && len != 0)
		{
			str = malloc(len + 1);
			if (!str)
				return ;
			str[len] = '\0';
		}
		char_manage(sig, &count_char, str);
	}
	if (count_char == len && str)
	{
		ft_printf("%s\n", str);
		reset_values(&count, &count_char, &len, &str);
	}
	if (count == 32 && len == 0)
		reset_values(&count, &count_char, &len, &str);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("pid : %d\n", pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
