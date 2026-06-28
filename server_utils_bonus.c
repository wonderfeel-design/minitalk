/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:11 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/05 23:46:12 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putnbr(int n)
{
	char	digit;

	if (n >= 10)
		ft_putnbr(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);
}

void	process_complete_char(char *buffer, int *buf_index,
		unsigned char character)
{
	extern pid_t	g_client_pid;

	if (character == '\0')
	{
		write(1, buffer, *buf_index);
		write(1, "\n", 1);
		*buf_index = 0;
		if (g_client_pid > 0)
		{
			kill(g_client_pid, SIGUSR1);
			write(1, "Message received and acknowledged!\n", 35);
		}
	}
	else if (*buf_index < BUFFER_SIZE - 1)
	{
		buffer[(*buf_index)++] = character;
	}
}

void	process_bit(int sig, unsigned char *character, int bit_index)
{
	extern pid_t	g_client_pid;

	if (sig == SIGUSR1)
		*character &= ~(1 << bit_index);
	else if (sig == SIGUSR2)
		*character |= (1 << bit_index);
	if (g_client_pid > 0 && kill(g_client_pid, SIGUSR2) == -1)
		write(1, "Failed to acknowledge client\n", 29);
}

void	handle_complete_byte(unsigned char *character, int *bit_index,
		char *buffer, int *buf_index)
{
	process_complete_char(buffer, buf_index, *character);
	*bit_index = 0;
	*character = 0;
	usleep(1000);
}
