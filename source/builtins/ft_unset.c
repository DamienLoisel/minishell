/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:07:38 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/05 22:15:04 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Cette fonction déplace en bas de env la
variable entrée en argument de unset et la remplace par NULL. */

void	change_env(t_minishell *mini, int i)
{
	char	*temp;

	while (mini->env_cpy[i])
	{
		temp = mini->env_cpy[i];
		if (mini->env_cpy[i + 1] == NULL)
			break ;
		mini->env_cpy[i] = mini->env_cpy[i + 1];
		mini->env_cpy[i + 1] = temp;
		i++;
	}
	free(mini->env_cpy[i]);
	mini->env_cpy[i] = NULL;
}

/* Cette fonction reproduit la commande bash du même nom.
L'objectif est suprimer la variable input.*/

int	ft_unset(t_minishell *mini, char *input)
{
	int				i;
	t_token_list	*start;
	t_token_list	*list;

	list = mini->token;
	start = list;
	if (start == list->next)
		return (0);
	while (1)
	{
		input = list->next->str;
		i = -1;
		while (mini->env_cpy[++i])
		{
			if (ft_strncmp(input, mini->env_cpy[i], ft_strlen(input)) == 0)
			{
				change_env(mini, i);
				break ;
			}
		}
		list = list->next;
		if (start == list->next)
			break ;
	}
	return (0);
}
