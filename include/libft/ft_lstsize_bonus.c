/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:54:38 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 18:12:07 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		taille;
	t_list	*current;

	current = lst;
	taille = 0;
	while (current != NULL)
	{
		taille++;
		current = current->next;
	}
	return (taille);
}
