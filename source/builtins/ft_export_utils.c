/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:30:12 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/09 12:10:18 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_copy_export(char *value, int flag_double_quote, \
int flag_single_quote, char *new_value)
{
	t_stuff	stuff;

	stuff.i = 0;
	stuff.j = 0;
	while (stuff.i < ft_strlen(value))
	{
		if (value[stuff.i] == '\'' && flag_double_quote == 0)
		{
			flag_single_quote = !flag_single_quote;
			stuff.i++;
			continue ;
		}
		if (value[stuff.i] == '\"' && flag_single_quote == 0)
		{
			flag_double_quote = !flag_double_quote;
			stuff.i++;
			continue ;
		}
		if (value[stuff.i] == '\0')
			break ;
		new_value[stuff.j++] = value[stuff.i++];
	}
	new_value[stuff.j] = '\0';
	return (new_value);
}

char	*ft_handle_export(char *value, int flag_double_quote, \
int flag_single_quote, int i)
{
	char	*new_value;
	int		count;

	count = 0;
	while (value[i])
	{
		if (value[i] == '\'' && flag_double_quote == 0)
		{
			flag_single_quote = !flag_single_quote;
			count++;
		}
		if (value[i] == '\"' && flag_single_quote == 0)
		{
			flag_double_quote = !flag_double_quote;
			count++;
		}
		i++;
	}
	new_value = malloc(sizeof(char) * (ft_strlen(value) - count + 1));
	if (!new_value)
		return (NULL);
	new_value = ft_copy_export(value, 0, 0, new_value);
	return (free(value), new_value);
}

int	ft_verif_input_export(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '=' && input[i + 1] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_setenv_alone(char *value, t_minishell *mini)
{
	int		i;
	char	*new_value;
	char	*new_input;

	i = 0;
	new_input = ft_strdup(value);
	new_input = ft_handle_export(new_input, 0, 0, 0);
	while (mini->env_cpy[i] != NULL)
	{
		if (!ft_strncmp(mini->env_cpy[i], new_input, ft_strlen(new_input)))
			return (free(new_input), 0);
		i++;
	}
	new_value = malloc(sizeof(char) * (ft_strlen(new_input) + 1));
	if (!new_value)
		return (1);
	ft_strlcpy(new_value, new_input, ft_strlen(new_input) + 1);
	mini->env_cpy = ft_realloc(mini->env_cpy, sizeof(char *) * (i + 1), \
	sizeof(char *) * (i + 2));
	mini->env_cpy[i] = new_value;
	mini->env_cpy[i + 1] = NULL;
	free(new_input);
	return (0);
}
