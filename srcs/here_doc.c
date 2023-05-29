/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:35:06 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 10:58:30 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	compare_here_doc(char *here_doc, char *lim)
{
	int		len;
	char	*here_doc_mod;
	int		cont;

	here_doc_mod = malloc(sizeof(char) * ft_strlen(here_doc));
	cont = 0;
	while (here_doc[cont] != '\n')
	{
		here_doc_mod[cont] = here_doc[cont];
		cont++;
	}
	here_doc_mod[cont] = '\0';
	if (ft_strlen(here_doc_mod) > ft_strlen(lim))
		len = ft_strlen(here_doc_mod);
	else
		len = ft_strlen(lim);
	free(here_doc_mod);
	return (len);
}

char	*here_doc(char *lim, int num)
{
	char	*line;
	char	*here_doc_name;
	int		here_doc;
	char	*str_num;
	int		len;

	str_num = ft_itoa(num);
	here_doc_name = ft_strjoin("here_doc", str_num);
	free(str_num);
	here_doc = open(here_doc_name, O_CREAT | O_RDWR
			| O_APPEND | O_TRUNC, 0666);
	if (here_doc < 0)
	{
		perror("Archivo here_doc no pudo crearse y abrirse\n");
		exit(EXIT_FAILURE);
	}
	write(1, "pipe heredoc> ", 14);
	line = get_next_line(0);
	len = compare_here_doc(line, lim);
	while (ft_strncmp(line, lim, len) != 0)
	{
		write(here_doc, line, ft_strlen(line));
		free(line);
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		len = compare_here_doc(line, lim);
	}
	free(line);
	close(here_doc);
	printf("Nombre de here_doc: %s\n", here_doc_name);
	return (here_doc_name);
}

void	here_doc_initializer(t_btree *root, t_executer *executer)
{	
	t_list		*tokens;
	t_token		*token;

	if (!root)
		return ;
	tokens = root->content;
	token = tokens->content;
	if (token->type == CMD || token->type > PIPE)
	{
		while (tokens)
		{
			if (get_token(tokens)->type == HERE_DOC)
			{
				executer->dirs.here_doc_num++;
				ft_lstadd_back(&(executer->dirs.here_docs),
					ft_lstnew(((void *)here_doc(get_token(tokens->next)->str,
								executer->dirs.here_doc_num))));
				return ;
			}
			tokens = tokens->next;
		}
	}
	here_doc_initializer(root->left, executer);
	here_doc_initializer(root->right, executer);
}
