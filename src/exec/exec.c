#include "../includes/minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

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