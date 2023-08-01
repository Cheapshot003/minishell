/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:31:25 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/07/31 15:33:00 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/history.h>
# include "/usr/include/readline/readline.h"
# include "/usr/include/readline/history.h"
# include "libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>

typedef struct s_data{
	char	*working_dir;
	char	*path_env;
}	t_data;

int		counttoken(char *str, char delim);
char	**gettokens(char *input);
void	execute(char **tokens, t_data *data);
void	intHandler(int lol);
int		internalCommand(char **tokens);
char	*getPrompt(char *working_dir);
char	*find_path(char *program, t_data *data);
void	fill_path(t_data *data);

#endif
