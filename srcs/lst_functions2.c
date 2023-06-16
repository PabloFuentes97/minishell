/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:12:55 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/13 17:23:35 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

size_t	strlen_lst(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len += ft_strlen((char *)lst->content);
		lst = lst->next;
	}
	return (len);
}

void	sort_str_lst(t_list **lst)
{
	t_list	*curr1;
	t_list	*curr2;

	curr1 = *lst;
	curr2 = curr1;
	while (curr1)
	{
		while (curr2)
		{
			if (ft_strncmp((char *)curr1->content, (char *)curr2->content,
					longer_str((char *)curr1->content,
						(char *)curr2->content)) > 0)
				swap_lst_nodes(&curr1, &curr2);
			curr2 = curr2->next;
		}
		if (!curr1->next)
			break ;
		curr1 = curr1->next;
		curr2 = curr1->next;
	}
}

char	*lst_to_str(t_list *lst)
{
	char	*str;
	char	*lst_str;
	int		i;
	int		l;

	str = malloc(strlen_lst(lst) + 1);
	i = 0;
	l = 0;
	while (lst)
	{
		lst_str = (char *)lst->content;
		while (lst_str[l])
		{
			str[i] = lst_str[l];
			i++;
			l++;
		}
		l = 0;
		lst = lst->next;
	}
	str[i] = '\0';
	return (str);
}

char	*lst_to_str_spaces(t_list *lst)
{
	char	*str;
	char	*lst_str;
	int		i;
	int		l;

	str = malloc(strlen_lst(lst) + ft_lstsize(lst) + 1);
	i = 0;
	l = 0;
	while (lst)
	{
		lst_str = (char *)lst->content;
		while (lst_str[l])
		{
			str[i] = lst_str[l];
			i++;
			l++;
		}
		str[i] = ' ';
		i++;
		l = 0;
		lst = lst->next;
	}
	str[i] = '\0';
	return (str);
}
