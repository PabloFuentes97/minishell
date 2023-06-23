/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:45:41 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 11:55:15 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static int	ft_rev_strncmp(char *s1, char *s2, int n)
{
	int	cont_s1;

	cont_s1 = (int)ft_strlen(s1) - 1;
	while (n >= 0 && (s1[cont_s1] != '\0' || s2[n] != '\0'))
	{
		if (s1[cont_s1] != s2[n])
			return ((unsigned char)s1[cont_s1] - (unsigned char)s2[n]);
		cont_s1--;
		n--;
	}
	return (0);
}

static char	*check_word(t_list *tokens, char *entry)
{
	t_token	*token;
	char	*ptr_between;

	token = get_token(tokens);
	if (!tokens->prev || get_token(tokens->prev)->type == 2)
	{
		if (ft_strncmp(token->str, entry, ft_strlen(token->str)) == 0)
			return (entry);
		return (NULL);
	}
	else if (!tokens->next)
	{
		if (ft_rev_strncmp(entry, token->str, ft_strlen(token->str) - 1) == 0)
			return (entry);
		return (NULL);
	}
	ptr_between = ft_strnstr(entry, token->str, ft_strlen(entry));
	if (!ptr_between)
		return (NULL);
	return (ptr_between);
}

static char	*new_path(char *curr_path, char *bar, char *entry)
{
	char	*new;

	if (curr_path)
	{
		new = ft_strjoin(curr_path, entry);
		new = aux_join(new, bar);
	}
	else
	{
		new = ft_strdup(entry);
		new = aux_join(new, bar);
	}
	return (new);
}

int	check_dir_case(t_list *tokens, struct dirent *ent,
	t_list **wildcards_lst, char *path)
{
	if (!tokens->next && ent->d_type == DT_DIR)
		return (1);
	else if (ent->d_type == DT_DIR && ((ft_strncmp(ent->d_name, ".", 1) != 0)
			&& (ft_strncmp(ent->d_name, "..", 2) != 0)))
		wildcards(tokens->next, wildcards_lst,
			new_path(path, get_token(tokens)->str, ent->d_name));
	return (0);
}

int	check_entry(t_list *tokens, struct dirent *ent,
	t_list **wildcards_lst, char *path)
{
	t_list			*curr;
	t_token			*token;
	char			*entry;

	curr = tokens;
	entry = ent->d_name;
	while (curr)
	{
		token = get_token(curr);
		if (ft_strncmp(entry, ".", 1) == 0 || ft_strncmp(entry, "..", 2) == 0)
			return (0);
		if (token->type == 0)
		{
			entry = check_word(curr, entry);
			if (!entry || *entry == '\0')
				return (0);
			entry += ft_strlen(token->str);
		}
		else if (token->type == 2)
			return (check_dir_case(curr, ent, wildcards_lst, path));
		curr = curr->next;
	}
	if (!curr)
		return (1);
	return (0);
}
