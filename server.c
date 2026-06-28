/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:11 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/06 18:25:48 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int n)
{
	char	digit;

	if (n >= 10)
		ft_putnbr(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);
}

static void	process_char(unsigned char c, char *buffer, int *buf_index)
{
	if (c == '\0')
	{
		write(1, buffer, *buf_index);
		write(1, "\n", 1);
		*buf_index = 0;
	}
	else if (*buf_index < BUFFER_SIZE - 1)
	{
		buffer[(*buf_index)++] = c;
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_index = 0;
	static unsigned char	character = 0;
	static char				buffer[BUFFER_SIZE];
	static int				buf_index = 0;

	(void)context;
	(void)info;
	if (sig == SIGUSR1)
		character &= ~(1 << bit_index);
	else if (sig == SIGUSR2)
		character |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		process_char(character, buffer, &buf_index);
		bit_index = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		return (1);
	}
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
