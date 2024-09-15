/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:53:47 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/05 21:43:29 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_empty_or_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_export_alone(char *new_env)
{
	char	**split;

	split = ft_split(new_env, '=');
	if (!split)
		return ;
	printf("declare -x ");
	printf("%s=\"%s\"\n", split[0], split[1]);
	ft_free_split(split);
}
