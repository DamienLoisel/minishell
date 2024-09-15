/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:36:45 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 16:02:11 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*last_occ;

	i = 0;
	last_occ = NULL;
	if (c == 0)
		return ((char *)s + ft_strlen((char *)s));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			last_occ = &s[i];
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + ft_strlen((char *)s));
	return ((char *)last_occ);
}
