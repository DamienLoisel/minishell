/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:53:39 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 15:13:46 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

/*size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_size;

	i = 0;
	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	dest_size = ft_strlen(dst);
	if (dest_size >= size)
	{
		return (ft_strlen((char *)src) + size);
	}
	while (i < (size - dest_size - 1) && src[i] != '\0')
	{
		dst[i + dest_size] = src[i];
		i++;
	}
	dst[i + dest_size] = '\0';
	return (dest_size + ft_strlen((char *)src));
}
