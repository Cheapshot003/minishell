#include "../includes/minishell.h"

t_data *init_data(t_data *data)
{
    data->append_redirection = 0;
    data->arg_count = 0;
    data->full_tokens = NULL;
    data->input_file = NULL;
    data->input_redirection = 0;
    data->output_file = NULL;
    data->output_redirection = 0;
    data->path_args = NULL;
    data->path_env = NULL;
    data->working_dir = NULL;
	data->builtin = 0;
	data->exit_status = 0;
	data->exit = 0;
	data->exit_arg = 0;
	data->exit_str = NULL;
  	fill_path(data);
    return data;
}