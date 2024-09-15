/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:35:22 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/07 16:42:36 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_awk(char *str, int i, int j)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * ft_strlen(str) - 1);
	if (!new_str)
		return (NULL);
	while (str[i + 1] != '\0')
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}

int	ft_awk(t_minishell *mini)
{
	t_token_list	*start;

	start = mini->token;
	while (1)
	{
		if (start->token_value == CMD && !ft_strcmp("awk", start->str) && \
		start->next->token_value == ARG)
		{
			start->next->str = handle_awk(start->next->str, 1, 0);
			if (!start->next->str)
				return (0);
		}
		start = start->next;
		if (start == mini->token)
			break ;
	}
	return (1);
}
