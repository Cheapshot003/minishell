#include "../../includes/minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
void execute(t_data *data)
{
	(void)(data);
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
        full_path = ft_calloc(full_path_len, sizeof(char));
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