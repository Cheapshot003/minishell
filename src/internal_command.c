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

int add_or_replace_var(t_list **lst, char *var_name, char *var_value, unsigned int token_len)
{
	t_var *new_var;
	t_list *new_lst_el;
	t_list *old_var;

	new_var = malloc(sizeof(t_var));
	new_var->var_name = var_name;
	if (ft_strlen(new_var->var_name) == token_len)
	{
		free(new_var);
		return (1);
	}
	new_var->var_value = var_value;
	new_lst_el = ft_lstnew(new_var);
	old_var = ft_lst_remove(lst, (void *)new_var, ft_cmp);
	if (old_var)
		free_var(old_var);
	ft_lstadd_back(lst, new_lst_el);
	return (0);
}

void	ft_export(t_data *data, char **tokens)
{
	char *var_name;
	char *var_value;
	size_t	len;
	int	i;

	i = 1;
	len = ft_strlen(tokens[1]);
	while(tokens[i] != NULL)
	{
		var_name = ft_strdup(ft_strtok(tokens[i], "="));
		var_value = ft_strdup(ft_strtok(NULL, "="));
		if (add_or_replace_var(&data->vars, var_name, var_value, len))
		{
			printf("Error\n");
			free(var_name);
			free(var_value);
		}

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

void	print_env_vars(t_list *lst)
{
	while(lst != NULL)
		printf("%s=%s\n", ((t_var*)lst->content)->var_name, ((t_var*)lst->content)->var_value);
		lst = lst->next;
}

void	ft_env(t_data *data, char **tokens)
{
	t_list *command_env;
	t_list *current;
	t_list *current_copy;
	t_list *previous_current_copy;
	t_var *current_var;

	if(ft_strlen(tokens) < 2)
		print_env_vars(data->vars);
	current = data->vars;
	previous_current_copy = NULL;
	command_env = NULL;
	while (current != NULL)
	{
		current_var = (t_var *)current->content;
		// copy
		t_var *current_var_copy = malloc(sizeof(t_var));
		current_var_copy->var_name = current_var->var_name;
		current_var_copy->var_value = current_var->var_value;
		current_copy = malloc(sizeof(t_list));
		current_copy->content = current_var_copy;
		current_copy->next = NULL;
		if (previous_current_copy != NULL)
		{
			// non-first element
			previous_current_copy->next = current_copy;
		} else {
			// first element
			command_env = current_copy;
		}
		previous_current_copy = current_copy;
		current = current->next;
	}

	// apply new vars
	int current_token = 1;
	char *var_name;
	char *var_value;
	int token_len;
	while (1)
	{
		if (tokens[current_token] == NULL)
		{
			print_env_vars(command_env);
			break;
		}
		token_len = ft_strlen(tokens[current_token]);
		var_name = ft_strtok(tokens[current_token], "=");
		var_value = ft_strtok(NULL, "=");
		if (add_or_replace_var(&command_env, var_name, var_value, token_len))
			break;
		current_token++;
	}

	t_list *original_env = data->vars;
	data->vars = command_env;
	execute(&tokens[current_token], data);
	data->vars = original_env;

	// remove env copy
	current = command_env;
	t_list *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
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
	else if (!ft_strncmp(tokens[0], "env", 4))
	{
		ft_env(data, tokens);
		return (1);
	}
	return (0);
}
