#include "../../includes/minishell.h"

void fill_heredocs(t_data *data, t_exec *exec)
{
	int i;
	char *line;
	char *delim;
	int fulllen;
	char *temp;
	int heredoc_file;

	fulllen = 0;
	heredoc_file = 0;
	(void)data;
	temp = NULL;
	delim = NULL;
	line = NULL;
	i = 0;
	while(i < exec->heredoc->numheredoc)
	{
		delim = exec->heredoc->delims[i];
		line = readline("heredoc> ");
		while (ft_strncmp(line, delim, ft_strlen(delim)) != 0)
		{
			fulllen = ft_strlen(line) + ft_strlen(exec->heredoc->stuff) + 2;
			temp = calloc(sizeof(char *), fulllen);
			ft_strlcpy(temp, exec->heredoc->stuff, fulllen);
			ft_strlcat(temp, line, fulllen);
			ft_strlcat(temp, "\n", fulllen);
			if (exec->heredoc->stuff != NULL)
				free(exec->heredoc->stuff);
			exec->heredoc->stuff = temp;
			free(line);	
			line = readline("heredoc> ");
		}
		i++;
	}
	heredoc_file = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(heredoc_file, exec->heredoc->stuff, ft_strlen(exec->heredoc->stuff));
	close(heredoc_file);
	heredoc_file = open(".temp", O_RDONLY);
	dup2(heredoc_file, 0);
}