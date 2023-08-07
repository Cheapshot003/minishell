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

COMP = cc

CFLAGS = -Wall -Werror -Wextra -Ilibft -g

# Add -lncurses after $(OBJS) to ensure proper linking
LDFLAGS = -Llibft -l:libft.a -lreadline -lncurses

SRCS = src/main.c \
       src/utils.c \
       src/exec.c \
			 src/ft_lst_remove.c \
			 src/internal_command.c \
			 src/ft_strtok.c \
	   src/data.c

libft = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

$(NAME): $(libft) $(OBJS)
	$(COMP) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(libft):
	make -C libft && make bonus -C libft
	
all: $(NAME)

clean:
	rm -f $(OBJS) && make -C libft clean

fclean: clean
	rm -f $(NAME) && make -C libft fclean

re: fclean all
