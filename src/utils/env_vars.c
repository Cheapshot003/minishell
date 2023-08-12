#include "../../includes/minishell.h"

t_list *init_env_vars(char **environ)
{
  int i;
  t_var *new_var;
  t_list *result_list;
  t_list *new_lst_el;
  char *var_value;

  result_list = NULL;
  i = 0;
  while (environ[i] != NULL)
  {
    new_var = malloc(sizeof(t_var));
    new_var->var_name = ft_strdup(environ[i]);
    var_value = getenv(environ[i]);
    if (var_value != NULL)
      var_value = ft_strdup(var_value);
    new_var->var_value = var_value;
    new_lst_el = ft_lstnew(new_var);
    ft_lstadd_back(&result_list, new_lst_el);
    i++;
  }
  return (result_list);
}

char **get_env_vars_array(t_data *data)
{
  int vars_len = ft_lstsize(data->vars);
  char **env_vars;
	t_list *current = data->vars;
	int i = 0;

  env_vars = malloc((vars_len + 1) * sizeof(char *)); // +1 for NULL at the end
	while (current != NULL)
	{
		t_var *var = (t_var *)current->content;
		char *env_var_str = malloc(ft_strlen(var->var_name) + ft_strlen(var->var_value) + 2); // 1 for '=', 1 for '\0'
		env_var_str[0] = '\0';
		ft_strlcat(env_var_str, var->var_name, ft_strlen(var->var_name) + 1);
		ft_strlcat(env_var_str, "=", ft_strlen(var->var_name) + 2);
    if (var->var_value != NULL)
		  ft_strlcat(env_var_str, var->var_value, ft_strlen(var->var_name) + 1 + ft_strlen(var->var_value) + 1);
		env_vars[i] = env_var_str;
		i++;
		current = current->next;
	}
  env_vars[i] = NULL;
  return (env_vars);
}

void free_lst(t_data *data)
{
	t_var *temp;
	t_list *temp1;
	t_list *lst;

	lst = data->vars;
	while(lst != NULL)
	{
		temp = (t_var *)lst->content;
		temp1 = lst;
		free(temp->var_name);
		free(temp->var_value);
		free(temp1->content);
		lst = lst->next;
		free(temp1);
	}
	rl_clear_history();
	
}