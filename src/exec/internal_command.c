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

void	add_or_replace_var(t_list **lst, char *var_name, char *var_value)
{
	t_var *new_var;
	t_list *new_lst_el;
	t_list *old_var;

	new_var = malloc(sizeof(t_var));
	new_var->var_name = var_name;
	new_var->var_value = var_value;
	new_lst_el = ft_lstnew(new_var);
	old_var = ft_lst_remove(lst, (void *)new_var, ft_cmp);
	if (old_var)
		free_var(old_var);
	ft_lstadd_back(lst, new_lst_el);
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

int	ft_export(t_data *data, char **tokens)
{
	char *var_name;
	char *var_value;
	int exit_status;
	int	i;

	if (getarrlen(tokens) == 1)
		export_print_env_vars(data->vars);
	i = 1;
	exit_status = 0;
	while(tokens[i] != NULL)
	{
		var_name = ft_strtok(tokens[i], "=");
		if (var_name == NULL || check_identifier(var_name) == 1)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(tokens[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		} else
		{
			var_name = ft_strdup(var_name);
			var_value = ft_strtok(NULL, "=");
			if (var_value != NULL)
				var_value = ft_strdup(var_value);
			add_or_replace_var(&data->vars, var_name, var_value);
		}
		i++;
	}
	return (exit_status);
}

void	ft_exit(char **tokens, t_data *data)
{
	int	exit_arg;

	data->exit = 1;
	if (getarrlen(tokens) > 2)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		data->exit_arg = 1;
	}
	else if (tokens[1])
	{
		if (ft_isnum(tokens[1]) == 0)
		{
			exit_arg = ft_atoi_long(tokens[1]) % 256;
			if (exit_arg != -1)
			{
				rl_clear_history();
				data->exit_arg = exit_arg;
				printf("exit\n");
				return;
			}
		}
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(tokens[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit_arg = 2;
	} else
		printf("exit\n");
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
		data->exit_status = ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "echo", 5))
	{
		data->exit_status = ft_echo(data, tokens);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "export", 7))
	{
		data->exit_status = ft_export(data, tokens);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "unset", 6))
	{
		data->exit_status = ft_unset(data, tokens);
		return (1);
	}
	else if (!ft_strncmp(tokens[0], "env", 4))
	{
		data->exit_status = ft_env(data, tokens);
		return (1);
	}
	return (0);
}
