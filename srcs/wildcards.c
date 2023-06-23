/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:31:07 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/20 13:45:45 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static DIR	*get_wildcard_dir(char *path)
{
	DIR	*dir;

	if (!path)
		dir = opendir(".");
	else
		dir = opendir(path);
	if (!dir)
		exit(EXIT_FAILURE);
	return (dir);
}

static void	free_wildcards_struct(DIR *dir, struct dirent *ent, char *path)
{
	free(ent);
	free(dir);
	if (path)
		free(path);
}

void	wildcards(t_list *tokens, t_list **wildcards_lst, char *path)
{
	DIR				*dir;
	struct dirent	*ent;
	struct dirent	*aux;

	dir = get_wildcard_dir(path);
	ent = readdir(dir);
	aux = ent;
	while (ent)
	{
		if (check_entry(tokens, ent, wildcards_lst, path) == 1)
			add_entry_wildcards(wildcards_lst, path,
				entry_to_add(tokens, ent->d_name));
		ent = readdir(dir);
	}
	free_wildcards_struct(dir, aux, path);
}

void	tokens_wildcards(t_list **lst, char *str)
{
	int		start;
	int		end;
	char	c;

	end = 0;
	while (str[end])
	{
		start = end;
		if (str[end] == '*' || str[end] == '/')
		{
			c = str[end];
			while (str[end] == c)
				end++;
			ft_lstadd_back(lst, ft_lstnew(new_token
					(ft_substr(str, start, end - start))));
			start = end;
		}
		while (str[end] && (str[end] != '*' && str[end] != '/'))
			end++;
		if (start != end)
			ft_lstadd_back(lst, ft_lstnew(new_token
					(ft_substr(str, start, end - start))));
	}
}

char	*call_wildcards(char *str)
{
	t_list	*wildcards_lst;
	t_token	*token;
	char	*wildcards_str;
	t_list	*tokens;
	char	**dict;

	wildcards_lst = NULL;
	tokens = NULL;
	tokens_wildcards(&tokens, str);
	dict = new_wildcards_dict();
	assign_tokens_type(&tokens, dict);
	free(dict);
	token = get_token(tokens);
	if (token->type == 2)
		wildcards(tokens->next, &wildcards_lst, ft_strdup(token->str));
	else
		wildcards(tokens, &wildcards_lst, NULL);
	print_str_lst(wildcards_lst);
	sort_str_lst(&wildcards_lst);
	wildcards_str = lst_to_str_spaces(wildcards_lst);
	ft_lstclear(&tokens, &free_token);
	ft_lstclear(&wildcards_lst, free);
	free(str);
	return (wildcards_str);
}
