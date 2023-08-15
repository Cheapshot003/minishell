/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_pwd_and_old(t_data *data)
{
	char	*old_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd  == NULL)
	{
		perror("Getcwd error\n");
		exit(1);
	}
	old_pwd = ft_strdup(get_env_var_value(data, "PWD"));
	add_or_replace_var(&data->vars, ft_strdup("PWD"), pwd);
	add_or_replace_var(&data->vars, ft_strdup("OLDPWD"), old_pwd);
}

int	ft_cd(char **tokens, t_data *data)
{
	char	*cd_path;

	cd_path = tokens[1];
	if (getarrlen(tokens) == 1)
		cd_path = get_env_var_value(data, "HOME");
	else if (getarrlen(tokens) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(cd_path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cd_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	change_pwd_and_old(data);
	return (0);
}