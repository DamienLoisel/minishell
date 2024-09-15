/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:11:33 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 16:10:01 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_vide(void)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * 1);
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*new_str;

	i = 0;
	if (*s == '\0')
		return (ft_vide());
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		new_str = malloc(sizeof(char) * 1);
		if (new_str == NULL)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (len > (s_len - start))
		len = s_len - start;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	while ((i < len) && s[start])
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}

/*#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_substr("tripouille", 1,1));
	return (0);
}*/
