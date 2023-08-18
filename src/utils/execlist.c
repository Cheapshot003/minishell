/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 15:13:46 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	*create_t_exec(void)
{
	t_exec	*new_exec;

	new_exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (new_exec == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	new_exec->path = NULL;
	new_exec->input_file = NULL;
	new_exec->next = NULL;
	new_exec->append_redirection = 0;
	new_exec->input_redirection = 0;
	new_exec->output_file = NULL;
	new_exec->output_redirection = 0;
	new_exec->pipes[0] = -1;
	new_exec->pipes[1] = -1;
	new_exec->heredoc = get_hdoc();
	return (new_exec);
}

void	insert_t_exec(t_exec **head, t_exec *new_exec)
{
	t_exec	*current;

	if (*head == NULL)
		*head = new_exec;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_exec;
		new_exec->prev = current;
	}
}

void	free_t_exec(t_exec *temp)
{
	if (temp->input_file != NULL)
		free(temp->input_file);
	if (temp->output_file != NULL)
		free(temp->output_file);
	if (temp->path != NULL)
	{
		if (ft_strncmp(temp->path[0], "",
				ft_strlen(temp->path[0])) != 0)
			free_array((void **)temp->path);
	}
	if (temp->heredoc != NULL)
	{
		if (temp->heredoc->stuff != NULL)
			free(temp->heredoc->stuff);
		if (temp->heredoc->delims != NULL)
			free_array((void **)temp->heredoc->delims);
		free(temp->heredoc);
	}
	temp->path = NULL;
	free(temp);
}

void	free_t_exec_list(t_exec *head)
{
	t_exec	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free_t_exec(temp);
	}
	head = NULL;
}

t_exec	*get_t_exec_at_index(t_exec *head, int index)
{
	t_exec	*current;
	int		count;

	if (index < 0)
	{
		fprintf(stderr, "Invalid index\n");
		return (NULL);
	}
	current = head;
	count = 0;
	while (current != NULL && count < index)
	{
		current = current->next;
		count++;
	}
	if (current == NULL)
	{
		fprintf (stderr, "Index out of bounds\n");
		return (NULL);
	}
	return (current);
}
