#include "../../includes/minishell.h"

void parse(t_data *data)
{
	data->exec_head = getexecs(data);
	fillredirects(data->exec_head, data);
	fillpath(data->exec_head, data);
	if (data->exec_head->path == NULL)
		exiterror(data, "Syntax Error", 0);

}

void	fillpath(t_exec *head, t_data *data)
{
	t_cmd *head_cmd;
	//t_exec *head_exec;
	t_exec *current_exec;
	t_cmd *current_cmd;
	int done;

	done = 0;
	//head_exec = head;
	current_exec = head;
	head_cmd = data->cmd_head;
	current_cmd = head_cmd;
	
	while (done == 0)
	{
		while (current_cmd->str && ft_strncmp(current_cmd->str, "|", ft_strlen(current_cmd->str)) != 0)
		{
			if (is_redirect(current_cmd->str) != 0)
			{
				current_cmd = current_cmd->next;
			}
			else
			{
				current_exec->path = ft_appendstr(current_exec->path, ft_strdup(current_cmd->str));
				current_cmd = current_cmd->next;
			}
		}
		if (current_cmd->str == NULL)
			done = 1;
		else
		{
			current_exec = current_exec->next;
			current_cmd = current_cmd->next;
		}
	}
}

t_exec *getexecs(t_data *data)
{
	int	npipes;
	t_exec *head;
	t_exec *new;
	npipes = -1;
	npipes = count_pipes(data);
	if (npipes >= 0)
	{
		head = create_t_exec();
		npipes--;
	}
	while (npipes >= 0)
	{
		new = create_t_exec();
		insert_t_exec(&head, new);
		npipes--;
	}
	return (head);
}

int	count_pipes(t_data *data)
{
	int npipes;
	t_cmd *this;

	this = data->cmd_head;	
	npipes = 0;

	while(this->str != NULL)
	{
		if (ft_strncmp(this->str, "|", ft_strlen(this->str)) == 0)
		{
			npipes++;
		}
		this = this->next;
	}
	return (npipes);	
}

void	exiterror(t_data *data, char *errmsg, int exitbit)
{
	data->exit = exitbit;
	data->skip = 1;
	printf("%s\n", errmsg);
	return ;
}