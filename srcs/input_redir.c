/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/15 13:18:45 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*get_cmd_input(t_list *tokens, t_mshell *mshell)
{
	t_token	*token;
	char	*input_file;
	char	*here_doc_file;

	input_file = NULL;
	here_doc_file = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == REDIR_INPUT || token->type == HERE_DOC)
		{
			if (input_file)
				close(mshell->data.input);
			if (token->type == REDIR_INPUT)
				input_file = get_file_name(tokens->next);
			else if (token->type == HERE_DOC)
			{
				here_doc_file = get_here_doc_file(here_doc_file, mshell);
				input_file = here_doc_file;
			}
			mshell->data.input = open(input_file, O_RDONLY, 0666);
		}
		tokens = tokens->next;
	}
	return (input_file);
}
