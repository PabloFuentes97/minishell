#include "../includes/minishell.h" 
#include "../libft/libft.h"

t_token	*get_token(t_list *node)
{
	t_token	*token;

	token = (t_token *)node->content;
	return (token);
}

char	*char_to_str(int c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	skip_spaces(char *str, int pos)
{
	while (str[pos] == ' ')
		pos++;
	return (pos);
}

int	last_word(char *str, int last)
{
	if (str[last] == ' ')
	{
		while (last >= 0 && str[last] == ' ')
			last--;
	}
	return (last);
}

int	next_word(char *str, int pos)
{
	while (str[pos] != ' ')
		pos++;
	return (pos);
}

char	**new_unlim_matrix(int n, ...)
{
	int		i;
	char	**matrix;
	va_list	lst;

	va_start(lst, n);
	matrix = malloc(sizeof(char *) * n + 1);
	i = 0;
	while (i < n)
	{
		matrix[i] = ft_strdup(va_arg(lst, char *));
		i++;
	}
	matrix[i] = NULL;
	va_end(lst);
	return (matrix);
}

char	**create_tokens_dict(void)
{
	char 	*d_quote;
	char	**dict;

	d_quote = char_to_str(34);
	dict = new_unlim_matrix(13, "||", "&&", "|", "<<",
			"<", ">>", ">", "(", ")", "'", d_quote, "=", "$", "*");
	free(d_quote);
	return (dict);
}
