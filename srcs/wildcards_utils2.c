/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:22:27 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/13 16:29:26 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	**new_wildcards_dict(void)
{
	char	**dict;

	dict = malloc(sizeof(char *) * 3);
	dict[0] = "*";
	dict[1] = "/";
	dict[2] = NULL;
	return (dict);
}

char	*entry_to_add(t_list *tokens, char *entry)
{
	char	*new;
	t_token	*last;

	last = get_token(ft_lstlast(tokens));
	if ((tokens->prev && get_token(tokens->prev)->type != 2)
		&& (ft_strncmp(entry, ".", ft_strlen(entry)) == 0
			|| ft_strncmp(entry, "..", ft_strlen(entry)) == 0))
	{
		free(entry);
		return (NULL);
	}
	if (last->type == 2)
		new = ft_strjoin(entry, last->str);
	else
		new = ft_strdup(entry);
	return (new);
}

void	add_entry_wildcards(t_list **wildcards_lst, char *path, char *entry)
{
	if (!entry)
		return ;
	if (path)
	{
		ft_lstadd_back(wildcards_lst,
			ft_lstnew(ft_strjoin(path, entry)));
		free(entry);
	}
	else
		ft_lstadd_back(wildcards_lst, ft_lstnew((void *)entry));
}
