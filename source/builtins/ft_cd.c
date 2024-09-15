/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:44:34 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 18:13:28 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Dans le cas où le chemin entré n'existe pas cette fonction est appelé
et imprime un message d'erreur. */

static void	ft_error(void)
{
	printf("No such file or directory\n");
}

/* Cette fonction ft_cd reproduit la commande bash 'cd'.
Cette commande permet de se déplacer dans le terminal en entrant des chemins
absolus ou relatifs. */

int	ft_cd(t_minishell *mini)
{
	char	*str;
	char	*user;

	str = mini->token->next->str;
	if (str == mini->token->str)
	{
		user = ft_getenv("HOME", mini);
		if (user == NULL)
			return (printf("cd: HOME not set\n"), 1);
		chdir(user);
		free(user);
		return (0);
	}
	if (chdir(str) != 0)
		return (ft_error(), 0);
	return (0);
}
