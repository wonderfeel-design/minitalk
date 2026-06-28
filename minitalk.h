/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:05 by ekakhmad          #+#    #+#             */
/*   Updated: 2025/09/05 23:46:15 by ekakhmad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define BUFFER_SIZE 4096

void	send_bit(int pid, char bit);
void	send_char(int pid, unsigned char c);
int		ft_atoi(const char *str);
void	ft_putnbr(int n); /* Used by server to display PID */

#endif
