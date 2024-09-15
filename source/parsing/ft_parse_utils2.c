/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:27:45 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 00:12:04 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env_parse(t_minishell *mini)
{
	t_token_list	*start;
	char			*new_str;
	int				loop_nbr;

	if (mini == NULL || mini->token == NULL)
		return (0);
	start = mini->token;
	while (1)
	{
		loop_nbr = ft_count_words(mini->token->str, ' ');
		while (loop_nbr > 0)
		{
			new_str = ft_search_and_replace(mini);
			if (new_str != mini->token->str)
			{
				free(mini->token->str);
				mini->token->str = new_str;
			}
			loop_nbr--;
		}
		mini->token = mini->token->next;
		if (mini->token == start)
			break ;
	}
	return (1);
}

char	*ft_search_and_replace(t_minishell *mini)
{
	char	*var_name;
	int		i;
	int		start;
	char	*var_content;

	i = 0;
	var_content = NULL;
	while (mini->token->str[i] != '\0' && \
	mini->token->str[i] != '$')
		i++;
	if (mini->token->str[i] == '\0')
		return (mini->token->str);
	start = i + 1;
	i++;
	while (mini->token->str[i] != '\0' && \
	(ft_isalnum(mini->token->str[i]) || mini->token->str[i] == '_'))
		i++;
	var_name = malloc(sizeof(char) * (i - start + 1));
	if (var_name == NULL)
		return (NULL);
	var_name = ft_strcpy_parse(mini->token->str, var_name, (i - start), start);
	var_content = ft_getenv(var_name, mini);
	if (var_content != NULL)
		return (free(var_content), ft_replace_str(mini, var_name, start, i));
	return (free(var_name), mini->token->str);
}

char	*ft_replace_str(t_minishell *mini, char *var_name, int start, int end)
{
	char	*new_str;
	char	*var_content;
	int		i;
	int		j;

	var_content = ft_getenv(var_name, mini);
	if (ft_is_in_single_quote(mini->token->str, start, end - 1, 0))
		return (free(var_content), free(var_name), mini->token->str);
	new_str = malloc(sizeof(char) * (ft_strlen(mini->token->str) - \
	(end - start) + (ft_strlen(var_content) + 1)));
	if (new_str == NULL)
		return (free(var_content), NULL);
	i = -1;
	while (++i < start - 1)
		new_str[i] = mini->token->str[i];
	j = 0;
	while (var_content[j] != '\0')
		new_str[i++] = var_content[j++];
	while (mini->token->str[end] != '\0')
		new_str[i++] = mini->token->str[end++];
	new_str[i] = '\0';
	return (free(var_content), free(var_name), new_str);
}

int	ft_is_in_single_quote(char *str, int start, int end, int in_double_quote)
{
	int	i;
	int	quote_count_single;

	i = -1;
	quote_count_single = 0;
	while (++i < start)
	{
		if (str[i] == '"')
			in_double_quote = !in_double_quote;
		if (str[i] == '\'' && !in_double_quote)
			quote_count_single++;
	}
	if (quote_count_single % 2 == 0)
		return (0);
	quote_count_single = 0;
	while (++end < ft_strlen(str))
	{
		if (str[end] == '"')
			in_double_quote = !in_double_quote;
		if (str[end] == '\'' && !in_double_quote)
			quote_count_single++;
	}
	if (quote_count_single % 2 == 0)
		return (0);
	return (1);
}

char	*ft_getenv(char *var_name, t_minishell *mini)
{
	char	*var_content;
	int		i;
	int		start;
	int		var_name_len;

	i = 0;
	var_name_len = ft_strlen(var_name);
	while (mini->env_cpy[i])
	{
		if (ft_strncmp(var_name, mini->env_cpy[i], var_name_len) == 0 \
		&& mini->env_cpy[i][var_name_len] == '=')
		{
			start = var_name_len + 1;
			var_content = malloc(sizeof(char) \
			* (ft_strlen(mini->env_cpy[i]) - start + 1));
			if (!var_content)
				return (NULL);
			ft_strcpy_parse(mini->env_cpy[i], var_content, \
			ft_strlen(mini->env_cpy[i]) - start, start);
			return (var_content);
		}
		i++;
	}
	return (NULL);
}
