/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/09 23:38:38 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_var(t_list *var_to_del)
{
	free(((t_var*)var_to_del->content)->var_name);
	free(((t_var*)var_to_del->content)->var_value);
	free(var_to_del->content);
	free(var_to_del);
}

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
	size_t	len;
	int	i;

	i = 1;
	len = ft_strlen(tokens[1]);
	while(tokens[i] != NULL)
	{
		new_var = malloc(sizeof(t_var));
		new_var->var_name = ft_strdup(ft_strtok(tokens[i], "="));
		if (ft_strlen(new_var->var_name) == len)
		{
			printf("Error\n");
			i++;
			continue ;
		}
		new_var->var_value = ft_strdup(ft_strtok(NULL, "="));
		new_lst_el = ft_lstnew(new_var);
		old_var = ft_lst_remove(&data->vars, (void *)new_var, ft_cmp);
		if (old_var)
			free_var(old_var);
		ft_lstadd_back(&data->vars, new_lst_el);
		//printf("%s == %s\n", ((t_var *)new_lst_el->content)->var_name, ((t_var *)new_lst_el->content)->var_value);
		i++;
	}
}

void	ft_unset(t_data *data, char **tokens)
{
	t_var	new_var;
	t_list	*deleted_var;
	int	i;

	i = 1;
	while(tokens[i] != NULL)
	{
		new_var.var_name = tokens[i];
		//printf("before%s = %s\n", ((t_var *)data->vars[0].content)->var_name, ((t_var *)data->vars[0].content)->var_value);
		deleted_var = ft_lst_remove(&data->vars, (void *)&new_var, ft_cmp);
		//printf("after%s = %s\n", ((t_var *)data->vars[0].content)->var_name, ((t_var *)data->vars[0].content)->var_value);
		if (deleted_var == NULL)
		{
			free(deleted_var);
			break ;
		}
		i++;
	}
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
	else if (!ft_strncmp(tokens[0], "unset", 6))
	{
		ft_unset(data, tokens);
		return (1);
	}
	return (0);
}
