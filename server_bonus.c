/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:11 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/05 23:46:13 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

pid_t	g_client_pid = 0;

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_index = 0;
	static unsigned char	character = 0;
	static char				buffer[BUFFER_SIZE];
	static int				buf_index = 0;

	(void)context;
	if (info->si_pid > 0)
		g_client_pid = info->si_pid;
	process_bit(sig, &character, bit_index);
	bit_index++;
	if (bit_index == 8)
		handle_complete_byte(&character, &bit_index, buffer, &buf_index);
	else if (g_client_pid > 0)
	{
		usleep(500);
		kill(g_client_pid, SIGUSR2);
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
		pause();
	return (0);
}
