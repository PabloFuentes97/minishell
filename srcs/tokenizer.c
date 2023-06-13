/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:40:59 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/09 16:47:30 by pfuentes         ###   ########.fr       */
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

int	check_assignment(char *str, t_list **tokens)
{
	int	skip;
	int	cont;

	skip = 0;
	printf("Checkear asignación: %c y %c\n", str[0], str[1]);
	if (str[1] == 39 || str[1] == 34)
	{
		printf("Siguiente es comillas\n");
		ft_lstadd_back(tokens, ft_lstnew(ft_lstnew(char_to_str(str[1]))));
		skip = check_quotes(&str[1], tokens) + 1;
	}
	else
	{
		skip = skip_to_char(str, 32);
		ft_lstadd_back(tokens, ft_lstnew((void *)new_token
				(ft_substr(&str[1], 0, skip - 1))));
	}
	return (skip);
}

int	check_special_symbol(char *str, t_list **tokens)
{
	if (str[0] == 34 || str[0] == 39)
		return (check_quotes(str, tokens));
	if (str[0] == 61)
		return (check_assignment(str, tokens));
	return (0);
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

void	tokens_lst(char *line, t_list **tokens, char **dict)
{
	int	pos[3];

	pos[1] = 0;
	while (line[pos[1]])
	{
		pos[1] = skip_spaces(line, pos[1]);
		pos[0] = pos[1];
		while (line[pos[1]] && line[pos[1]] != ' ')
		{
			pos[2] = in_dict(&line[pos[1]], dict);
			if (pos[2] > 0)
			{
				if (pos[0] != pos[1] || (line[pos[1]] == 61
						&& (pos[1] - 1) >= 0 && line[pos[1] - 1] == ' '))
					add_token_lst(line, pos, tokens, 0);
				add_token_lst(line, pos, tokens, 1);
				pos[1] += check_special_symbol(&line[pos[1]], tokens) + pos[2];
				pos[0] = pos[1];
			}
			else
				pos[1]++;
		}
		if (pos[0] != pos[1])
			add_token_lst(line, pos, tokens, 0);
	}
}

void	print_tokens_lst(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		printf("%s$:  %d\n", token->str, token->type);
		tokens = tokens->next;
	}
}
