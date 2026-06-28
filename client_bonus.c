/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:05 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/27 13:57:23 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	wait_for_acknowledgment(void)
{
	int	timeout;

	timeout = 0;
	write(1, "Waiting for server acknowledgment...\n", 37);
	while (g_signal_received != 2 && timeout < 1000)
	{
		usleep(1000);
		timeout++;
	}
	if (g_signal_received == 2)
		write(1, "Message sent and acknowledged by server!\n", 41);
	else
		write(2, "Error: No acknowledgment received from server\n", 46);
}

static void	send_message(int pid, char *message)
{
	int	i;
	int	msg_len;

	i = 0;
	msg_len = 0;
	while (message[msg_len] != '\0')
		msg_len++;
	write(1, "Buffering message...\n", 21);
	write(1, "Sending message (", 17);
	ft_putnbr(msg_len);
	write(1, " bytes)...\n", 11);
	while (message[i] != '\0')
	{
		send_char(pid, (unsigned char)message[i]);
		i++;
	}
	send_char(pid, '\0');
	wait_for_acknowledgment();
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		write(2, "Usage: ./client <server_pid> <message>\n", 39);
		return (1);
	}
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
	{
		write(2, "Error: sigaction failed\n", 25);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(2, "Error: Invalid PID\n", 19);
		return (1);
	}
	send_message(pid, argv[2]);
	return (0);
}
