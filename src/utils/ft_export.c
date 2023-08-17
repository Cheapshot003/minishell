/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_print_env_vars(t_list *vars)
{
	t_list	*current;
	t_var	*current_var;

	current = vars;
	while (current != NULL)
	{
		current_var = (t_var *)current->content;
		printf("declare -x %s=\"", current_var->var_name);
		if (current_var->var_value != NULL)
			printf("%s", current_var->var_value);
		printf("\"\n");
		current = current->next;
	}
}

void	export_var(t_data *data, char *var_token, int *exit_status)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strtok(var_token, "=");
	if (var_name == NULL || check_identifier(var_name) == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(var_token, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*exit_status = 1;
	}
	else
	{
		var_name = ft_strdup(var_name);
		var_value = ft_strtok(NULL, "=");
		if (var_value != NULL)
			var_value = ft_strdup(var_value);
		add_or_replace_var(&data->vars, var_name, var_value);
	}
}

int	ft_export(t_data *data, char **tokens)
{
	int		exit_status;
	int		i;

	if (getarrlen(tokens) == 1)
		export_print_env_vars(data->vars);
	i = 1;
	exit_status = 0;
	while (tokens[i] != NULL)
	{
		export_var(data, tokens[i], &exit_status);
		i++;
	}
	return (exit_status);
}
