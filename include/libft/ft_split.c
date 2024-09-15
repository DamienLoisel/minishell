/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:17:08 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/05 21:57:43 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free(char **tab, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	count_words(char const *s, char c)
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

char	*ft_strcpy(char *src, char *dest, int size, int j)
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

char	**magic(const char *s, char c, int nb_words, char **new_str)
{
	int	i;
	int	j;
	int	k;
	int	nb_boucle;

	i = 0;
	k = 0;
	nb_boucle = 0;
	while (nb_boucle++ < nb_words)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		new_str[k] = malloc(sizeof(char) * (i - j + 1));
		if (new_str[k] == NULL)
		{
			ft_free(new_str, k);
			return (NULL);
		}
		ft_strcpy((char *)s, new_str[k], (i - j), j);
		k++;
	}
	return (new_str);
}

char	**ft_split(char const *s, char c)
{
	char	**new_str;
	int		nb_words;

	nb_words = count_words(s, c);
	new_str = malloc(sizeof(char *) * (nb_words + 1));
	if (new_str == NULL)
		return (NULL);
	new_str = magic(s, c, nb_words, new_str);
	if (new_str == NULL)
	{
		free(new_str);
		return (NULL);
	}
	new_str[nb_words] = 0;
	return (new_str);
}
