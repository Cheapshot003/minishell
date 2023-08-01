# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 15:30:52 by ohnatiuk          #+#    #+#              #
#    Updated: 2023/07/31 15:30:55 by ohnatiuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -Ilibft -lncurses -g -lreadline

SRCS = src/main.c \
				src/utils.c \
				src/exec.c \

libft = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

$(NAME): $(libft) $(OBJS)
				@cc $(CFLAGS) $(OBJS) -o $(NAME) -Llibft -l:libft.a

$(libft):
	make -C libft
	
all: $(NAME)

clean:
	rm -f $(OBJS) && make -C libft clean

fclean: clean
	rm -f $(NAME) && make -C libft fclean

re: fclean all
