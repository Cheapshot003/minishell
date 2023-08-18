/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/16 10:45:07 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_one_path(char *path, char *program)
{
	size_t	full_path_len;
	char	*full_path;

	full_path_len = strlen(path) + 1 + strlen(program) + 1;
	full_path = ft_calloc(full_path_len, sizeof(char));
	if (full_path == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	snprintf(full_path, full_path_len, "%s/%s", path, program);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_path(char *program, t_data *data)
{
	char	*path_var;
	char	*path;
	char	*full_path;

	if (program[0] == '/' || program[0] == '.')
		return (strdup(program));
	path_var = ft_strdup(get_env_var_value(data, "PATH"));
	path = ft_strtok(path_var, ":");
	while (path)
	{
		full_path = check_one_path(path, program);
		if (full_path != NULL)
		{
			free(path_var);
			return (full_path);
		}
		path = ft_strtok(NULL, ":");
	}
	free(path_var);
	return (NULL);
}
