/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:31:25 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/03 16:51:57 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/history.h>
# include "/usr/include/readline/readline.h"
# include "/usr/include/readline/history.h"
# include "../libft/libft.h"
# include <stdlib.h>
#	include <unistd.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_data{
	char	*working_dir;
	char	*path_env;
	int		arg_count;
	char	**full_tokens;
	char	**path_args;
	int		input_redirection;
	int		output_redirection;
	char	*input_file;
	char	*output_file;
	int		append_redirection;
	t_list	*vars;
}	t_data;

typedef struct s_var
{
	struct s_var *next;
	char *var_name;
	char *var_value;
} t_var;

int		counttoken(char *str, char delim);
char	**gettokens(char *input, t_data *data);
void	execute(char **tokens, t_data *data);
void	intHandler(int lol);
int		internal_command(char **tokens, t_data *data);
char	*getPrompt(char *working_dir);
char	*find_path(char *program, t_data *data);
void	fill_path(t_data *data);
void	setRedirects(t_data *data);
void	parse_tokens(char **tokens, t_data *data);
int		countargs(char **tokens, t_data *data);
int		is_special(char *token);
void	checkRedirects(char **tokens, t_data *data);
void	free_data(t_data *data);
t_list	*ft_lst_remove(t_list **begin_list, void *data_ref, int (*cmp)());
int	ft_cmp(void *a, void *b);
char	*ft_strtok(char *str, const char *delim);
#endif
