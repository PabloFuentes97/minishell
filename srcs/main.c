/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:48:23 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 12:46:58 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

int	minishell(t_mshell *mshell)
{
	init_lexer(&mshell->lexer);
}

int	main(int argc, char **argv, char **env)
{
	t_mshell			mshell;

	if (argc > 1 || !argv)
		return (1);
	signals_parent();
	while (1)
	{
		system("leaks -q minishell");
		mshell.line = readline("minishell> ");
		if ((!mshell.line) || !(*mshell.line))
			b_exit(errno);
		add_history(mshell.line);
		tokens_lst(mshell.line, &mshell.tokens, mshell.data.tokens_dict);
		assign_tokens_type(&mshell.tokens, mshell.data.tokens_dict);
		print_tokens_lst(mshell.tokens);
		if (syntax_analizer(mshell.tokens) == 0)
			continue ;
		mshell.parse_tree = btree_new_node(mshell.tokens);
		new_parser_tree(&mshell.parse_tree);
		op_lst(mshell.parse_tree, &mshell);
		print_op_lst(mshell.data.op_lst);
		here_doc_initializer(mshell.parse_tree, &mshell);
		execute_parser_tree(mshell.parse_tree, &mshell);
		reset_mshell(&mshell);
	}
	b_exit(errno);
}
