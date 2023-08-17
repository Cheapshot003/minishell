/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/16 10:45:07 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_t_cmd(void)
{
	t_cmd	*new_cmd; 

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (new_cmd == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	new_cmd->str = NULL;
	new_cmd->i = -1;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

void	insert_t_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (*head == NULL)
		*head = new_cmd;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
		new_cmd->prev = current;
	}
}

void	free_t_cmd_list(t_cmd *head)
{
	t_cmd	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->str != NULL)
		{
			free(temp->str); 
			temp->str = NULL;
		}
		free(temp);
		temp = NULL;
	}
	head = NULL;
}

t_cmd	*get_t_cmd_at_index(t_cmd *head, int index)
{
	t_cmd	*current;
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
		fprintf(stderr, "Index out of bounds\n");
		return (NULL);
	}
	return (current);
}

void	delete_t_cmd_at_index(t_cmd **head, int index)
{
	t_cmd	*temp;
	t_cmd	*current;
	int		count;

	if (index < 0)
	{
		fprintf(stderr, "Invalid index\n");
		return ;
	}
	if (*head == NULL)
	{
		fprintf(stderr, "List is empty\n");
		return ;
	}
	if (index == 0) 
	{
		temp = *head;
		*head = (*head)->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(temp->str);
		free(temp);
		return ;
	}
	current = *head;
	count = 0;
	while (current != NULL && count < index)
	{
		current = current->next;
		count++;
	}
	if (current == NULL)
	{
		fprintf(stderr, "Index out of bounds\n");
		return ;
	}
	if (current->prev != NULL)
		current->prev->next = current->next;
	if (current->next != NULL)
		current->next->prev = current->prev;
	free(current->str);
	free(current);
}
