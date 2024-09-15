/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:52:59 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 15:07:34 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_strncmp("Bonjour","Bonjour!!!",9));
	return (0);
}*/
