/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:55:44 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:06:47 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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

void	set_var_type(t_list **node, int type)
{
	t_kv	*key_val;

	key_val = (t_kv *)get_key_value(*node);
	key_val->type = type;
	(*node)->content = key_val;
}
