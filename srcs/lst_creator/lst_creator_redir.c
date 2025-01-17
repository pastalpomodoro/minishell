/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:06:33 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:07:46 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	adding(t_tkn_lst **lst, char *input, int i, char c)
{
	int			start;
	int			token;
	t_tkn_lst	*node;

	token = 0;
	if (input[i] == c && input[i + 1] == c)
	{
		i++;
		token = 1;
	}
	i++;
	while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
		i++;
	start = i;
	while (is_space(input[i], "\t\n\v\f\r ") && input[i] != c && input[i])
		i++;
	node = my_new_node(ft_substr(input, start, i - start));
	if (!node)
		return (free_branche(*lst), 0);
	if (token == 1)
		node->token = T_DLESS;
	else
		node->token = T_LESS;
	my_node_addfront_branche(lst, node);
	return (i);
}

//me rappeler que quand il y a << il faut l executer dans tout les cas meme 
//s'il y a une commande 
//me rapperler de free lst une foi que tout est finis ou sy il y a un probleme
t_tkn_lst	*fill_branche(char *input, char c)
{
	int			i;
	t_tkn_lst	*lst;

	lst = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			i = adding(&lst, input, i, c);
			if (i == 0)
			{
				free_branche(lst);
				break ;
			}
		}
		else
		i++;
	}
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
int	take_index_last_right(t_tkn_lst **node_out, char *input)
{
	int	i;
	int	save;

	i = 0;
	save = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
		{
			node_out[0]->token = T_DGREAT;
			i += 2;
			save = i;
		}
		else if (input[i] == '>')
		{
			node_out[0]->token = T_GREAT;
			i++;
			save = i;
		}
		else
			i++;
	}
	return (save);
}

int	find_outfile(t_tkn_lst **node_out, char *input)
{
	int		i;
	int		start;
	char	*file;

	node_out[0] = my_new_node(NULL);
	if (!node_out)
		return (ft_printf("Erreur malloc node_out find_outfile"), 1);
	i = take_index_last_right(node_out, input);
	while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
		i++;
	start = i;
	while (is_space(input[i], "\t\n\v\f\r ") && input[i])
		i++;
	file = ft_substr(input, start, i - start);
	if (!file)
		return (ft_printf("Malloc error in find outfile"), 1);
	if (ft_strlen(file) != 0)
		node_out[0]->value = file;
	else
	{
		free(file);
		free(node_out[0]);
		node_out[0] = NULL;
	}
	return (0);
}