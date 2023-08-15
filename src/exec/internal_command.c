/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_var(t_list *var_to_del)
{
	free(((t_var*)var_to_del->content)->var_name);
	free(((t_var*)var_to_del->content)->var_value);
	free(var_to_del->content);
	free(var_to_del);
}

int	add_or_replace_var(t_list **lst, char *var_name, char *var_value, unsigned int token_len)
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

void	export_print_env_vars(t_list *vars)
{
	t_list *current;
	t_var *current_var;

	current = vars;
	while (current != NULL)
	{
		current_var = (t_var *)current->content;
		printf("declare -x %s", current_var->var_name);
		if (current_var->var_value != NULL)
			printf("=\"%s\"", current_var->var_value);
		printf("\n");
		current = current->next;
	}
}

void	ft_export(t_data *data, char **tokens)
{
	char *var_name;
	char *var_value;
	size_t	len;
	int	i;

	if (getarrlen(tokens) == 1)
		export_print_env_vars(data->vars);
	i = 1;
	while(tokens[i] != NULL)
	{
		len = ft_strlen(tokens[i]);
		var_name = ft_strdup(ft_strtok(tokens[i], "="));
		var_value = ft_strtok(NULL, "=");
		if (var_value != NULL)
			var_value = ft_strdup(var_value);
		if (add_or_replace_var(&data->vars, var_name, var_value, len))
		{
			printf("Error\n");
			free(var_name);
			free(var_value);
		}
		i++;
	}
}

void	ft_exit(char **tokens, t_data *data)
{
	int	exit_arg;

	data->exit = 1;
	if (tokens[1])
	{
		if (ft_isnum(tokens[1]) == 0)
		{
			exit_arg = ft_atoi(tokens[1]);
			rl_clear_history();
			free(tokens);
			if (exit_arg >= 0 && exit_arg <= 255)
			{
				printf("exit\n");
				data->exit_arg = exit_arg;
				return ;
			}
		}
		else
			printf("exit: %s: numeric argument required\n", tokens[1]);
		return ;
	}
	printf("exit\n");
	data->exit = 1;
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
		deleted_var = ft_lst_remove(&data->vars, (void *)&new_var, ft_cmp);
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
	{
		printf("%s=%s\n", ((t_var*)lst->content)->var_name, ((t_var*)lst->content)->var_value);
		lst = lst->next;
	}
}

void	ft_env(t_data *data, char **tokens)
{
	t_list *command_env;
	t_list *current;
	t_list *current_copy;
	t_list *previous_current_copy;
	t_var *current_var;

	if(getarrlen(tokens) < 2)
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
	t_exec *exec_head;
	exec_head = create_t_exec();
	exec_head->path = &tokens[current_token];
	execute1(data, exec_head);
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
		data->exit_status = ft_cd(tokens, data);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "exit", 5))
	{
		ft_exit(tokens, data);
	}
	else if (!ft_strncmp(tokens[0], "pwd", 4))
	{
		printf("%s\n", getcwd(NULL, 0));
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "echo", 5))
	{
		data->exit_status = ft_echo(data, tokens);
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
