/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:58:14 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 09:29:32 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_which_builtin(t_minishell *mini)
{
	if (mini->token == NULL || mini->token->str == NULL)
		return (1);
	else if (ft_strncmp(mini->token->str, "pwd\0", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(mini->token->str, "cd\0", 3) == 0)
		return (ft_cd(mini));
	else if (ft_strncmp(mini->token->str, "env\0", 4) == 0)
		return (ft_env(mini->env_cpy));
	else if (ft_strncmp(mini->token->str, "unset\0", 6) == 0)
		return (ft_unset(mini, NULL));
	else if (ft_strncmp(mini->token->str, "echo\0", 5) == 0)
		return (ft_echo(mini->token, mini));
	else if (ft_strncmp(mini->token->str, "export\0", 7) == 0)
		return (ft_export(mini, mini->token, NULL, NULL));
	if (ft_strncmp(mini->token->str, "exit\0", 5) == 0)
		return (ft_exit(mini->token, mini), 0);
	return (42);
}
