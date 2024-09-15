/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:41:54 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/05 21:39:55 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_token_init(t_minishell *mini)
{
	t_token_list	*start;

	if (mini == NULL || mini->token == NULL)
		return (0);
	start = mini->token;
	while (1)
	{
		mini->token->token_value = ft_which_token(mini->token, mini->env_cpy);
		mini->token = mini->token->next;
		if (start == mini->token)
			break ;
	}
	return (1);
}

int	ft_which_token(t_token_list *token, char **env)
{
	if (ft_is_command(token, env))
		return (CMD);
	else if ((ft_strncmp(token->str, "<\0", 2) == 0))
		return (INPUT);
	else if ((ft_strncmp(token->str, "<<\0", 3) == 0))
		return (HEREDOC);
	else if ((ft_strncmp(token->str, ">\0", 2) == 0))
		return (TRUNC);
	else if ((ft_strncmp(token->str, ">>\0", 3) == 0))
		return (APPEND);
	else if ((ft_strncmp(token->str, "|\0", 2) == 0))
		return (PIPE);
	else
		return (ARG);
}

int	ft_is_command(t_token_list *token, char **env)
{
	char	*path;

	if (ft_strncmp(token->str, "pwd\0", 4) == 0)
		return (1);
	else if (ft_strncmp(token->str, "cd\0", 3) == 0)
		return (1);
	else if (ft_strncmp(token->str, "env\0", 4) == 0)
		return (1);
	else if (ft_strncmp(token->str, "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(token->str, "export\0", 7) == 0)
		return (1);
	else if (ft_strncmp(token->str, "exit\0", 5) == 0)
		return (1);
	path = findpath(token->str, env, -1);
	if (path == NULL)
		return (0);
	return (free(path), 1);
}

//J'effectue une copie de la chaîne a partir de start dans une nouvelle chaîne.
char	*ft_strcpy_parse(char *src, char *dest, int size, int j)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_count_words(char const *s, char c)
{
	int	nb;
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		if (flag == 1 && s[i] == c)
			flag = 0;
		if (flag == 0 && s[i] != c)
		{
			flag = 1;
			nb++;
		}
		i++;
	}
	return (nb);
}
