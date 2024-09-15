/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:00:38 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 12:14:08 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_token_parse(t_minishell *mini)
{
	t_token_list	*start;

	start = mini->token;
	if ((start->prev->token_value >= 1 && start->prev->token_value <= 3) \
	|| start->prev->token_value == 5)
		return (printf("syntax error near unexpected token '%s'\n", \
		start->prev->str), 0);
	while (1)
	{
		if ((start->token_value >= 1 && start->token_value <= 5) \
		&& (start->next->token_value >= 1 && start->next->token_value <= 5))
			return (printf("syntax error near unexpected token '%s'\n", \
			start->next->str), 0);
		start = start->next;
		if (start == mini->token)
			break ;
	}
	return (1);
}

int	ft_dollar_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*ft_replace_exit_status3(char *str, char *new_str, int len, int start)
{
	char	*temp;
	int		i;
	int		j;

	temp = malloc(sizeof(char) * (ft_strlen(str) - \
	(len - start) + ft_strlen(new_str) + 1));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < start)
	{
		temp[i] = str[i];
		i++;
	}
	j = 0;
	while (new_str[j])
		temp[i++] = new_str[j++];
	while (str[len] != '\0')
		temp[i++] = str[len++];
	temp[i] = '\0';
	return (free(new_str), temp);
}

char	*ft_replace_exit_status2(char *str, t_minishell *mini, int i)
{
	int		start;
	char	*new_str;
	char	*temp;

	while (mini->token->str[i] != '\0' && \
	mini->token->str[i] != '$')
		i++;
	if (mini->token->str[i] == '\0')
		return (mini->token->str);
	start = i;
	if (mini->token->str[i] != '\0' && mini->token->str[i + 1] == '?')
		i++;
	else
		return (mini->token->str);
	if (ft_is_in_single_quote(str, start, i, 0))
		return (str);
	new_str = ft_itoa(mini->exit_status);
	if (!new_str)
		return (NULL);
	temp = ft_replace_exit_status3(str, new_str, i + 1, start);
	return (free(str), temp);
}

int	ft_replace_exit_status(t_minishell *mini)
{
	t_token_list	*start;
	int				i;
	int				count;

	start = mini->token;
	while (1)
	{
		i = 0;
		count = ft_dollar_count(mini->token->str);
		while (i < count)
		{
			mini->token->str = ft_replace_exit_status2(mini->token->str, \
			mini, 0);
			if (mini->token->str == NULL)
				return (0);
			i++;
		}
		mini->token = mini->token->next;
		if (start == mini->token)
			break ;
	}
	return (1);
}
