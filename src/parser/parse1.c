#include "../../includes/minishell.h"

void	fillredirects(t_exec *head, t_data *data)
{
	t_cmd *head_cmd;
	t_exec *current_exec;
	t_cmd *current_cmd;
	int done;
	int i;
	int redirect;

	redirect = -1;
	done = 0;
	i = 0;
	current_exec = head;
	head_cmd = data->cmd_head;
	current_cmd = head_cmd;
	while (done == 0 && current_cmd)
	{
		while (current_cmd->str != NULL)
		{
			if (ft_strncmp(current_cmd->str, "|", ft_strlen(current_cmd->str)) != 0)
			{
				redirect = is_redirect(current_cmd->str);
				if (redirect > 0)
				{
					if (redirect == 1)// < Input Redirection
					{
						current_exec->input_redirection = 1;
						current_exec->input_file = ft_strdup(current_cmd->next->str);
					} 
					else if (redirect == 2) //> Output
					{
						current_exec->output_redirection = 1,
						current_exec->output_file = ft_strdup(current_cmd->next->str);
					}
					else if (redirect == 3) // << Heredoc
					{
						//TBD
					}
					else if (redirect == 4) // >> Append
					{
						current_exec->append_redirection = 1;
						current_exec->output_file = ft_strdup(current_cmd->next->str);
					}
					delete_t_cmd_at_index(&head_cmd, i+1);
					delete_t_cmd_at_index(&head_cmd, i);
					current_cmd = head_cmd;
					i--;
					continue;
				}
			}
			current_cmd = current_cmd->next;
			i++;
		}
		if (current_cmd == NULL || current_cmd->str == NULL)
			done = 1;
		else
		{
			current_exec = current_exec->next;
			current_cmd = current_cmd->next;
		}
	}
	data->cmd_head = head_cmd;
}

void	free_tok(char **tokens)
{
	int i;

	i = getarrlen(tokens);
	while (i >= 0)
	{
		free(tokens[i]);
		i--;
	}
	free(tokens);
	return ;
}