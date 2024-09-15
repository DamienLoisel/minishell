/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:56:56 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 14:48:38 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
/*#include <stdio.h>*/

char	*ft_intmin(void)
{
	char	*int_min;
	char	*tab;
	int		i;

	i = 0;
	int_min = "-2147483648";
	tab = malloc(sizeof(char) * 12);
	if (tab == NULL)
		return (NULL);
	while (int_min[i] != '\0')
	{
		tab[i] = int_min[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

int	nb_char(int nb)
{
	int	i;

	i = 0;
	if (nb < 1)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*remplir_tab(char *tab, int len, int len1, int n)
{
	while (len - len1 > 0)
	{
		tab[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	int		len;
	int		len1;
	int		flag;
	char	*tab;

	if (n == -2147483648)
		return (ft_intmin());
	flag = 0;
	len1 = 0;
	if (n < 0)
	{
		len1 = 1;
		flag = 1;
		n = -n;
	}
	len = nb_char(n) + len1;
	tab = malloc(sizeof(char) * len + 1);
	if (tab == NULL)
		return (NULL);
	tab[len] = '\0';
	tab = remplir_tab(tab, len, len1, n);
	if (flag == 1)
		tab[0] = '-';
	return (tab);
}

/*int    main(void)
  {
  printf("%s\n", ft_itoa(-0));
  printf("%s\n", ft_itoa(6815610));
  printf("%s\n", ft_itoa(-698516650));
  return (0);
  }*/
