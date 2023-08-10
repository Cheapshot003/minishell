#include "../../includes/minishell.h"



t_cmd *create_t_cmd(void) {
    t_cmd *new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (new_cmd == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    new_cmd->str = NULL;
    new_cmd->i = -1;
    new_cmd->next = NULL;
    new_cmd->prev = NULL;

    return new_cmd;
}

// Function to insert a t_cmd node at the end of the linked list
void insert_t_cmd(t_cmd **head, t_cmd *new_cmd) {
    if (*head == NULL) {
        *head = new_cmd;
    } else {
        t_cmd *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_cmd;
        new_cmd->prev = current;
    }
}

// Function to free the memory of the linked list
void free_t_cmd_list(t_cmd *head) {
    while (head != NULL) {
        t_cmd *temp = head;
        head = head->next;
        
        // Free any dynamically allocated memory in the t_cmd struct
        // For example: free(temp->str), free(temp->infile), free(temp->outfile), etc.
        
        free(temp);
    }
}

t_cmd *get_t_cmd_at_index(t_cmd *head, int index) {
    if (index < 0) {
        fprintf(stderr, "Invalid index\n");
        return NULL;
    }

    t_cmd *current = head;
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

void insert_t_cmd_at_index(t_cmd **head, t_cmd *new_cmd, int index) {
    if (index < 0) {
        fprintf(stderr, "Invalid index\n");
        return;
    }

    if (*head == NULL) {
        if (index == 0) {
            *head = new_cmd;
        } else {
            fprintf(stderr, "Index out of bounds\n");
        }
        return;
    }

    if (index == 0) {
        new_cmd->next = *head;
        (*head)->prev = new_cmd;
        *head = new_cmd;
        return;
    }

    t_cmd *current = *head;
    int count = 0;
    while (current != NULL && count < index - 1) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    new_cmd->next = current->next;
    new_cmd->prev = current;
    if (current->next != NULL) {
        current->next->prev = new_cmd;
    }
    current->next = new_cmd;
}

void delete_t_cmd_at_index(t_cmd **head, int index) {
    if (index < 0) {
        fprintf(stderr, "Invalid index\n");
        return;
    }

    if (*head == NULL) {
        fprintf(stderr, "List is empty\n");
        return;
    }

    if (index == 0) {
        t_cmd *temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp); // Free dynamically allocated memory
        return;
    }

    t_cmd *current = *head;
    int count = 0;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current); // Free dynamically allocated memory
}