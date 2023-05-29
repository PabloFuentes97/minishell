/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 09:06:00 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:59:55 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

static void	swap_lst_nodes(t_list **node1, t_list **node2)
{
	t_list	*aux;

	aux = (*node1)->content;
	(*node1)->content = (*node2)->content;
	(*node2)->content = aux;
}

void	sort_env_lst(t_list	**lst)
{
	t_list	*curr1;
	t_list	*curr2;

	curr1 = *lst;
	curr2 = curr1;
	while (curr1)
	{
		while (curr2)
		{
			if (ft_strncmp(get_key_value(curr1)->key, get_key_value(curr2)->key,
					longer_str(get_key_value(curr1)->key,
						get_key_value(curr2)->key)) > 0)
				swap_lst_nodes(&curr1, &curr2);
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
		if (!curr1->next)
			break ;
		curr2 = curr1->next;
	}
}

int	matrix_len(char **matrix)
{
	int	cont;

	cont = 0;
	while (matrix[cont])
		cont++;
	return (cont);
}

static void	export_exiting_var(char *var, t_executer *executer)
{
	t_list	*node;
	t_kv	*key_val;

	printf("No hay igual, solo nombre de variable\n");
	node = get_node_by_key(executer->env->env_lst, var);
	if (node)
	{
		printf("Está en la lista: %s\n", get_key_value(node)->key);
		set_var_type(&node, 0);
		key_val = (t_kv *)node->content;
	}
	else
	{
		ft_lstadd_back(&executer->env->env_lst,
			ft_lstnew(set_key_value(ft_strdup(var),
					ft_strdup("''"), 0)));
	}
}

static void	export_assign_var(char *key, char *value, t_executer *executer)
{
	t_list	*node;
	t_kv	*key_val;

	printf("Hay igual, asignación de key y valor\n");
	node = get_node_by_key(executer->env->env_lst, key);
	if (node)
	{
		printf("Ya existe, cambio valor de la key\n");
		set_env_value(&executer->env->env_lst,
			get_key_value(node)->key, value);
	}
	else
	{
		printf("No existe, añadir key y valor\n");
		ft_lstadd_back(&executer->env->env_lst,
			ft_lstnew(set_key_value(ft_strdup(key),
					ft_strdup(value), 0)));
	}
}

void	export(char **cmd, t_executer *executer)
{
	int		cont;

	if (!cmd[1])
	{
		sort_env_lst(&executer->env->env_lst);
		print_env_lst(executer->env->env_lst);
	}
	cont = 1;
	while (cmd[cont])
	{
		if (!cmd[cont + 1] || ft_strncmp(cmd[cont + 1], "=",
				longer_str(cmd[cont + 1], "=")) != 0)
		{	
			export_exiting_var(cmd[cont], executer);
			cont++;
		}
		else if (ft_strncmp(cmd[cont + 1], "=",
				longer_str(cmd[cont + 1], "=")) == 0)
		{
			export_assign_var(cmd[cont], cmd[cont + 2], executer);
			cont += 3;
		}
	}
	executer->last_return = 0;
}
