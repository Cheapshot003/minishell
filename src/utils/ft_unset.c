/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	return (0);
}

int	ft_unset(t_data *data, char **tokens)
{
	t_var	new_var;
	t_list	*deleted_var;
	int	i;
	int	is_error;

	i = 1;
	is_error = 0;
	while(tokens[i] != NULL)
	{
		new_var.var_name = tokens[i];
		if (check_identifier(new_var.var_name) == 1)
		{
			is_error = 1;
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(new_var.var_name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			deleted_var = ft_lst_remove(&data->vars, (void *)&new_var, ft_cmp);
			if (deleted_var == NULL)
				free(deleted_var);
		}
		i++;
	}
	return (is_error);
}