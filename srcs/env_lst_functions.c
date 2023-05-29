#include "../includes/minishell.h"
#include "../libft/libft.h"

//establece valores de nodo de variable de entorno: key-value
t_kv	*set_key_value(char *key, char *value, int type)
{
	t_kv	*key_value;

	key_value = malloc(sizeof(t_kv));
	key_value->key = key;
	key_value->value = value;
	key_value->type = type;
	return (key_value);
}

t_kv	*get_key_value(t_list *node)
{
	t_kv	*key_value;

	key_value = (t_kv *)node->content;
	return (key_value);
}

//crear un nodo para lista de variables de entorno
t_list	*set_env_node(char *env_var)
{
	t_kv	*key_value;
	int		cont;

	cont = 0;
	while (env_var[cont])
	{
		if (env_var[cont] == '=')
		{
			key_value = set_key_value(ft_substr(env_var, 0, cont),
					ft_substr(env_var, cont + 1, ft_strlen(env_var) - cont), 0);
			return (ft_lstnew((void *)key_value));
		}
			cont++;
	}
	return (NULL);
}

//crear lista de variables de entorno
t_list	*set_env_list(char **env)
{
	int			row;
	t_list		*node;
	t_list		*env_lst;

	row = 0;
	env_lst = NULL;
	while (env[row])
	{
		node = set_env_node(env[row]);
		if (node)
			ft_lstadd_back(&env_lst, node);
		row++;
	}
	return (env_lst);
}

//cambia tipo de variable
void	set_var_type(t_list **node, int type)
{
	t_kv	*key_val;

	key_val = (t_kv *)get_key_value(*node);
	key_val->type = type;
	(*node)->content = key_val;
}

//imprimir lista de variables de entorno
void	print_env_lst(t_list *env_lst)
{
	t_kv	*key_value;
	t_list	*curr;
	int		cont;

	cont = 0;
	curr = env_lst;
	while (curr)
	{
		key_value = (t_kv *)curr->content;
		if (key_value->type == 0)
			printf("%s=%s\n", key_value->key, key_value->value);
		curr = curr->next;
		cont++;
	}
}

//busca un nodo con una key y la devuelve
char	*get_env_key(t_list	**lst, t_list **node)
{
	t_list	*curr;
	t_kv	*key_value;

	curr = *lst;
	while (curr)
	{
		if (curr == *node)
		{
			key_value = (t_kv *)curr->content;
			return (key_value->key);
		}	
		curr = curr->next;
	}
	return (NULL);
}

//busca un nodo con una key y devuelve su valor
char	*get_env_value(t_list	*lst, char *cmp)
{
	t_kv	*key_value;
	char	*key;
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		key_value = (t_kv *)curr->content;
		key = key_value->key;
		if (ft_strncmp(cmp, key, longer_str(cmp, key)) == 0)
			return (key_value->value);
		curr = curr->next;
	}
	return (NULL);
}

//busca un nodo con una key y lo devuelve
t_list	*get_node_by_key(t_list	*lst, char *cmp)
{
	t_kv	*key_value;
	char	*key;
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		key_value = (t_kv *)curr->content;
		key = key_value->key;
		if (ft_strncmp(cmp, key, longer_str(key, cmp)) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
//establece el valor de un nodo buscando su key
void set_env_value(t_list **env_lst, char *key, char *new_value)
{
	t_list	*env_var;
	t_kv 	*key_value;

	env_var = get_node_by_key(*env_lst, key);
	if (!env_var)
		return ;
	key_value =	(t_kv *)env_var->content;
	free(key_value->value);
	key_value->value = new_value;
	env_var->content = (void *)key_value;
}

char **env_lst_to_matrix(t_list *env_lst)
{
	t_kv	*key_val;
	char	**env_matrix;
	int		i;

	env_matrix = malloc(sizeof(ft_lstsize(env_lst) + 1));
	i = 0;
	while (env_lst)
	{
		key_val = (t_kv *)env_lst->content;
		env_matrix[i] = ft_strjoin_variadic(2, ft_strdup(key_val->key),
				ft_strdup("="), ft_strdup(key_val->value));
		printf("Env: %s\n", env_matrix[i]);
		i++;
		env_lst = env_lst->next;
	}
	printf("i: %d\n", i);
	env_matrix[i] = NULL;
	return (env_matrix);
}

void	free_key_value(void *content)
{
	t_kv *key_val;

	key_val = (t_kv *)content;
	free(key_val->key);
	key_val->key = NULL;
	free(key_val->value);
	key_val->value = NULL;
	free(key_val);
	key_val = NULL;
}