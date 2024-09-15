/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:26:06 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 18:08:03 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token_list	*ft_new_element(char *str);
static int			ft_is_one_after_the_other(char *input, int i);

/*Fonction qui initialise une liste doublement chaînée
qui stockera les différentes chaîne de caractères
de l'input et les tokens associé.*/

int	ft_lst_init(char *input, t_minishell *mini, int i, int q_s)
{
	int	start;

	while (input[i] != '\0')
	{
		while (input[i] == ' ' && !q_s)
			i++;
		start = i;
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|') && !q_s)
			i += ft_is_one_after_the_other(input, i);
		else
		{
			while (input[i] && (input[i] != ' ' || q_s) && \
			((input[i] != '<' && input[i] != '>' && input[i] != '|') || q_s))
				q_s = ft_change_quote_state(input[i++], q_s);
			if (q_s)
				return (printf("Error : Quote not closed.\n"), 0);
		}
		if (!ft_lst_fill(i - start, start, input, mini))
			return (printf("Error : Malloc error\n"), 0);
		while (input[i] == ' ' && !q_s)
			i++;
	}
	return (1);
}

static int	ft_is_one_after_the_other(char *input, int i)
{
	if (input[i + 1] == input[i])
		return (2);
	else
		return (1);
}

int	ft_change_quote_state(char c, int quote_state)
{
	if (c == '\'' && quote_state == 0)
		quote_state = 1;
	else if (c == '\'' && quote_state == 1)
		quote_state = 0;
	else if (c == '\"' && quote_state == 0)
		quote_state = 2;
	else if (c == '\"' && quote_state == 2)
		quote_state = 0;
	return (quote_state);
}

// Fonction qui remplie avec des nouveaux élements la liste chaînée.
int	ft_lst_fill(int size, int start, char *input, t_minishell *mini)
{
	char			*str;
	t_token_list	*new_element;

	str = malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (0);
	ft_strcpy_parse(input, str, size, start);
	new_element = ft_new_element(str);
	if (new_element == NULL)
		return (0);
	if (mini->token == NULL)
	{
		mini->token = new_element;
		mini->token->next = new_element;
		mini->token->prev = new_element;
	}
	else
	{
		mini->token->prev->next = new_element;
		new_element->prev = mini->token->prev;
		new_element->next = mini->token;
		mini->token->prev = new_element;
	}
	return (1);
}

// Fonction qui initialise un nouvel élement
static t_token_list	*ft_new_element(char *str)
{
	t_token_list	*new_element;

	new_element = malloc(sizeof(t_token_list));
	if (!new_element)
		return (NULL);
	new_element->str = str;
	new_element->token_value = -1;
	new_element->next = new_element;
	new_element->prev = new_element;
	return (new_element);
}
