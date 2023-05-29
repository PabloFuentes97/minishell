NAME = minishell

SRCS =	srcs/binary_tree.c srcs/parser_tree.c srcs/cmd.c srcs/command_paths.c \
srcs/dollar_expansion.c srcs/env_lst_functions.c srcs/here_doc.c srcs/lst_functions.c \
srcs/operators_func.c srcs/parser_tree_utils.c srcs/redir.c srcs/assign_var.c \
srcs/signals.c srcs/syntax_analizer.c srcs/tokenizer.c srcs/tokens_utils.c \
srcs/pipes.c srcs/pipes_lst.c srcs/token.c srcs/execute_tree.c \
srcs/mshell_struct.c srcs/built-ins/cd.c srcs/built-ins/echo.c srcs/built-ins/exit.c \
srcs/built-ins/export.c srcs/built-ins/pwd.c srcs/built-ins/unset.c \
srcs/cmd_matrix.c srcs/execute_cmd.c srcs/dir.c srcs/op_lst.c \
new_main.c

OBJS	= $(SRCS:.c=.o)

LIBFT_A = libft.a

CC		= gcc

READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

CCFLAGS	= -Wall -Werror -Wextra -Ilibft -I/Users/$(USER)/.brew/opt/readline/include


#-Ilibft en CFLAGS

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
			$(CC) $(CCFLAGS) $(READLINE) $(OBJS) $(LIBFT_A) -o $(NAME)

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