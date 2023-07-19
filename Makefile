SRCS = ./src/main.c ./src/utils.c ./src/exec.c
COMP = gcc
FLAGS = -Wall -Werror -Wextra -lreadline -g
OBJS = main.o utils.o exec.o

$(NAME):
	minishell

minishell: $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) -o minishell

$(OBJS): $(SRCS)
	$(COMP) $(FLAGS) -c $(SRCS)

clean:
	rm -rf *.o
fclean:
	rm -rf *.o
	rm -rf minishell

re: fclean minishell
