/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:28:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 11:41:28 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

static void	dollar_var(char *var, t_list **lst, t_mshell *mshell)
{
	char	*value;

	value = get_env_value(mshell->data.env_lst, var);
	if (value)
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(value)));
	free(var);
}

static int	add_dollar(char *line, int i, t_list **words, t_mshell *mshell)
{
	int	dollar;

	dollar = i + 1;
	i++;
	if (line[dollar] == '?')
	{
		ft_lstadd_back(words, ft_lstnew(ft_itoa(mshell->data.last_err)));
		i += 1;
	}
	else if (line[dollar] != '\0')
	{
		while (line[i] && (line[i] != ' '
				&& line[i] != '$' && line[i] != '/' && line[i] != 39))
			i++;
		dollar_var(ft_substr(line, dollar, i - dollar), words, mshell);
	}
	return (i);
}

static char	*dollar_str(char *line, t_list *words)
{
	char	*new;

	new = lst_to_str(words);
	ft_lstclear(&words, &free);
	free(line);
	return (new);
}

char	*dollar_expansion(char *line, t_mshell *mshell)
{
	int		i;
	int		prev;
	t_list	*words;

	i = 0;
	prev = 0;
	words = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (prev != i)
				ft_lstadd_back(&words, ft_lstnew
					(ft_substr(line, prev, i - prev)));
			i = add_dollar(line, i, &words, mshell);
			prev = i;
		}
		else
			i++;
	}
	if (prev != i)
		ft_lstadd_back(&words, ft_lstnew(ft_substr(line, prev, i - prev)));
	return (dollar_str(line, words));
}
