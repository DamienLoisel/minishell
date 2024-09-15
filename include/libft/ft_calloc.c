/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:33:38 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/20 13:49:53 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	taille;
	void	*s;

	if (size == 0 || nmemb == 0)
	{
		s = malloc(0);
		return (s);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	taille = nmemb * size;
	s = malloc(taille);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, taille);
	return (s);
}
