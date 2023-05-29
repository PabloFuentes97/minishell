/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:51:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 10:58:17 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

t_tokenizer	*init_tokenizer(void)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	tokenizer->start = 0;
	tokenizer->end = 0;
	tokenizer->op_len = 0;
	return (tokenizer);
}

t_lexer	*init_lexer(void)
{	
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->line = readline("minishell> ");
	if ((!lexer->line) || !(*lexer->line))
		b_exit(errno);
	add_history(lexer->line);
	lexer->dict = create_tokens_dict();
	lexer->tokens = NULL;
	lexer->tokenizer = init_tokenizer();
	tokens_lst(lexer);
	set_tokens_type(lexer);
	print_tokens_lst(lexer->tokens);
	return (lexer);
}

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->tree = btree_new_node(lexer->tokens);
	new_parser_tree(&parser->tree);
	parser_tree_print(parser->tree);
	return (parser);
}

t_op	*init_ops(void)
{
	t_op	*ops;

	ops = malloc(sizeof(t_op));
	ops->concat_left = 0;
	ops->concat_right = 0;
	ops->pids_lst = NULL;
	ops->op_lst = NULL;
	ops->pipes_lst = NULL;
	ops->pipe_file = NULL;
	return (ops);
}

t_dirs	*init_dirs(void)
{
	t_dirs	*dirs;

	dirs = malloc(sizeof(t_dir));
	dirs->input = STDIN_FILENO;
	dirs->output = STDOUT_FILENO;
	dirs->stdin = dup(STDIN_FILENO);
	dirs->stdout = dup(STDOUT_FILENO);
	dirs->input_file = NULL;
	dirs->output_file = NULL;
	dirs->here_doc_num = 0;
	dirs->here_docs = NULL;
	return (dirs);
}

t_env	*init_env(char **env_matrix)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env_matrix)
		env->env_matrix = env_matrix;
	env->env_lst = set_env_list(env_matrix);
	return (env);
}

t_executer	*init_executer(t_parser *parser, char **env)
{
	t_executer	*executer;

	executer = malloc(sizeof(t_executer));
	executer->parser = parser;
	executer->root = parser->tree;
	executer->env = init_env(env);
	executer->dirs = init_dirs();
	executer->ops = init_ops();
	op_lst(executer->root, executer);
	print_op_lst(executer->ops->op_lst);
	executer->paths = path_matrix(env);
	executer->cmd = NULL;
	executer->shell_lev = 0;
	execute_parser_tree(executer->root, executer);
	return (executer);
}

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->lexer = init_lexer();
	mshell->parser = init_parser(mshell->lexer);
	mshell->executer = init_executer(mshell->parser, env);
}
/*
void	reset_mshell(t_mshell *mshell)
{
	reset_data(&mshell->data);
	free(mshell->line);
	mshell->line = NULL;
	mshell->tokens = NULL;
	free_parser_tree(&mshell->parse_tree);
	mshell->data.op_lst = NULL;
	mshell->parse_tree = NULL;
}
void	set_data(t_data *data, char **env)
{
	data->stdin = dup(STDIN_FILENO);
	printf("Stdin: %d\n", data->stdin);
	data->stdout = dup(STDOUT_FILENO);
	printf("Stdout: %d\n", data->stdout);
	data->input = data->stdin;
	data->output = data->stdout;
	data->paths = path_matrix(env);
	data->cmd_type = 0;
	data->tokens_dict = create_tokens_dict();
	data->env_matrix = env;
	data->env_lst = set_env_list(env);
	data->here_docs = 0;
	data->here_doc = NULL;
	data->pipes_lst = NULL;
	data->op_lst = NULL;
	data->pids_lst = NULL;
	data->subshell = 0;
	data->inside_par = 0;
	data->dollar_par = 0;
}

void	reset_data(t_data *data)
{
	data->input = data->stdin;
	dup2(data->stdin, STDIN_FILENO);
	data->output = data->stdout;
	dup2(data->stdout, STDOUT_FILENO);
	data->cmd_type = 0;
	data->here_docs = 0;
	data->here_doc = NULL;
	ft_lstclear(&data->pipes_lst, &free);
	data->pipes_lst = NULL;
	ft_lstclear(&data->op_lst, &free);
	data->op_lst = NULL;
	ft_lstclear(&data->pids_lst, &free);
	data->pids_lst = NULL;
	data->subshell = 0;
	data->inside_par = 0;
	data->dollar_par = 0;
	data->link_par_pipe = 0;
}
*/
