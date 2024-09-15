/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:45:33 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/20 17:30:28 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_bordel(const char *s1)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (new_str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	ft_get_start(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	ft_get_end(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0)
	{
		if (ft_strchr(set, s1[i - 1]) == 0)
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{	
	char	*new_str;
	int		debut;
	int		fin;
	int		i;

	i = 0;
	debut = ft_get_start(s1, set);
	fin = ft_get_end(s1, set);
	if (debut >= fin || *s1 == '\0')
	{
		new_str = malloc(sizeof(char) * 1);
		if (new_str == NULL)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (*set == '\0')
		return (ft_bordel(s1));
	new_str = malloc(sizeof(char) * (fin - debut + 1));
	if (new_str == NULL)
		return (NULL);
	while (debut < fin)
		new_str[i++] = s1[debut++];
	new_str[i] = '\0';
	return (new_str);
}

/*int	main(void)
{
	printf("%s\n", ft_strtrim("   xtripouille","x "));
	return (0);
}*/
