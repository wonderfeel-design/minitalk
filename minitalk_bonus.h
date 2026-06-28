/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:05 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/06 15:53:46 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

# define BUFFER_SIZE 4096

extern int		g_signal_received;
extern pid_t	g_client_pid;

void	signal_handler(int sig);
void	send_bit(int pid, char bit);
void	send_char(int pid, unsigned char c);
int		ft_atoi(const char *str);
void	ft_putnbr(int n);
void	process_complete_char(char *buffer, int *buf_index,
			unsigned char character);
void	process_bit(int sig, unsigned char *character, int bit_index);
void	handle_complete_byte(unsigned char *character, int *bit_index,
			char *buffer, int *buf_index);

#endif
