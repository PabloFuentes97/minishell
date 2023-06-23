/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:12:39 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	lst_delete_node(t_list **node, void (*del)(void *))
{
	t_list	*aux;

	if (!node || !(*node))
		return ;
	aux = *node;
	if (!(*node)->prev)
		(*node) = (*node)->next;
	if ((aux)->prev)
		(aux)->prev->next = (aux)->next;
	if ((aux)->next)
		(aux)->next->prev = (aux)->prev;
	del((aux)->content);
	free(aux);
}

void	lst_insert_node(t_list *node, t_list *add)
{
	t_list	*node_last;

	if (!node || !add)
		return ;
	add->prev = node;
	node_last = ft_lstlast(node);
	add->next = node_last->next;
	node_last->next = add;
	if (node_last->next)
		node_last->next->prev = add;
}

t_list	*find_node(t_list *lst, char *str)
{
	while (lst)
	{
		if (ft_strncmp((char *)lst->content, str,
				longer_str((char *)lst->content, str)) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	print_str_lst(t_list *str_list)
{
	char	*content;
	t_list	*curr;

	curr = str_list;
	while (curr)
	{
		content = (char *)curr->content;
		printf("%s\n", content);
		curr = curr->next;
	}
}

void	swap_lst_nodes(t_list **node1, t_list **node2)
{
	t_list	*aux;

	aux = (*node1)->content;
	(*node1)->content = (*node2)->content;
	(*node2)->content = aux;
}
