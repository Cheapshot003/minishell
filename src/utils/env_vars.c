/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:57:08 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/13 09:57:12 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*init_env_vars(char **environ)
{
	int		i;
	t_var	*new_var;
	t_list	*result_list;
	t_list	*new_lst_el;
	char	*var_value;

	result_list = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		new_var = malloc(sizeof(t_var));
		new_var->var_name = ft_strdup(strtok(environ[i], "="));
		var_value = strtok(NULL, "=");
		if (var_value != NULL)
			var_value = ft_strdup(var_value);
		new_var->var_value = var_value;
		new_lst_el = ft_lstnew(new_var);
		ft_lstadd_back(&result_list, new_lst_el);
		i++;
	}
	return (result_list);
}

char *env_var_to_str(t_var *var)
{
	char	*env_var_str;

	env_var_str = malloc(
			ft_strlen(var->var_name) + ft_strlen(var->var_value) + 2);
	env_var_str[0] = '\0';
	ft_strlcat(env_var_str, var->var_name, ft_strlen(var->var_name) + 1);
	ft_strlcat(env_var_str, "=", ft_strlen(var->var_name) + 2);
	if (var->var_value != NULL)
		ft_strlcat(env_var_str, var->var_value,
			ft_strlen(var->var_name) + 1 + ft_strlen(var->var_value) + 1);
	
	return (env_var_str);
}

char	**get_env_vars_array(t_data *data)
{
	int		vars_len;
	char	**env_vars;
	t_list	*current;
	int		i;

	vars_len = ft_lstsize(data->vars);
	current = data->vars;
	i = 0;
	env_vars = malloc((vars_len + 1) * sizeof(char *));
	while (current != NULL)
	{
		env_vars[i] = env_var_to_str((t_var *)current->content);
		i++;
		current = current->next;
	}
	env_vars[i] = NULL;
	return (env_vars);
}

void	free_lst(t_data *data)
{
	t_var	*temp;
	t_list	*temp1;
	t_list	*lst;

	lst = data->vars;
	while (lst != NULL)
	{
		temp = (t_var *)lst->content;
		temp1 = lst;
		free(temp->var_name);
		free(temp->var_value);
		free(temp1->content);
		lst = lst->next;
		free(temp1);
	}
	rl_clear_history();
}
