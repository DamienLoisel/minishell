/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:32:38 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 00:39:51 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_len(t_token_list *token, t_token_list *start)
{
	int	len;

	len = 0;
	while (token->token_value > 5)
	{
		token = token->next;
		len++;
		if (token == start)
			break ;
	}
	return (len);
}

static t_cmd	*ft_new_element(t_token_list *token, t_token_list *temp, \
t_token_list *start, int i)
{
	t_cmd	*new_element;

	new_element = malloc(sizeof(t_cmd));
	if (!new_element)
		return (NULL);
	new_element->infile = -1;
	new_element->outfile = -1;
	new_element->next = new_element;
	new_element->prev = new_element;
	new_element->skip_cmd = 0;
	new_element->cmd_param = malloc(sizeof(char *) * \
	(ft_len(token, start) + 1));
	if (!new_element->cmd_param)
		return (free(new_element), NULL);
	while (1)
	{
		new_element->cmd_param[i] = temp->str;
		i++;
		temp = temp->next;
		if (temp->token_value < 6 || temp == start)
			break ;
	}
	new_element->cmd_param[i] = NULL;
	return (new_element);
}

int	ft_lst_init_cmd(t_minishell *mini, int count, t_token_list *start, int i)
{
	t_cmd	*new_element;

	while (++i < count)
	{
		while (start->token_value != CMD)
			start = start->next;
		new_element = ft_new_element(start, start, mini->token, 0);
		if (new_element == NULL)
			return (0);
		if (mini->cmd == NULL)
		{
			mini->cmd = new_element;
			mini->cmd->next = new_element;
			mini->cmd->prev = new_element;
		}
		else
		{
			mini->cmd->prev->next = new_element;
			new_element->prev = mini->cmd->prev;
			new_element->next = mini->cmd;
			mini->cmd->prev = new_element;
		}
		start = start->next;
	}
	return (1);
}

int	ft_parse_pipex(t_minishell *mini, t_token_list *start)
{
	int	count_cmd;
	int	count_pipex;

	count_cmd = 0;
	count_pipex = 0;
	while (1)
	{
		if (start->token_value == CMD)
			count_cmd++;
		if (start->token_value >= 1 && start->token_value <= 5)
			count_pipex++;
		start = start->next;
		if (start == mini->token)
			break ;
	}
	if (count_cmd >= 1 && count_pipex >= 1)
	{
		ft_lst_init_cmd(mini, count_cmd, mini->token, -1);
		return (1);
	}
	return (0);
}
