/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:52 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/15 14:58:54 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var_value(t_data *data, char *var_name)
{
	t_list *current;
	t_var *current_var;

	current = data->vars;
	data->exit_str = ft_itoa(data->exit_status);
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		return (data->exit_str);
	while (current != NULL)
	{
		current_var = (t_var *)current->content;
		if (ft_strncmp(current_var->var_name, var_name, ft_strlen(var_name)) == 0) {
				return current_var->var_value;
		}
		current = current->next;
	}
	return getenv(var_name);
}
