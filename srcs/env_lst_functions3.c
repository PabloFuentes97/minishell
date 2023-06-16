/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_functions3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:08:00 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 13:26:52 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	**env_lst_to_matrix(t_list *env_lst)
{
	t_kv	*key_val;
	char	**env_matrix;
	char	*join;
	int		i;

	env_matrix = malloc(sizeof(char *) * (ft_lstsize(env_lst) + 1));
	i = 0;
	while (env_lst)
	{
		key_val = (t_kv *)env_lst->content;
		join = ft_strdup(key_val->key);
		join = aux_join(join, ft_strdup("="));
		join = aux_join(join, ft_strdup(key_val->value));
		env_matrix[i] = join;
		join = NULL;
		i++;
		env_lst = env_lst->next;
	}
	env_matrix[i] = NULL;
	return (env_matrix);
}

void	free_key_value(void *content)
{
	t_kv	*key_val;

	key_val = (t_kv *)content;
	free(key_val->key);
	key_val->key = NULL;
	free(key_val->value);
	key_val->value = NULL;
	free(key_val);
	key_val = NULL;
}

void	sort_env_lst(t_list	*lst)
{
	t_list	*curr1;
	t_list	*curr2;

	curr1 = lst;
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

t_list	*copy_env_lst(t_list	*env)
{
	t_list	*copy;
	t_kv	*key_val;

	copy = NULL;
	while (env)
	{
		key_val = get_key_value(env);
		if (key_val->type == 0)
			ft_lstadd_back(&copy,
				ft_lstnew(set_key_value(ft_strdup(key_val->key),
						ft_strdup(key_val->value), 0)));
		env = env->next;
	}
	return (copy);
}
