# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekakhmad <ekakhmad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 14:29:59 by ekakhmad          #+#    #+#              #
#    Updated: 2025/09/27 14:16:44 by ekakhmad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT_SRC = client.c client_utils.c
SERVER_SRC = server.c

CLIENT_BONUS_SRC = client_bonus.c client_utils_bonus.c
SERVER_BONUS_SRC = server_bonus.c server_utils_bonus.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(CLIENT_OBJ)

$(NAME_SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(SERVER_OBJ)

$(NAME_CLIENT_BONUS): $(CLIENT_BONUS_OBJ)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(CLIENT_BONUS_OBJ)

$(NAME_SERVER_BONUS): $(SERVER_BONUS_OBJ)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(SERVER_BONUS_OBJ)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)  $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all
rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus
