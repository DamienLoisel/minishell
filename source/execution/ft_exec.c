/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:20:08 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 00:35:10 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_launch(t_minishell *mini)
{
	if (ft_parse_pipex(mini, mini->token))
	{
		mini->exit_status = ft_pipex(mini);
		return (1);
	}
	mini->exit_status = ft_which_builtin(mini);
	if (mini->exit_status != 42)
		return (1);
	mini->exit_status = ft_which_command(mini);
	return (1);
}
