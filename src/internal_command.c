/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/04 07:21:57 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_data *data, char **tokens)
{
	if (data->arg_count == 2)
		printf("%s\n", tokens[1]);
	else if (data->arg_count == 3)
	{
		if (!ft_strncmp(tokens[1], "-n", 3))
			printf("%s", tokens[2]);
		else
			printf("Error\n");
	}
	else
		printf("Error\n");
}

void	ft_export(t_data *data, char **tokens)
{
	t_var	*new_var;
	t_list	*new_lst_el;
	t_list	*old_var;

	new_var = malloc(sizeof(t_var));
	new_var->var_name = ft_strdup(strtok(tokens[1], "="));
	new_var->var_value = ft_strdup(strtok(NULL, "="));
	new_lst_el = ft_lstnew(new_var);
	old_var = ft_lst_remove(&data->vars, (void *)new_var, ft_cmp);
	if (old_var)
	{
		free(((t_var*)old_var->content)->var_name);
		free(((t_var*)old_var->content)->var_value);
		free(old_var->content);
		free(old_var);
	}
	ft_lstadd_back(&data->vars, new_lst_el);
	//printf("%s = %s\n", ((t_var *)data->vars[0].content)->var_name, ((t_var *)data->vars[0].content)->var_value);
}

int	internal_command(char **tokens, t_data *data)
{
	if (!ft_strncmp(tokens[0], "cd", 3))
	{
		chdir(tokens[1]);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "exit", 5))
	{
		rl_clear_history();
		free(tokens);
		exit(0);
	}
	else if (!ft_strncmp(tokens[0], "pwd", 4))
	{
		printf("%s\n", getcwd(NULL, 0));
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "echo", 5))
	{
		ft_echo(data, tokens);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "export", 7))
	{
		ft_export(data, tokens);
		return (1);
	}
	return (0);
}
