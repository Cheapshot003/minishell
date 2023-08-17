/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:31:25 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/17 14:49:26 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/history.h>
# include "readline/readline.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_cmd{
	char					*str;
	int						i;
	struct s_cmd			*next;
	struct s_cmd			*prev;
}	t_cmd;

typedef struct s_exec{
	char	**path;
	int		input_redirection;
	int		output_redirection;
	char	*input_file;
	char	*output_file;
	int		append_redirection;
	int		pipes[2];
	struct s_heredoc *heredoc;
	struct s_exec	*next;
	struct s_exec	*prev;
}	t_exec;

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
	t_cmd	*cmd_head;
	t_list	*vars;
	char	*delim;
	int		exit_status;
	t_exec	*exec_head;
	int		builtin;
	int		exit;
	int		exit_arg;
	char	*exit_str;
	int		skip;
}	t_data;

typedef struct s_var
{
	struct s_var	*next;
	char			*var_name;
	char			*var_value;
}	t_var;

typedef struct s_heredoc
{
	int numheredoc;
	char *stuff;
	char **delims;
} t_heredoc;

void	execute(t_data *data);
int		internal_command(char **tokens, t_data *data);
char	*find_path(char *program, t_data *data);
void	setRedirects(t_data *data);
int		countargs(char **tokens, t_data *data);
int		is_special(char *token);
void	checkRedirects(char **tokens, t_data *data);
t_list	*ft_lst_remove(t_list **begin_list, void *data_ref, int (*cmp)());
int		ft_cmp(void *a, void *b);
char	*ft_strtok(char *str, const char *delim);
t_data	*init_data(t_data *data);
char	**cmdtok(char *line, t_data *data);
void	cmdlex(char **input_tokens, t_data *data);
void	tokenize(char *line, t_data *data);
char	*getnexttoken(char *line);
int		is_whitespace(char c);
void	*ft_realloc(void* ptr, size_t new_size);
void	expander(char **tokens, t_data *data);
int		is_special_char(char c);
int		is_quote(char c);
int		is_empty_string(const char* str);
char	**remove_empty_strings(char **input_tokens);
void	parse(t_data *data);
t_cmd	*getcmd(t_data *data);
void	exiterror(t_data *data, char *errmsg, int exitbit);
int		count_pipes(t_data *data);
void	getcmdlst(t_data *data, int npipes);
t_cmd	*create_t_cmd(void);
void	insert_t_cmd(t_cmd **head, t_cmd *new_cmd);
void	free_t_cmd_list(t_cmd *head);
t_cmd	*get_t_cmd_at_index(t_cmd *head, int index);
void	insert_t_cmd_at_index(t_cmd **head, t_cmd *new_cmd, int index);
t_exec	*create_t_exec(void);
void	insert_t_exec(t_exec **head, t_exec *new_cmd);
void	free_t_exec_list(t_exec *head);
t_exec	*get_t_exec_at_index(t_exec *head, int index);
void	insert_t_exec_at_index(t_exec **head, t_exec *new_cmd, int index);
char	isdouble(char *token);
t_exec	*getexecs(t_data *data);
void	fillpath(t_exec *head, t_data *data);
char	**ft_appendstr(char **dest, char *str);
int		is_redirect(char *str);
int		getarrlen(char **arr);
void	fillredirects(t_exec *head, t_data *data);
void	delete_t_cmd_at_index(t_cmd **head, int index);
int		execute1(t_data *data, t_exec *exec_head);
int		fork_exec(t_data *data, t_exec *exec, int input_fd, int output_fd);
int		expand_paths(t_data *data, t_exec *exec_head);
char	**get_env_vars_array(t_data *data);
void	free_array(void **arr);
t_list	*init_env_vars(char **environ);
int		ft_isnum(char *s);
void	handle_signal_by_child(int sig);
void	free_tok(char **tokens);
void	free_env(char **env);
void	free_lst(t_data *data);
char	*get_env_var_value(t_data *data, char *var_name);
int		ft_cd(char **tokens, t_data *data);
int		ft_pwd(void);
int		ft_unset(t_data *data, char **tokens);
int		ft_env(t_data *data, char **tokens);
int		ft_export(t_data *data, char **tokens);
int		ft_echo(t_data *data, char **tokens);
void	ft_exit(char **tokens, t_data *data);
void handle_execerr(t_data *data);
int	is_closed(char **tokens, int i, int j);
char *clear_single_quotes(char *str);
int is_closed_line(char *line, int i);
long long int	ft_atoi_long(const char *str);
int	check_identifier(char *str);
void	add_or_replace_var(t_list **lst, char *var_name, char *var_value);
void init_signals(void);
void fill_heredocs(t_data *data, t_exec *exec);
t_heredoc *get_heredoc(void);
int exec_builtins(t_data *data, t_exec *exec, int input_fd, int output_fd);
#endif
