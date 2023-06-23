/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:31:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 13:26:40 by pfuentes         ###   ########.fr       */
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
}	t_dir;

typedef struct s_btree
{
	void			*content;
	struct s_btree	*up;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_data{
	int		input;
	int		output;
	int		stdin;
	int		stdout;
	int		last_cmd;
	int		last_err;
	t_list	*pids_lst;
	t_list	*op_lst;
	int		pipes[2];
	int		prev_pipe;
	int		here_docs;
	int		here_doc_success;
	t_list	*here_doc;
	t_list	*env_lst;
	char	*input_file;
	char	*output_file;
	char	**tokens_dict;
	char	**paths;
	char	**env_matrix;
}	t_data;

typedef struct s_mshell
{
	t_data	data;
	char	*line;
	t_list	*tokens;
	t_btree	*parse_tree;
}	t_mshell;

typedef struct s_kv
{
	char	*key;
	char	*value;
	int		type;
}	t_kv;

//mshell struct

void	set_data(t_data *data, char **env);
void	reset_data(t_data *data);
void	set_mshell(t_mshell *mshell, char **env);
void	reset_mshell(t_mshell *mshell);

//lst functions
void	delete_node(t_list **lst, t_list **node);
void	lst_delete_node(t_list **node, void (*del)(void *));
void	lst_insert_node(t_list *node, t_list *add);
t_list	**lst_divide(int num, ...);
t_list	*lst_join(t_list **lst);
void	delete_node_str(t_list **lst, t_list *node);
void	remove_head(t_list **lst);
t_list	*find_node(t_list *lst, char *str);
t_list	*move_to_node(t_list	*lst, int pos);
char	*lst_to_str(t_list *lst);
char	*lst_to_str_spaces(t_list *lst);
void	sort_str_lst(t_list **lst);
void	swap_lst_nodes(t_list **node1, t_list **node2);

//tokens utils
char	*char_to_str(int c);
int		skip_to_char(char *str, char c);
int		skip_spaces(char *str, int pos);
int		last_word(char *str, int last);
int		next_word(char *str, int pos);
char	**create_tokens_dict(void);

//tokenizer

t_token	*new_token(char *str);
int		token_type(char *cmp, char **dict);
int		in_dict(char *entry, char **dict);
void	tokens_lst(char *line, t_list **tokens, char **dict);
void	assign_tokens_type(t_list **tokens, char **dict);
int		check_special_symbol(char *str, char **dict, t_list **tokens);
char	**create_tokens_dict(void);
void	print_tokens_lst(t_list *tokens);

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
t_list	*copy_env_lst(t_list	*env);
void	sort_env_lst(t_list	*lst);

//built-ins
void	cd(char **cmd, t_mshell *mshell);
void	echo(char **cmd, t_mshell *mshell);
void	env(char **cmd, t_mshell *mshell);
void	export(char **cmd, t_mshell *mshell);
void	pwd(char **cmd, t_mshell *mshell);
void	unset(char **cmd, t_list **env_lst, t_mshell *mshell);
void	b_exit(char **cmd, t_mshell *mshell);

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

//parser_tree
void	new_parser_tree(t_btree **tree);
void	tokens_skip(t_list **lst, int type);
void	tokens_skip_par(t_list **lst);
void	tokens_delete_par(t_list **lst);
int		lst_node_pos(t_list *lst, t_list *node);
void	lst_move_pos(t_list **lst, int pos);
t_token	*get_token(t_list *node);
int		tokens_check_operators(t_list	*lst);
void	tokens_delete_par(t_list **lst);
void	lst_divide_by_pos(t_list	**start, int end);
void	execute_parser_tree(t_btree *root, t_mshell *mshell);
void	free_parser_tree(t_btree **root);
void	set_pipes(t_btree *root, t_mshell *mshell);

//operators functions

void	subshell(t_btree *root, t_mshell *mshell);
void	pipe_op(t_btree *root, t_mshell *mshell);
void	pipe_dir(t_mshell *mshell);
void	and_op(t_btree *root, t_mshell *mshell);
void	or_op(t_btree *root, t_mshell *mshell);

//here_doc

char	*here_doc_op(t_mshell *mshell);
void	here_doc_initializer(t_btree *root, t_mshell *mshell);

//cmd
void	cmd_op(t_list **tokens, t_mshell *mshell);
char	**cmd_matrix(t_list *tokens);
void	cmd_type(char *cmd, t_mshell *mshell);
void	search_cmd(t_mshell *mshell, t_list *tokens);
void	execute_cmd(char **arg, t_mshell *mshell);
void	cmd_return(t_mshell *mshell, int status);

//redir
char	*get_file_name(t_list *tokens);
//char	*get_here_doc_file(char	*here_doc, t_mshell *mshell);
int		get_cmd_input(t_list *tokens, t_mshell *mshell);
void	set_output(char *output, int type, t_mshell *mshell);
char	*get_cmd_output(t_list *tokens, t_mshell *mshell);
void	and_or_redir(t_mshell *mshell, t_dir *dir);
int		set_redirections(t_list *tokens, t_mshell *mshell);

//pipex-execute cmd

char	**path_matrix(char **envp);
char	*correct_path(char **paths, char *command);

void	execute_cmd(char **arg, t_mshell *mshell);
void	parent_wait_cmd(t_mshell *mshell, int pid, int wstatus);
void	cmd_return(t_mshell *mshell, int status);
void	waitpid_pids(t_mshell *mshell);
void	new_pipes(t_mshell *mshell);
int		*get_pipes(t_list	*lst);
void	pipes_dir(t_mshell *mshell, t_dir *dir);
void	close_pipes(t_mshell *mshell, int type);
int		*int_ptr(int num);
void	after_execute_cmd(t_mshell *mshell);

//dollar expansion

char	*dollar_expansion(char *line, t_mshell *mshell);
void	check_sustitution(t_list *tokens, t_mshell *mshell);

//assign vars

void	var_assignment(t_list *tokens, t_mshell *mshell);
int		check_var_assignment(t_list **tokens, t_mshell *mshell);

//free structs

void	free_token(void *content);

//op lst

t_dir	*new_dir(int input, int output, int type);
t_dir	*get_dir(t_list *node);
void	first_pipe(t_mshell *mshell);
void	left_pipe(t_mshell *mshell);
void	right_pipe(t_mshell *mshell);
void	op_add_pipes(t_btree *root, t_mshell *mshell);
void	op_add_or_and(t_btree *root, t_mshell *mshell, int type);
void	op_lst(t_btree *root, t_mshell *mshell);
void	assign_dirs_op(t_mshell *mshell);
void	print_op_lst(t_list *lst);

//utils

int		*int_ptr(int num);

//signals

void	ctrl_c_signal(void);
void	signal_handler_parent(int signal);
void	signals_parent(void);
void	ctrl_4_signal_child(void);
void	signal_handler_child(int signal);
void	signals_child(void);
void	signal_handler_parent(int signal);
void	signal_handler_parent_wait(int signal);
void	signals_parent_wait(void);

//wildcards

char	*call_wildcards(char *str);
char	**new_wildcards_dict(void);
void	wildcards(t_list *tokens, t_list **wildcards_lst, char *path);
void	add_entry_wildcards(t_list **wildcards_lst, char *path, char *entry);
int		check_entry(t_list *tokens, struct dirent *ent,
			t_list **wildcards_lst, char *path);
char	*entry_to_add(t_list *tokens, char *entry);

//ft_func

int		ft_dup(int fd);
void	ft_dup2(int fd1, int fd2);
void	ft_close(int fd);
void	*ft_malloc(int size);
int		ft_open(char *file, int type);

#endif