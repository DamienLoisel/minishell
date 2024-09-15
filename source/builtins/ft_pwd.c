/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:42:36 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/05 21:30:48 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Cette fonction ft_pwd reproduit la commande bash pwd.
Cette commande affiche le chemin absolu du répertoire de travail
où l'on se trouve. */

int	ft_pwd(void)
{
	char	wd[4096];

	if ((getcwd(wd, sizeof(wd)) != NULL))
	{
		printf("%s\n", getcwd(wd, sizeof(wd)));
		return (0);
	}
	else
		return (1);
}
