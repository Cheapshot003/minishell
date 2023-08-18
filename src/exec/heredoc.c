/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 11:23:17 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_loop(t_exec *exec, char *line)
{
	int		fulllen;
	char	*temp;

	fulllen = ft_strlen(line) + ft_strlen(exec->heredoc->stuff) + 2;
	temp = calloc(sizeof(char *), fulllen);
	ft_strlcpy(temp, exec->heredoc->stuff, fulllen);
	ft_strlcat(temp, line, fulllen);
	ft_strlcat(temp, "\n", fulllen);
	if (exec->heredoc->stuff != NULL)
		free(exec->heredoc->stuff);
	exec->heredoc->stuff = temp;
	free(line);
	return (0);
}

void	fill_heredocs(t_data *data, t_exec *exec)
{
	int		i;
	char	*line;
	int		heredoc_file;

	heredoc_file = 0;
	(void)data;
	line = NULL;
	i = 0;
	while (i < exec->heredoc->numheredoc)
	{
		line = readline("heredoc> ");
		while (ft_strncmp(line, exec->heredoc->delims[i],
				ft_strlen(exec->heredoc->delims[i])) != 0)
		{
			heredoc_loop(exec, line);
			line = readline("heredoc> ");
		}
		if (line != NULL)
			free(line);
		i++;
	}
	heredoc_file = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(heredoc_file, exec->heredoc->stuff, ft_strlen(exec->heredoc->stuff));
	close(heredoc_file);
}
