#include "../includes/minishell.h"
#include "../libft/libft.h"

t_list	*get_dollar_par(t_mshell *mshell)
{
	t_list	*lst;
	int		fd;
	char	*line;
	char	**matrix;
	char	*file;
	int		cont;

	cont = 0;
	lst = NULL;
	file = str_num(ft_strdup(".dollar_par"), mshell->data.subshell + 1);
	printf("Fichero de dollar_par para leer: %s\n", file);
	fd = open(file, O_RDONLY, 0666);
	if (fd < 0)
		printf("Error al abrir dollar_par\n");
	line = get_next_line(fd);
	while (line) //esto añadirlo como matriz, hacer un split de la linea y añadir array a array a la lista
	{
		line = str_no_spaces(line);
		matrix = ft_split(line, ' ');
		while (matrix[cont])
		{
			ft_lstadd_back(&lst, ft_lstnew(new_token(matrix[cont])));
			cont++;
		}
		cont = 0;
		free(line);
		free(matrix);
		matrix = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	unlink(file);
	free(file);
	t_list *print = lst;
	printf("Imprimir lista completa en get_dollar_par\n");
	while (print)
	{
		printf("%s\n", get_token(print)->str);
		print = print->next;
	}
	printf("Sale de get_dollar_par\n");
	return (lst);
}

void	dollar_par(t_list **tokens, t_mshell *mshell)
{
	char	*file;
	int		fd;
	int		stdout;
	t_btree	*tree;
	t_list	*print;
	printf("Va a hacer árbol de dollar_par\n");
	print = *tokens;
	printf("Imprimo tokens de dollar_par\n");
	while (print)
	{
		printf("%s\n", get_token(print)->str);
		print = print->next;
	}
	file = str_num(ft_strdup(".dollar_par"), mshell->data.subshell + 1);
	printf("Fichero de dollar_par para escribir: %s\n", file);
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0)
		printf("Error al abrir dollar_par\n");
	free(file);
	stdout = mshell->data.stdout;
	mshell->data.stdout = fd;
	mshell->data.output = mshell->data.stdout;
	printf("Nuevo stdout, fichero de dollar_par: %d\n", mshell->data.stdout);
	printf("Va a crear árbol nuevo\n");
	tree = btree_new_node(*tokens);
	mshell->data.dollar_par = 1;
	new_parser_tree(&tree);
	execute_parser_tree(tree, mshell);
	free_parser_tree(&tree);
	*tokens = get_dollar_par(mshell);
	close(fd);
	//hacer una funcion de reset data y resetar solo los redir
	mshell->data.stdout = stdout;
	mshell->data.output = mshell->data.stdout;
	mshell->data.dollar_par = 0;
}

void	dollar_par_head(t_list **lst, t_mshell *mshell)
{
	t_list	*right;

	printf("Dollar es el primer nodo\n");
	right = (*lst)->next;
	lst_delete_node(lst, &free_token);
	(*lst) = right;
	tokens_skip_par(&right);
	right = right->next; //me muevo al siguiente al paréntesis
	if (right)
	{
		right->prev->next = NULL;
		right->prev = NULL;
		printf("Hay más tokens después del dollar_par\n");
	}
	dollar_par(lst, mshell);
	if (right)
		ft_lstadd_back(lst, right);
}

void	dollar_par_between(t_list **lst, t_list **dollar, t_mshell *mshell)
{
	t_list	*right;

	(*dollar)->prev->next = NULL;
	(*dollar)->prev = NULL;
	right = (*dollar)->next;
	lst_delete_node(dollar, &free_token);
	*dollar = NULL;
	*dollar = right;
	tokens_skip_par(&right);
	right = right->next;
	if (right)
	{
		right->prev->next = NULL;
		right->prev = NULL;
		printf("Hay más tokens después del dollar_par\n");
	}
	dollar_par(dollar, mshell);
	ft_lstadd_back(lst, *dollar);
	if (right)
		ft_lstadd_back(lst, right);
}

void	call_dollar_par(t_list **lst, t_mshell *mshell)
{
	t_list	*right;
	t_list	*dollar;
	t_list	*curr;

	curr = *lst;
	dollar = NULL;
	right = NULL;
	printf("Encontró $(, dentro de call_dollar_par\n");
	while (curr)
	{
		if (get_token(curr)->type == DOLLAR_PAR)
		{
			printf("Es dollar_par\n");
			if (!curr->prev)
				dollar_par_head(lst, mshell);
			else
				dollar_par_between(lst, &curr, mshell);
			break ;
		}
		curr = curr->next;
	}
	t_list *print = *lst;
	printf("Imprimir lista completa al hacer dollar_par\n");
	while (print)
	{
		printf("Token: %s\n", get_token(print)->str);
		print = print->next;
	}
	printf("---------------TERMINÓ DOLLAR_PAR------------\n\n\n");
}
