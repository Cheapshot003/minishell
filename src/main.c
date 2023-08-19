/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/19 09:37:04 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_received_signal;

char	*get_prompt(char *working_dir)
{
	char	*prompt;

	prompt = malloc(strlen(working_dir) + 3);
	prompt[0] = '\0';
	ft_strlcat(prompt, working_dir, strlen(working_dir) + 1);
	ft_strlcat(prompt, "$ ", strlen(working_dir) + 3);
	rl_set_prompt(prompt);
	free(working_dir);
	return (prompt);
}

void	readline1(void)
{
	char	*temp;

	temp = readline(NULL);
	printf("\n");
	free(temp);
	temp = readline(NULL);
	printf("\n");
	free(temp);
}

void	free_data(t_data *data, char *line)
{
	free_t_cmd_list(data->cmd_head);
	free_t_exec_list(data->exec_head);
	if (data->exit_str != NULL)
	{
		free(data->exit_str);
		data->exit_str = NULL;
	}
	if (data->flag)
		readline1();
	data->cmd_head = NULL;
	data->exec_head = NULL;
	data->append_redirection = 0;
	data->builtin = 0;
	data->delim = NULL;
	data->input_redirection = 0;
	data->flag = 0;
	if (line)
	{
		free(line);
		line = NULL;
	}
}

char	*main1(char **argv, t_data *data)
{
	char	*prompt;
	char	*line;

	line = NULL;
	(void)argv;
	data->working_dir = getcwd(NULL, 0);
	if (data->working_dir == NULL)
	{
		perror("Getcwd error\n");
		exit(1);
	}
	prompt = get_prompt(data->working_dir);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
	{
		printf("exit\n");
		return (NULL);
	}
	if (line[0] == '\0')
		data->skip = 1;
	if (line && *line)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	data = *(init_data(&data));
	(void) argc;
	init_signals();
	data.vars = init_env_vars(envp);
	g_received_signal = 0;
	using_history();
	while (data.exit == 0)
	{
		if (g_received_signal != 0)
			continue ;
		signal(SIGQUIT, SIG_IGN);
		line = main1(argv, &data);
		if (line == NULL)
			break ;
		tokenize(line, &data);
		execute1(&data, data.exec_head);
		free(data.path_args);
		data.skip = 0;
		free_data(&data, line);
	}
	free_lst(&data);
	return (data.exit_arg);
}
