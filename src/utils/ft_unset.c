/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/17 17:38:47 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	return (0);
}

void	free_env_var(t_list **lst)
{
	t_var	*var;

	var = (t_var *)(*lst)->content;
	free(var->var_name);
	free(var->var_value);
	free(var);
	free(*lst);
}

void	handle_unset_token(t_data *data, char *token, int *is_error)
{
	t_var	new_var;
	t_list	*deleted_var;

	new_var.var_name = token;
	if (check_identifier(new_var.var_name) == 1)
	{
		*is_error = 1;
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(new_var.var_name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		deleted_var = ft_lst_remove(&data->vars, (void *)&new_var, ft_cmp);
		if (deleted_var != NULL)
			free_env_var(&deleted_var);
	}
}

int	ft_unset(t_data *data, char **tokens)
{
	int		i;
	int		is_error;

	i = 1;
	is_error = 0;
	while (tokens[i] != NULL)
	{
		handle_unset_token(data, tokens[i], &is_error);
		i++;
	}
	return (is_error);
}
