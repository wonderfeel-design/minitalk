/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:05 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/06 18:26:22 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int pid, char bit)
{
	int	result;

	if (bit == '0')
		result = kill(pid, SIGUSR1);
	else
		result = kill(pid, SIGUSR2);
	if (result == -1)
	{
		write(2, "Error: Failed to send\n", 21);
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
	}
	usleep(1000);
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
