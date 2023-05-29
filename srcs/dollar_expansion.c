/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:14:58 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:32:39 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

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

void	dollar_var(char *var, t_list **lst, t_executer *executer)
{
	char	*value;

	printf("Var recortada: %s|\n", var);
	value = get_env_value(executer->env->env_lst, var);
	printf("Value es: %s\n", value);
	//if (!value)
	//	ft_lstadd_back(lst, ft_lstnew(ft_strdup(" ")));
	if (value)
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(value)));
		printf("Último añadido a la lista: %s\n", ft_lstlast(*lst)->content);
	}
	free(var);
}

char	*dollar_change(char *line, t_executer *executer)
{
	int		i;
	int		prev;
	int		dollar;
	char	*new;
	t_list	*words;

	i = 0;
	prev = 0;
	words = NULL;
	while (line[i])
	{
		//printf("Línea a recorrer: %s\n", &line[i]);
		if (line[i] == '$') //meter esto en otra funcion para ahorrar líneas
		{
			printf("Dollar\n");
			if (i > 0)
				ft_lstadd_back(&words, ft_lstnew(ft_substr(line, prev, i - prev)));
			dollar = i + 1;
			i++;
			if (line[dollar] == '?')
			{
				ft_lstadd_back(&words, ft_lstnew(ft_itoa(executer->last_return)));
				i += 2;
			}
			else if (line[dollar] == '\0')
				break ;
			else
			{
				while (line[i] && (line[i] != ' ' && line[i] != '$'
					&& ft_isalnum(line[i]) == 1))
						i++;
				dollar_var(ft_substr(line, dollar, i - dollar), &words, executer);
			}
			prev = i;
			printf("Final de comprobar dollar\n");
		}
		else
			i++;
	}
	if (prev != i)
		ft_lstadd_back(&words, ft_lstnew(ft_substr(line, prev, i - prev)));
	new = lst_to_str(words);
	ft_lstclear(&words, &free);
	free(line);
	return (new);
}
void	check_dollar_expansion(t_list **tokens, t_executer *executer)
{
	t_list	*curr;
	t_token	*token;

	curr = *tokens;
	while (curr)
	{
		token = get_token(curr);
		if (token->type == QUOTE) // a la hora de asignar tipo de token, saltarse quote simple para que no asigne lo que hay dentro
		{
			curr = curr->next;
			token = get_token(curr);
			while (token->type != QUOTE)
			{
				token->type = 0;
				curr = curr->next;
				token = get_token(curr);
			}
		}
		else if (token->type == DOLLAR)
		{
			token->str = dollar_change(token->str, executer);
			token->type = 0;
		}
		curr = curr->next;
	}
}
