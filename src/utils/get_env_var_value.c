/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:52 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 17:53:39 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var_value(t_data *data, char *var_name)
{
	t_list	*current;
	t_var	*current_var;

	current = data->vars;
	data->exit_str = ft_itoa(data->exit_status);
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (data->exit_str);
	if (data->exit_str != NULL)
		free(data->exit_str);
	data->exit_str = NULL;
	while (current != NULL)
	{
		current_var = (t_var *)current->content;
		if (ft_strncmp(current_var->var_name,
				var_name, ft_strlen(current_var->var_name)) == 0)
			return (current_var->var_value);
		current = current->next;
	}
	return (getenv(var_name));
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
