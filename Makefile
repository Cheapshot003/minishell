SRCS = ./src/main.c ./src/utils.c ./src/exec.c
COMP = gcc
FLAGS = -Wall -Werror -Wextra -lncurses -g -lreadline
OBJS = main.o utils.o exec.o

$(NAME):
	minishell

minishell: $(OBJS)
	$(COMP) $(OBJS) $(FLAGS) -o minishell

$(OBJS): $(SRCS)
	$(COMP)  -c $(SRCS) $(FLAGS)

clean:
	rm -rf *.o
fclean:
	rm -rf *.o
	rm -rf minishell

re: fclean minishell
