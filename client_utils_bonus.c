/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:05 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/05 23:44:16 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_signal_received = 0;

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		g_signal_received = 2;
		write(1, "Final acknowledgment received from server.\n", 43);
	}
	else if (sig == SIGUSR2)
	{
		g_signal_received = 1;
	}
}

void	send_bit(int pid, char bit)
{
	int	result;
	int	timeout;

	g_signal_received = 0;
	if (bit == '0')
		result = kill(pid, SIGUSR1);
	else
		result = kill(pid, SIGUSR2);
	if (result == -1)
	{
		write(2, "Error: Failed to send signal to server\n", 38);
		exit(1);
	}
	timeout = 0;
	while (g_signal_received == 0 && timeout < 500)
	{
		usleep(500);
		timeout++;
	}
	if (timeout >= 500)
	{
		write(2, "Error: No acknowledgment from server\n", 37);
		exit(1);
	}
	usleep(1000);
}

void	send_char(int pid, unsigned char c)
{
	int		i;
	char	bit;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			bit = '1';
		else
			bit = '0';
		send_bit(pid, bit);
		i++;
		usleep(500);
	}
	usleep(5000);
}

void	ft_putnbr(int n)
{
	char	digit;

	if (n >= 10)
		ft_putnbr(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
