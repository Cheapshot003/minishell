
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void copy_env_vars(t_list **dest, t_list *src)
{
	t_var *current_var;
	t_var *current_var_copy;
	t_list *current_copy;
	t_list *previous_current_copy;
	t_list *current;

	previous_current_copy = NULL;
	current = src;
	while (current != NULL)
	{
		current_var = (t_var *)current->content;
		current_var_copy = malloc(sizeof(t_var));
		current_var_copy->var_name = current_var->var_name;
		current_var_copy->var_value = current_var->var_value;
		current_copy = malloc(sizeof(t_list));
		current_copy->content = current_var_copy;
		current_copy->next = NULL;
		if (previous_current_copy != NULL)
			previous_current_copy->next = current_copy;
		else
			*dest = current_copy;
		previous_current_copy = current_copy;
		current = current->next;
	}
}

void	print_env_vars(t_list *lst)
{
	while(lst != NULL)
	{
		printf("%s=%s\n", ((t_var*)lst->content)->var_name, ((t_var*)lst->content)->var_value);
		lst = lst->next;
	}
}

int apply_vars_from_tokens(char **tokens, t_list **vars)
{
	int current_token;
	char *var_name;
	char *var_value;
	int token_len;

	current_token = 1;
	while (1)
	{
		if (tokens[current_token] == NULL)
		{
			print_env_vars(*vars);
			break ;
		}
		token_len = ft_strlen(tokens[current_token]);
		var_name = ft_strtok(tokens[current_token], "=");
		var_value = ft_strtok(NULL, "=");
		if (add_or_replace_var(vars, var_name, var_value, token_len))
			break ;
		current_token++;
	}
	return current_token;
}

void remove_env_copy(t_list *vars)
{
	t_list *current;

	current = vars;
	t_list *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

int	ft_env(t_data *data, char **tokens)
{
	t_list *command_env;
	int current_token;

	if(getarrlen(tokens) < 2)
	{
		print_env_vars(data->vars);
		return (0);
	}
	command_env = NULL;
	copy_env_vars(&command_env, data->vars);
	current_token = apply_vars_from_tokens(tokens, &command_env);
	t_list *original_env = data->vars;
	data->vars = command_env;
	t_exec *exec_head;
	exec_head = create_t_exec();
	exec_head->path = &tokens[current_token];
	execute1(data, exec_head);
	data->vars = original_env;
	remove_env_copy(command_env);
	return (data->exit_status);
}