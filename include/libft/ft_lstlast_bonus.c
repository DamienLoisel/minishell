/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:59:54 by dloisel           #+#    #+#             */
/*   Updated: 2024/05/21 18:12:29 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_element;

	if (!lst)
		return (NULL);
	last_element = lst;
	while (last_element->next)
		last_element = last_element->next;
	return (last_element);
}
