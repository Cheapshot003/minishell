#include "../../includes/minishell.h"


int	execute1(t_data *data, t_exec *exec_head)
{
	t_exec *current_exec;

	current_exec = exec_head;

	while (current_exec && current_exec->path)
	{
		fork_exec(data, current_exec);
		current_exec = current_exec->next;
	}
	return (0);
}

int fork_exec(t_data *data, t_exec *exec)
{
	pid_t pid;
	int	input_fd;
	int output_fd;

	exec->path[0] = expand_path(exec->path[0], data);
	if (data->builtin == 1)
	{
		data->builtin = 0;
		data->arg_count = getarrlen(exec->path);
		internal_command(exec->path, data);
		return (0);
	}
	int vars_len = 0;
	t_list *current = data->vars;
	while (current != NULL)
	{
			vars_len++;
			current = current->next;
	}
	char **env_vars = malloc((vars_len + 1) * sizeof(char *)); // +1 for NULL at the end
	current = data->vars;
	int i = 0;
	while (current != NULL)
	{
		t_var *var = (t_var *)current->content;
		char *env_var_str = malloc(ft_strlen(var->var_name) + ft_strlen(var->var_value) + 2); // 1 for '=', 1 for '\0'
		env_var_str[0] = '\0';
		ft_strlcat(env_var_str, var->var_name, ft_strlen(var->var_name) + 1);
		ft_strlcat(env_var_str, "=", ft_strlen(var->var_name) + 2);
		ft_strlcat(env_var_str, var->var_value, ft_strlen(var->var_name) + 1 + ft_strlen(var->var_value) + 1);
		env_vars[i] = env_var_str;
		i++;
		current = current->next;
	}
  env_vars[i] = NULL;
	pid = fork();
	input_fd = 0;
	output_fd = 1;
	if (pid == -1)
	{
		perror("Fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (exec->input_redirection == 1)
		{
			input_fd = open(exec->input_file, O_RDONLY);
			dup2(input_fd, 0);
			close(input_fd);
		}
		if (exec->output_redirection == 1)
		{
			output_fd = open(exec->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(output_fd, 1);
			close(output_fd);
		}
		execve(exec->path[0], exec->path, env_vars);
		perror("Exec failed\n");
		return (1);
	}
	else
	{
		waitpid(pid, &(data->exit_status), 0);
		i--;
		while (i > 0)
		{
				free(env_vars[i]);
				i--;
		}
		free(env_vars);
	}

	return (0);
}

int	containsslash(char *path)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '\\')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int isbuiltin(char *path)
{
	if (!ft_strncmp(path, "cd", 3))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "exit", 5))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "pwd", 4))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "echo", 5))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "export", 7))
	{
		return (1);
	}
	else if (!ft_strncmp(path, "unset", 6))
	{
		return (1);
	}
	return (0);
}
char *expand_path(char *path, t_data *data)
{
	if (containsslash(path) == 1)
	{
		return(path);
	}
	if (isbuiltin(path) == 1)
	{
		data->builtin = 1;
		return(path);
	}
	else
	{
		return(find_path(path, data));
	}
}
