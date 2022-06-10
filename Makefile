# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 15:08:45 by pbeheyt           #+#    #+#              #
#    Updated: 2022/06/10 02:59:48 by pbeheyt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER	= server

NAME_CLIENT	= client

SERVER_C	= server.c

CLIENT_C	= client.c 

SRC_SERVER = ${addprefix srcs/,${SERVER_C}}

SRC_CLIENT = ${addprefix srcs/,${CLIENT_C}}

HEAD		= -I libft -I include

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

OBJS_SERVER = ${SRC_SERVER:.c=.o}

OBJS_CLIENT = ${SRC_CLIENT:.c=.o}

LD_FLAG		= -L libft

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(LD_FLAG) $(OBJS_SERVER) -lft

$(NAME_CLIENT): $(OBJS_CLIENT)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(LD_FLAG) $(OBJS_CLIENT) -lft

.c.o                :
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean :
	make clean -C libft
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean : clean
	make fclean -C libft
	rm -f $(NAME_CLIENT) $(NAME_SERVER) 

re : fclean all 

.PHONY : all clean fclean re