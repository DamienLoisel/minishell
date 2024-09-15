/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:46:24 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/06 00:24:05 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_echo_suite(t_token_list *node, int flag_s, int i, t_minishell *mini)
{
	int	index;

	index = 0;
	if (node->str[i] == '$' && (ft_isalnum(node->str[i + 1]) || \
	node->str[i + 1] == '_' || node->str[i + 1] == '?') && !flag_s)
	{
		if (node->str[i + 1] == '?')
			return (printf("%d", mini->exit_status), 2);
		i++;
		index++;
		while (node->str[i] == '_' || ft_isalnum(node->str[i]))
		{
			index++;
			i++;
		}
	}
	return (index);
}

int	handle_echo(t_minishell *mini, int flag_d, int flag_s, t_token_list *node)
{
	int	i;

	i = 0;
	while (node->str[i] != '\0')
	{
		if (node->str[i] == '\"' && flag_s == 0)
		{
			flag_d = !flag_d;
			i++;
			continue ;
		}
		if (node->str[i] == '\'' && flag_d == 0)
		{
			flag_s = !flag_s;
			i++;
			continue ;
		}
		i += handle_echo_suite(node, flag_s, i, mini);
		if (node->str[i] != '\0')
			printf("%c", node->str[i]);
		else
			break ;
		i++;
	}
	return (0);
}

char	*ft_echo_suite(t_token_list *node, t_minishell *mini)
{
	char	*str;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	if (handle_echo(mini, 0, 0, node) == 1)
	{
		str[0] = '\0';
		printf("%s", str);
	}
	return (str);
}

/* Cette fonction ft_echo reproduit la commande du même nom de bash.
Cette fonction gère la version simple d'echo ainsi que le -n.*/

int	ft_echo(t_token_list *list, t_minishell *mini)
{
	t_token_list	*node;
	t_token_list	*start;
	char			*str;

	start = list;
	if (start == list->next || list->next->token_value < 6)
		return (printf("%c\n", '\0'), 1);
	if (ft_strncmp(list->next->str, "-n\0", 3) == 0)
		node = list->next->next;
	else
		node = list->next;
	while (1)
	{
		str = ft_echo_suite(node, mini);
		if (str == NULL)
			return (1);
		free(str);
		if (start == node->next || (node->next->token_value < 6))
			break ;
		printf(" ");
		node = node->next;
	}
	if (ft_strncmp(start->next->str, "-n\0", 3) != 0)
		printf("\n");
	return (0);
}
