/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dict.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:15:13 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/12 14:00:14 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	in_dict(char *entry, char **dict)
{
	int	i;

	i = 0;
	while (i < DOLLAR - 1)
	{
		if (ft_strncmp(dict[i], entry, ft_strlen(dict[i])) == 0)
			return (ft_strlen(dict[i]));
		i++;
	}
	return (0);
}

char	**create_tokens_dict(void)
{
	char	*d_quote;
	char	**dict;

	d_quote = char_to_str(34);
	dict = malloc(sizeof(char *) * 15);
	dict[0] = ft_strdup("||");
	dict[1] = ft_strdup("&&");
	dict[2] = ft_strdup("|");
	dict[3] = ft_strdup("<<");
	dict[4] = ft_strdup("<");
	dict[5] = ft_strdup(">>");
	dict[6] = ft_strdup(">");
	dict[7] = ft_strdup("(");
	dict[8] = ft_strdup(")");
	dict[9] = ft_strdup("'");
	dict[10] = ft_strdup(d_quote);
	dict[11] = ft_strdup("=");
	dict[12] = ft_strdup("$");
	dict[13] = ft_strdup("*");
	dict[14] = NULL;
	free(d_quote);
	return (dict);
}
