# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otietz <otietz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 15:30:52 by ohnatiuk          #+#    #+#              #
#    Updated: 2023/08/18 15:58:15 by otietz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

COMP = cc

CFLAGS = -Wall -Werror -Wextra -Ilibft -g

# Add -lncurses after $(OBJS) to ensure proper linking
LDFLAGS = -Llibft -l:libft.a -lreadline -lncurses

SRCS = src/main.c \
    src/exec/exec.c \
		src/utils/ft_lst_remove.c \
		src/exec/internal_command.c \
		src/utils/ft_strtok.c \
		src/utils/signals.c \
		src/utils/data.c \
		src/utils/get_env_var_value.c \
		src/utils/ft_cd.c \
		src/utils/ft_echo.c \
		src/utils/ft_pwd.c \
		src/utils/ft_unset.c \
		src/utils/ft_env.c \
		src/utils/ft_export.c \
		src/utils/ft_exit.c \
		src/parser/tokenize.c \
		src/parser/expand.c \
		src/parser/parser_utils.c \
		src/parser/parse.c \
		src/utils/cmdlist.c \
		src/utils/execlist.c \
		src/utils/utils1.c \
		src/utils/env_vars.c \
		src/utils/ft_isnum.c \
		src/utils/exit_error.c \
		src/parser/parse1.c \
		src/parser/check_redirects.c \
		src/parser/fillredirects.c \
		src/exec/executor.c \
		src/utils/error.c \
		src/exec/heredoc.c \
		src/exec/builtin.c \
		src/exec/executor_2.c \
		src/parser/tokenize_1.c

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
