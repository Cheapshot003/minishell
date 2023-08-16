#include "../../includes/minishell.h"

t_exec *create_t_exec(void) {
	t_exec *new_exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
    if (new_exec == NULL) {
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
	new_exec->heredoc = get_heredoc();
    return new_exec;
}

// Function to insert a t_exec node at the end of the linked list
void insert_t_exec(t_exec **head, t_exec *new_exec) {
    if (*head == NULL) {
        *head = new_exec;
    } else {
        t_exec *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_exec;
        new_exec->prev = current;
    }
}

void free_t_exec_list(t_exec *head) {
	while (head != NULL) {
		t_exec *temp = head;
        head = head->next;
		if (temp->input_file != NULL)
			free(temp->input_file);
		if (temp->output_file != NULL)
			free(temp->output_file);
		if (temp->path != NULL)
		{
			if (ft_strncmp(temp->path[0], "", ft_strlen(temp->path[0])) != 0)
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
	head = NULL;
}

t_exec *get_t_exec_at_index(t_exec *head, int index) {
    if (index < 0) {
        fprintf(stderr, "Invalid index\n");
        return NULL;
    }
    t_exec *current = head;
    int count = 0;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        fprintf(stderr, "Index out of bounds\n");
        return NULL;
    }

    return current;
}