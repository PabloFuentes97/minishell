/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:40:59 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 11:55:31 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

int	check_quotes(char *str, t_list **tokens)
{
	int	skip;
	int	start;

	skip = 0;
	start = 0;
	if (str[0] == 39)
		skip = skip_to_char(&str[1], 39);
	else if (str[0] == 34)
		skip = skip_to_char(&str[1], 34);
	ft_lstadd_back(tokens, ft_lstnew((void *)new_token(ft_substr(&str[1],
					start, skip - start))));
	if (str[skip + 1] != '\0')
		ft_lstadd_back(tokens,
			ft_lstnew((void *)new_token(ft_substr(&str[1], skip, 1))));
	return (skip + 1);
}

static void	add_token_lst(char *line, int *pos, t_list **tokens, int type)
{
	char	*str;
	t_token	*token;
	t_list	*new;

	if (type == 0)
		str = ft_substr(line, pos[0],
				pos[1] - pos[0]);
	else
		str = ft_substr(line, pos[1],
				pos[2]);
	token = new_token(str);
	new = ft_lstnew(token);
	ft_lstadd_back(tokens, new);
}

int	check_assignment(char *str, char **dict, t_list **tokens)
{
	int	skip;
	int	dict_check;

	skip = 0;
	if (str[1] == 39 || str[1] == 34)
	{
		ft_lstadd_back(tokens, ft_lstnew(ft_lstnew(char_to_str(str[1]))));
		skip = check_quotes(&str[1], tokens) + 1;
	}
	else
	{
		skip = 1;
		while (str[skip])
		{
			dict_check = in_dict(&str[skip], dict);
			if (str[skip] == ' ' || dict_check > 0)
				break ;
			skip++;
		}
		ft_lstadd_back(tokens, ft_lstnew((void *)new_token
				(ft_substr(&str[1], 0, skip - 1))));
		if (dict_check > 0)
			skip--;
	}
	return (skip);
}

int	check_special_symbol(char *str, char **dict, t_list **tokens)
{
	if (str[0] == 34 || str[0] == 39)
		return (check_quotes(str, tokens));
	if (str[0] == 61)
		return (check_assignment(str, dict, tokens));
	return (0);
}

void	tokens_lst(char *line, t_list **tokens, char **dict)
{
	int	p[3];

	p[1] = 0;
	while (line[p[1]])
	{
		p[1] = skip_spaces(line, p[1]);
		p[0] = p[1];
		while (line[p[1]] && line[p[1]] != ' ')
		{
			p[2] = in_dict(&line[p[1]], dict);
			if (p[2] > 0)
			{
				if (p[0] != p[1] || (line[p[1]] == 61
						&& (p[1] - 1) >= 0 && line[p[1] - 1] == ' '))
					add_token_lst(line, p, tokens, 0);
				add_token_lst(line, p, tokens, 1);
				p[1] += check_special_symbol(&line[p[1]], dict, tokens) + p[2];
				p[0] = p[1];
			}
			else
				p[1]++;
		}
		if (p[0] != p[1])
			add_token_lst(line, p, tokens, 0);
	}
}
