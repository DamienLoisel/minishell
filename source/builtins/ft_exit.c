/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:24:58 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 09:30:32 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_token_list *token, t_minishell *mini)
{
	if (token->next->token_value != ARG)
		exit(mini->exit_status);
	else
		exit(ft_atoi(token->next->str));
}
