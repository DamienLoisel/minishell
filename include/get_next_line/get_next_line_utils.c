/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:10:32 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/05 13:41:13 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p++ = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strjoin2(const char *s1, const char *s2)
{
	char	*result;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen2(s1) + ft_strlen2(s2) + 1);
	if (!result)
		return (NULL);
	tmp = result;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (result);
}

//char	*ft_strchr(const char *s, int c)
//{
//	int	i;
//
//	i = 0;
//	if (c == 0)
//		return ((char *)s + ft_strlen2((char *)s));
//	while (s[i] != '\0')
//	{
//		if (s[i] == (char)c)
//			return ((char *)&s[i]);
//		i++;
//	}
//	if (s[i] == (char)c)
//		return ((char *)s + ft_strlen2((char *)s));
//	return (NULL);
//}
