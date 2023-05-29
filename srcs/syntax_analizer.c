#include "../includes/minishell.h"
#include "../libft/libft.h"

int	valid_num_par(t_list *tokens)
{
	int		open;
	int		close;
	t_token	*token;

	open = 0;
	close = 0;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == OPEN_PAR)
			open++;
		else if (token->type == CLOSE_PAR)
			close++;
		tokens = tokens->next;
	}
	if (open == close)
		return (1);
	printf("Syntax error: invalid number of parenthesis\n");
	return (0);
}

int	valid_num_quotes(t_list *tokens)
{
	int		quotes;
	int		type;

	quotes = 0;
	while (tokens)
	{
		if (get_token(tokens)->type == D_QUOTE
			|| get_token(tokens)->type == QUOTE)
		{
			quotes++;
			type = get_token(tokens)->type;
			tokens = tokens->next;
			while (tokens && get_token(tokens)->type != type)
				tokens = tokens->next;
			if (tokens)
				quotes++;
			else
				break ;
		}
			tokens = tokens->next;
	}
	if (quotes % 2 == 0)
		return (1);
	printf("Syntax error: invalid number of quotes\n");
	return (0);
}

int	valid_redirections(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type >= HERE_DOC
			&& token->type <= REDIR_OUTPUT_TRUNC)
		{
			if (!tokens->next)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (0);
			}	
			if (get_token(tokens->next)->type >= HERE_DOC
				&& get_token(tokens->next)->type <= REDIR_OUTPUT_TRUNC)
			{
				printf("Syntax error near unexpected token `%s'\n",
					get_token(tokens->next)->str);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	valid_op_pos(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type >= OR && token->type <= PIPE)
		{
			if (!tokens->prev || !tokens->next)
			{
				printf("Syntax error near unexpected token `%s'\n",
					get_token(tokens)->str);
				return (0);
			}
			if (get_token(tokens->next)->type >= OR
				&& get_token(tokens->next)->type <= PIPE)
			{
				printf("Syntax error near unexpected token `%s'\n",
					get_token(tokens->next)->str);
				return (0);
			}	
		}
		tokens = tokens->next;
	}
	return (1);
}

int	valid_par_pos(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == CMD
			|| (token->type >= HERE_DOC && token->type <= REDIR_OUTPUT_TRUNC))
		{
			if (tokens->next && get_token(tokens->next)->type == OPEN_PAR)
			{
				printf("Syntax error near unexpected token `('\n");
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	valid_assignment(t_list *tokens)
{
	while (tokens)
	{
		if (get_token(tokens)->type == ASSIGN)
		{
			if (!tokens->prev)
			{
				printf("Sintax error: invalid assignment\n");
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	syntax_analizer(t_list *tokens)
{
	if (valid_num_par(tokens) == 0)
		return (0);
	if (valid_num_quotes(tokens) == 0)
		return (0);
	if (valid_redirections(tokens) == 0)
		return (0);
	if (valid_op_pos(tokens) == 0)
		return (0);
	if (valid_par_pos(tokens) == 0)
		return (0);
	if (valid_assignment(tokens) == 0)
		return (0);
	return (1);
}
