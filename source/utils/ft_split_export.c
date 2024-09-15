/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:09:54 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/06 12:20:11 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words_export(char const *s, char c)
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

char	**magic_export(char *str, char c, char **new_str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	start = i;
	while (str[i])
		i++;
	new_str[0] = malloc(sizeof(char) * (start + 1));
	if (!new_str[0])
		return (NULL);
	new_str[1] = malloc(sizeof(char) * (i - start + 1));
	if (!new_str[1])
		return (NULL);
	ft_strcpy_parse(str, new_str[0], start, 0);
	ft_strcpy_parse(str, new_str[1], (i - start), start);
	return (new_str);
}

char	**ft_split_export(char *s, char c)
{
	char	**new_str;
	int		nb_words;

	nb_words = count_words_export(s, c);
	new_str = malloc(sizeof(char *) * (nb_words + 1));
	if (new_str == NULL)
		return (NULL);
	new_str = magic_export(s, c, new_str);
	if (new_str == NULL)
	{
		free(new_str);
		return (NULL);
	}
	new_str[nb_words] = 0;
	return (new_str);
}
