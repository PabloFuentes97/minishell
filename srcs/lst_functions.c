/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/09 14:58:16 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"


//borra un nodo de una lista
void	delete_node(t_list **lst, t_list **node) // aqui pasar funcion de borrado de contenido por referencia
{
	t_list	*curr;

	
	if (*lst == *node)
	{
		*lst = *node;
		return ;
	}
	curr = *lst;
	while (curr)
	{
		if (curr == *node)
		{
			printf("Lo encontró, hacer unset\n");
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			//free(curr->content);
			//free(curr);
			break ;
		}
		curr = curr->next;
	}
}

void	lst_delete_node(t_list **node, void (*del)(void *))
{
	if (!node || !(*node))
		return ;
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	del((*node)->content);
	free(*node);
	*node = NULL;
	node = NULL;
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

void	lst_delete_sublst(t_list **head, t_list *last, int inc, void (*del) (void *))
{
	t_list	*curr;
	t_list	*aux;

	curr = *head;
	while (curr && curr != last)
	{
		aux = curr;
		curr = curr->next;
		lst_delete_node(&aux, del);
	}
	if (inc == 1 && curr)
		lst_delete_node(&curr, del);
}

t_list	**lst_divide(int num, ...)
{
	t_list	**sub_lst;
	va_list	args;
	int		cont;

	sub_lst = malloc(sizeof(t_list *) * num + 1);
	va_start(args, num);
	cont = 0;
	while (cont < num)
	{
		sub_lst[cont] = va_arg(args, t_list *);
		if (sub_lst[cont]->prev)
			sub_lst[cont]->prev->next = NULL;
		printf("Agregó lista %d al array de listas\n", cont);
		sub_lst[cont]->prev = NULL;
		cont++;
	}
	va_end(args);
	sub_lst[cont] = NULL;
	return (sub_lst);
}

t_list	*lst_join(t_list **lst)
{
	int		cont;
	t_list	*head;

	cont = 1;
	head = lst[0];
	while (lst[cont])
	{
		ft_lstadd_back(&head, lst[cont]);
		cont++;
	}
	free(lst);
	lst = NULL;
	return (head);
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
void	delete_node_str(t_list **lst, t_list *node)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	while (curr)
	{
		if (ft_strncmp((char *)curr->content, (char *)node->content,
				longer_str((char *)curr->content, (char *)node->content)) == 0)
		{
			prev->next = curr->next;
			free(curr->content);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	remove_head(t_list **lst)
{
	t_list	*aux;

	if (lst)
	{
		if (*lst)
		{
			aux = *lst;
			*lst = (*lst)->next;
			if (*lst)
			{
				(*lst)->prev = NULL;
				aux->next = NULL;
			}	
			free(aux->content);
			free(aux);
		}
	}
}

//busca un nodo con una posición y lo devuelve
t_list	*move_to_node(t_list	*lst, int pos)
{
	int	cont;

	cont = 0;
	while (cont < pos)
	{
		lst = lst->next;
		cont++;
	}
	return (lst);
}

//imprimir lista con contenido string
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
