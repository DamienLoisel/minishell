/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:40:48 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 13:02:49 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parse(char *input, t_minishell *mini)
{
	if (!ft_lst_init(input, mini, 0, 0))
		return (0);
	if (!ft_env_parse(mini))
		return (0);
	if (!ft_token_init(mini))
		return (0);
	if (!ft_token_parse(mini))
		return (0);
	if (!ft_replace_exit_status(mini) || !ft_awk(mini))
		return (0);
	return (1);
}
