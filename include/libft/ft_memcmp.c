/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:47:44 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/20 11:11:43 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>*/

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p_s1;
	const unsigned char	*p_s2;

	p_s1 = s1;
	p_s2 = s2;
	i = 0;
	while (i < n)
	{
		if (p_s1[i] != p_s2[i])
			return (p_s1[i] - p_s2[i]);
		i++;
	}
	return (0);
}

/*int main() {

    int array1 [] = { 54, 85, 20, 63, 21 };
    int array2 [] = { 54, 85, 19, 63, 21 };
    size_t size = sizeof( int ) * 5;

    assert( memcmp( array1, array2, size) == ft_memcmp( array1, array2, size) );
    assert( memcmp( array1, array1, size) == ft_memcmp( array1, array1, size) );
    assert( memcmp( array2, array1, size) == ft_memcmp( array2, array1, size) );

    printf( "Test is ok\n" );

    return 0;
}*/
