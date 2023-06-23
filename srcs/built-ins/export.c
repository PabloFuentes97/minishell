/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:41:42 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 13:14:19 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

static void	wrong_var(char *var, t_mshell *mshell)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	mshell->data.last_cmd = 1;
	mshell->data.last_err = 1;
	errno = 1;
}

static void	export_exiting_var(char *var, t_mshell *mshell)
{
	t_list	*node;
	t_kv	*key_val;

	if (ft_strncmp(var, "", 1) == 0 || ft_strncmp(var, " ", 1) == 0)
		return ;
	else if (ft_isdigit(var[0]) == 1)
		wrong_var(var, mshell);
	node = get_node_by_key(mshell->data.env_lst, var);
	if (node)
	{
		set_var_type(&node, 0);
		key_val = (t_kv *)node->content;
	}
	else
	{
		ft_lstadd_back(&mshell->data.env_lst,
			ft_lstnew(set_key_value(ft_strdup(var),
					ft_strdup("''"), 0)));
	}
}

static void	export_assign_var(char *key, char *value, t_mshell *mshell)
{
	t_list	*node;
	t_kv	*key_val;

	if (ft_strncmp(key, "", 1) == 0 || ft_strncmp(key, " ", 1) == 0)
		return ;
	else if (ft_isdigit(key[0]) == 1)
		wrong_var(key, mshell);
	node = get_node_by_key(mshell->data.env_lst, key);
	if (node)
	{
		set_env_value(&node,
			key, ft_strdup(value));
	}
	else
	{
		ft_lstadd_back(&mshell->data.env_lst,
			ft_lstnew(set_key_value(ft_strdup(key),
					ft_strdup(value), 0)));
	}
}

static void	export_sorted_env(t_list *env)
{
	t_list	*sort_lst;

	sort_lst = copy_env_lst(env);
	sort_env_lst(sort_lst);
	print_env_lst(sort_lst);
	ft_lstclear(&sort_lst, &free_key_value);
}

void	export(char **cmd, t_mshell *mshell)
{
	int		cont;

	if (!cmd[1])
	{
		export_sorted_env(mshell->data.env_lst);
		mshell->data.last_cmd = 0;
		return ;
	}
	cont = 1;
	mshell->data.last_cmd = 0;
	while (cmd[cont])
	{
		if (!cmd[cont + 1] || ft_strncmp(cmd[cont + 1], "=",
				longer_str(cmd[cont + 1], "=")) != 0)
		{	
			export_exiting_var(cmd[cont], mshell);
			cont++;
		}
		else if (ft_strncmp(cmd[cont + 1], "=",
				longer_str(cmd[cont + 1], "=")) == 0)
		{
			export_assign_var(cmd[cont], cmd[cont + 2], mshell);
			cont += 3;
		}
	}
}
