/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:07:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 13:26:01 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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

t_list	*get_node_by_key(t_list	*lst, char *cmp)
{
	t_kv	*key_value;
	char	*key;
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		key_value = get_key_value(curr);
		key = key_value->key;
		if (ft_strncmp(cmp, key, longer_str(key, cmp)) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	set_env_value(t_list **env_lst, char *key, char *new_value)
{
	t_kv	*key_value;
	t_list	*key_node;

	if (!*env_lst)
	{
		free(new_value);
		return ;
	}
	key_node = get_node_by_key(*env_lst, key);
	key_value = get_key_value(key_node);
	free(key_value->value);
	key_value->value = new_value;
	key_node->content = (void *)key_value;
}
