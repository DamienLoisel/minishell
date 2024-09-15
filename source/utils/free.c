/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:11:01 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/04 12:16:15 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_lst(t_minishell *mini)
{
	t_token_list	*current;
	t_token_list	*next;

	if (mini == NULL || mini->token == NULL)
		return ;
	current = mini->token;
	while (1)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
		if (current == mini->token)
			break ;
	}
	mini->token = NULL;
}

void	ft_free_lst_pipex(t_minishell *mini)
{
	t_cmd	*current;
	t_cmd	*next;

	if (mini == NULL || mini->cmd == NULL)
		return ;
	current = mini->cmd;
	while (1)
	{
		next = current->next;
		if (current->cmd_param)
			free(current->cmd_param);
		free(current);
		current = next;
		if (current == mini->cmd)
			break ;
	}
	mini->cmd = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split || !split[i])
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
