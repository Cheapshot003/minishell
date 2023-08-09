#include "../includes/minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(char **tokens, t_data *data)
{
    char *path;
    pid_t pid;

    checkRedirects(tokens, data);
    if (internal_command(tokens, data))
        return;

    char *program = tokens[0];
    char **args = tokens;
    path = find_path(program, data);
    if (path == NULL)
    {
        printf("Error\n");
        return;
    }

    // t_data vars to env var null-terminated array
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
    // Fork a child process
    pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process
        setRedirects(data);

        // Replace the last element of args with NULL (required by execve)
        execve(path, args, env_vars);
        perror("Execve failed"); // This line will only execute if execve fails
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        free(path);
        wait(NULL);
        i--;
        while (i > 0)
        {
            free(env_vars[i]);
            i--;
        }
        free(env_vars);
    }
}


void checkRedirects(char **tokens, t_data *data)
{
	int i;

	i = 1;
	data->input_redirection = 0;
	data->output_redirection = 0;
    data->append_redirection = 0;
    data->input_file = NULL;
	data->output_file = NULL;
    while(i < data->arg_count) {
		if (tokens[i] == NULL)
		{

		}
        else if (ft_strncmp(tokens[i], "<", ft_strlen(tokens[i])) == 0) {
            data->input_redirection = 1;
            data->input_file = tokens[i + 1];
        } else if (ft_strncmp(tokens[i], ">", ft_strlen(tokens[i])) == 0) {
            data->output_redirection = 1;
            data->output_file = tokens[i + 1];
        } else if (ft_strncmp(tokens[i], ">>", ft_strlen(tokens[i])) == 0) {
			data->output_redirection = 1;
			data->append_redirection = 1;
			data->output_file = tokens[i + 1];
		} else if (ft_strncmp(tokens[i], "<<", ft_strlen(tokens[i])) == 0) {
            data->append_redirection = 1;
            data->delim = tokens[i+1];
        }
		i++;
    }
}

void setRedirects(t_data *data)
{
	int fd_output;
	int	fd_input;
    char *content;
    char *line;

	// If inpus redirection is present, open the file and duplicate file descriptor
    line = NULL;
    content = NULL;
    if (data->input_redirection) {
        fd_input = open(data->input_file, O_RDONLY);
        if (fd_input < 0) {
            perror("Failed to open input file");
            exit(EXIT_FAILURE);
        }
        dup2(fd_input, STDIN_FILENO);
        close(fd_input);
    }
    // If output redirection is present, open the file and duplicate file descriptor
    else if (data->output_redirection) {
		if (data->append_redirection == 1)
		{
			fd_output = open(data->output_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else
		{
			fd_output = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
        if (fd_output < 0) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }
        dup2(fd_output, STDOUT_FILENO);
        close(fd_output);
    }

    else if (data->append_redirection) {
        while ((content = readline("heredoc> ")) != NULL) {
        if (strcmp(content, data->delim) == 0) {
            free(content); // Free the delimiter input
            break; // Exit the loop when the delimiter is encountered
        }
        if (line == NULL) {
            line = strdup(content); // Initialize line with the first input
        } else {
            char* temp = ft_strjoin(line, "\n"); // Add a newline between previous content and new input
            free(line); // Free the old line
            line = ft_strjoin(temp, content); // Concatenate the new input to line
            free(temp); // Free the temporary variable
        }
        free(content); // Free the input after processing
    }
    // Clean up memory and set 'data->input_file' to the concatenated content
    data->input_file = line;

    }
}

char *find_path(char *program, t_data *data)
{
    char *path_var;
    char *path;
    char *full_path;

    if (program[0] == '/' || program[0] == '.')
        return (strdup(program));
    path_var = strdup(data->path_env); // Make a copy of the path_env to avoid modifying the original string
    path = ft_strtok(path_var, ":");
    while (path)
    {
        // Calculate the length needed for the full path
        size_t full_path_len = strlen(path) + 1 + strlen(program) + 1; // path + '/' + program + '\0'
        full_path = malloc(full_path_len);
        if (full_path == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Construct the full path
        snprintf(full_path, full_path_len, "%s/%s", path, program);

        // Check if the file exists at the current full path
        if (access(full_path, F_OK) == 0)
        {
            free(path_var);
            return full_path;
        }

        free(full_path);
        path = ft_strtok(NULL, ":");
    }
    free(path_var);
    return NULL;
}