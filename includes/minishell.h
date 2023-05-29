/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:31:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 10:58:28 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"

# define CMD 0
# define OR 1
# define AND 2
# define PIPE 3
# define HERE_DOC 4
# define REDIR_INPUT 5
# define REDIR_OUTPUT_APPEND 6
# define REDIR_OUTPUT_TRUNC 7
# define OPEN_PAR 8
# define CLOSE_PAR 9
# define QUOTE 10
# define D_QUOTE 11
# define ASSIGN 12
# define DOLLAR 13
# define WILD_CARDS 14

//cmd type
# define CD 0
# define ECHO 1
# define EXIT 2
# define EXPORT 3
# define PWD 4
# define UNSET 5
# define EXECVE 6

//pipes define
# define PIPE_READ 257
# define PIPE_WRITE 258

extern int	errno;

typedef struct s_token
{
	char	*str;
	int		type;
}	t_token;

typedef struct s_dir
{
	int	input;
	int	output;
	int	type;
	int	*pipe;
}	t_dir;

typedef struct s_btree
{
	void			*content;
	struct s_btree	*up;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_kv
{
	char	*key;
	char	*value;
	int		type;
}	t_kv;

typedef struct s_tokenizer
{
	int	start;
	int	end;
	int	op_len;
}	t_tokenizer;

typedef struct s_lexer{
	char		*line;
	char		**dict;
	t_tokenizer	*tokenizer;
	t_list		*tokens;
}	t_lexer;

typedef struct s_parser{
	t_btree	*tree;
}	t_parser;

typedef struct s_op{
	int		concat_left;
	int		concat_right;
	t_list	*op_lst;
	t_list	*pids_lst;
	t_list	*pipes_lst;
	char	*pipe_file;
}	t_op;

typedef struct s_dirs{
	int		input;
	int		output;
	int		stdin;
	int		stdout;
	char	*input_file;
	char	*output_file;
	t_list	*here_docs;
	int		here_doc_num;
}	t_dirs;

typedef struct s_env{
	t_list	*env_lst;
	char	**env_matrix;
}	t_env;

typedef struct s_executer{
	t_parser	*parser;
	t_btree		*root;
	t_op		*ops;
	t_dirs		*dirs;
	t_env		*env;
	char		**cmd;
	char		**paths;
	int			last_return;
	int			shell_lev;
}	t_executer;

typedef struct s_mshell{
	t_lexer		*lexer;
	t_parser	*parser;
	t_executer	*executer;
}	t_mshell;


t_tokenizer	*init_tokenizer(void);
t_lexer		*init_lexer(void);
t_parser	*init_parser(t_lexer *lexer);
t_op		*init_ops(void);
t_dirs		*init_dirs(void);
t_env		*init_env(char **env_matrix);
t_executer	*init_executer(t_parser *parser, char **env);
void		init_mshell(t_mshell *mshell, char **env);
void		set_mshell(t_mshell *mshell, char **env);
void		reset_mshell(t_mshell *mshell);

//lst functions
void	delete_node(t_list **lst, t_list **node);
void	lst_delete_node(t_list **node, void (*del)(void *));
void	lst_insert_node(t_list *node, t_list *add);
t_list	**lst_divide(int num, ...);
t_list	*lst_join(t_list **lst);
void	lst_delete_sublst(t_list **head, t_list *last, int inc, void (*del) (void *));
void	delete_node_str(t_list **lst, t_list *node);
void	remove_head(t_list **lst);
t_list	*find_node(t_list *lst, char *str);
t_list	*move_to_node(t_list	*lst, int pos);
char	*lst_to_str(t_list *lst);

//tokens utils
char	*char_to_str(int c);
int		skip_spaces(char *str, int pos);
int		last_word(char *str, int last);
int		next_word(char *str, int pos);
char	**new_unlim_matrix(int n, ...);
char	**create_tokens_dict(void);

//token

t_token	*new_token(char *str);
t_token	*get_token(t_list *node);
void	free_token(void *content);
void	set_tokens_type(t_lexer *lexer);
int		set_token_type(char *cmp, char **dict);

//tokenizer

void	in_dict(t_lexer *lexer);
void	add_token_lst(t_lexer *lexer, int type);
void	add_tokens_quotes(t_lexer *lexer, int type);
void	add_tokens_assign(t_lexer *lexer);
void	special_symbols(t_lexer *lexer);
void	tokens_lst(t_lexer *lexer);
char	**create_tokens_dict(void);
void	print_tokens_lst(t_list *tokens);

//syntax analizer

int		valid_num_par(t_list *tokens);
int		valid_num_quotes(t_list *tokens);
int		valid_redirections(t_list *tokens);
int		valid_op_pos(t_list *tokens);
int		valid_par_pos(t_list *tokens);
int		valid_assignment(t_list *tokens);
int		syntax_analizer(t_list *tokens);

//binary tree

t_btree	*btree_new_node(void *content);
void	btree_add_left_node(t_btree **root, t_btree *new);
void	btree_add_right_node(t_btree **root, t_btree *new);
void	btree_add_up_node(t_btree **root);
void	parser_tree_print(t_btree *root);

//parser_tree

void	new_parser_tree(t_btree **tree);
void	tokens_skip(t_list **lst, int type);
void	tokens_skip_par(t_list **lst);
void	tokens_delete_par(t_list **lst);
int		tokens_check_operators(t_list	*lst);
void	tokens_delete_par(t_list **lst);
void	execute_parser_tree(t_btree *root, t_executer *executer);
void	free_parser_tree(t_btree **root);
void	execute_pipes_tree(t_btree *root, t_executer *executer);
void	print_pipes_lst(t_list *pipes);

//env functions

t_kv	*set_key_value(char *key, char *value, int type);
t_kv	*get_key_value(t_list *node);
void	set_var_type(t_list **node, int type);
t_list	*set_env_node(char *env_var);
t_list	*set_env_list(char **env);
void	print_env_lst(t_list *env_lst);
void	print_str_lst(t_list *str_list);
char	*get_env_key(t_list	**lst, t_list **node);
char	*get_env_value(t_list	*lst, char *cmp);
t_list	*get_node_by_key(t_list	*lst, char *cmp);
void	set_env_value(t_list **env_lst, char *key, char *new_value);
char	**env_lst_to_matrix(t_list *env_lst);
void	free_key_value(void *content);

//here_doc

char	*here_doc(char *lim, int num);
void	here_doc_initializer(t_btree *root, t_executer *executer);

//operators functions

void	subshell(t_btree *root, t_executer *executer);
void	pipe_op(t_btree *root, t_executer *executer);
void	pipe_dir(t_executer *executer);
void	and_op(t_btree *root, t_executer *executer);
void	or_op(t_btree *root, t_executer *executer);
void	cmd_op(t_list **tokens, t_executer *executer);

//cmd

char	**cmd_matrix(t_list *tokens);
void	search_cmd(t_executer *executer);
void	execute_cmd(char **arg, t_executer *executer);
void	cmd_return(t_executer *executer, int status);

//pipes 

void	new_pipe(t_executer *executer);
void	close_pipe(t_executer *executer);

//op

void	op_lst(t_btree *root, t_executer *executer);
void	print_op_lst(t_list *lst);

//dir

t_dir	*new_dir(int input, int output, int type);
t_dir	*get_dir(t_list *node);
void	free_dir(t_dir *dir);

//redir

void	cmd_input(t_list *tokens, t_executer *executer);
void	here_doc_dir(t_dirs *dirs);
void	cmd_output(t_list *tokens, t_executer *executer);
void	set_redirections(t_list *tokens, t_executer *executer);
void	reset_dirs(t_executer *executer);

//built-ins

void	cd(char **cmd, t_executer *executer);
void	echo(char **cmd, t_executer *executer);
void	export(char **cmd, t_executer *executer);
void	pwd(t_executer *executer);
void	unset(char **cmd, t_executer *executer);
void	b_exit(int value);

//execve

char	**path_matrix(char **envp);
char	*correct_path(char **paths, char *command);
void	free_matrix(void **matrix);
void	execute_cmd(char **arg, t_executer *executer);
int		*int_ptr(int num);
void	parent_wait_cmd(t_executer *executer, int pid);
void	waitpid_pids(t_executer *executer);

//dollar expansion

void	dollar_var(char *var, t_list **lst, t_executer *executer);
char	*dollar_change(char *line, t_executer *executer);
void	check_dollar_expansion(t_list **tokens, t_executer *executer);

//assign vars

void	var_assignment(t_list *tokens, t_executer *executer);
int		check_var_assignment(t_list **tokens, t_executer *executer);

//utils

char	*ft_strjoin_variadic(int n, ...);

//signals

void	signal_handler_parent(int signal);
void	signals_parent(void);

#endif