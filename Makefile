NAME = minishell

SRCS =	srcs/assign_token_type.c srcs/after_execute.c srcs/assign_var.c srcs/binary_tree.c \
srcs/check_syntax.c srcs/check_syntax2.c srcs/cmd.c srcs/cmd_matrix.c \
srcs/command_paths.c srcs/dir.c srcs/dollar_expansion.c srcs/env_lst_functions.c srcs/env_lst_functions2.c \
srcs/env_lst_functions3.c srcs/execute_cmd.c srcs/ft_funcs.c srcs/here_doc.c srcs/lst_functions.c \
srcs/lst_functions2.c srcs/mshell_struct.c srcs/check_sustitution.c \
srcs/op_lst.c srcs/op_lst_pipes.c srcs/op_lst_and_or.c srcs/operators_func.c srcs/new_parser_tree.c srcs/parser_tree.c \
srcs/parser_tree_utils.c srcs/pipes.c srcs/redir.c srcs/input_redir.c srcs/output_redir.c \
srcs/signal_parent.c srcs/signal_child.c srcs/str_utils.c srcs/syntax_analizer.c \
srcs/token.c srcs/token_dict.c srcs/tokenizer.c srcs/tokens_utils.c \
srcs/wait_child.c srcs/built-ins/cd.c srcs/built-ins/echo.c srcs/built-ins/env.c srcs/built-ins/exit.c \
srcs/built-ins/export.c srcs/built-ins/pwd.c srcs/built-ins/unset.c \
srcs/wildcards.c srcs/wildcards_utils.c srcs/wildcards_utils2.c srcs/main.c
OBJS	= $(SRCS:.c=.o)

LIBFT_A = libft.a

CC		= gcc

READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

CCFLAGS	= -Wall -Werror -Wextra -Ilibft -I/Users/$(USER)/.brew/opt/readline/include


#-Ilibft en CFLAGS

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
			$(CC) $(CCFLAGS) $(READLINE) $(OBJS) $(LIBFT_A) -o $(NAME)
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_A):
		make bonus -C libft
		cp libft/libft.a .
clean:
		make -C libft clean
		rm -f $(OBJS)
fclean: clean
		@make -C libft fclean
		rm -f libft.a
		rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re  