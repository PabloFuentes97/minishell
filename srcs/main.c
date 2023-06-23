/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:48:23 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/23 10:57:40 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

int	lexer(t_mshell *mshell)
{
	mshell->line = readline("minishell> ");
	if (!mshell->line)
	{
		free(mshell->line);
		exit(errno);
	}
	if (!(*mshell->line))
		return (0);
	add_history(mshell->line);
	tokens_lst(mshell->line, &mshell->tokens, mshell->data.tokens_dict);
	if (!mshell->tokens)
		return (0);
	assign_tokens_type(&mshell->tokens, mshell->data.tokens_dict);
	if (syntax_analizer(mshell->tokens) == 1)
		return (1);
	ft_lstclear(&mshell->tokens, &free_token);
	return (0);
}

void	parser(t_mshell *mshell)
{
	mshell->parse_tree = btree_new_node(mshell->tokens);
	new_parser_tree(&mshell->parse_tree);
}

void	executer(t_mshell *mshell)
{
	op_lst(mshell->parse_tree, mshell);
	assign_dirs_op(mshell);
	print_op_lst(mshell->data.op_lst);
	here_doc_initializer(mshell->parse_tree, mshell);
	if (!mshell->data.here_doc)
		mshell->data.here_docs = -1;
	if (mshell->data.here_doc_success == 0)
		ft_lstclear(&mshell->data.here_doc, &free);
	else
		execute_parser_tree(mshell->parse_tree, mshell);
}

void	minishell(t_mshell *mshell)
{
	if (lexer(mshell) == 1)
		parser(mshell);
	executer(mshell);
	reset_mshell(mshell);
}

int	main(int argc, char **argv, char **env)
{
	t_mshell			mshell;

	if (argc > 1 || !argv)
		return (1);
	signals_parent();
	set_mshell(&mshell, env);
	while (1)
	{
		minishell(&mshell);
	}
}
