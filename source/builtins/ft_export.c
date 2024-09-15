/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:54:47 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/07 18:33:29 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Cette fonction gère le cas où export est appelé seul, dans ce cas
il faut afficher chaque chaîne de env dans l'ordre alphabétique et
précédé de "declare -x "*/

char	**export_alone(char **env)
{
	char	**new_env;
	int		i;

	new_env = ft_env_cpy(env);
	if (new_env == NULL)
		return (NULL);
	ft_sort_env(new_env);
	i = 0;
	while (new_env[i])
	{
		if (ft_strchr(new_env[i], '=') != NULL)
			ft_print_export_alone(new_env[i]);
		else
		{
			printf("declare -x ");
			printf("%s\n", new_env[i]);
		}
		i++;
	}
	return (ft_free_split(new_env), NULL);
}

/* Cette fonction trie new_env dans l'ordre
alphabétique grâce à un bubble_sort */

void	ft_sort_env(char **new_env)
{
	int		i;
	int		j;
	int		size;
	char	*temp;

	i = -1;
	size = 0;
	while (new_env[size])
		size++;
	size--;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (ft_strcmp(new_env[j], new_env[j + 1]) > 0)
			{
				temp = new_env[j];
				new_env[j] = new_env[j + 1];
				new_env[j + 1] = temp;
			}
		}
	}
}

int	ft_setenv(char **value, t_minishell *mini)
{
	int		i;
	char	*new_value;

	i = 0;
	while (mini->env_cpy[i] != NULL)
	{
		if (ft_strncmp(mini->env_cpy[i], value[0], ft_strlen(value[0])) == 0)
		{
			new_value = ft_strjoin(value[0], value[1]);
			free(mini->env_cpy[i]);
			mini->env_cpy[i] = new_value;
			return (0);
		}
		i++;
	}
	new_value = ft_strjoin(value[0], value[1]);
	mini->env_cpy = ft_realloc(mini->env_cpy, sizeof(char *) \
	* (i + 1), sizeof(char *) * (i + 2));
	mini->env_cpy[i] = new_value;
	mini->env_cpy[i + 1] = NULL;
	return (0);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*temp;
	size_t	copy_size;

	temp = malloc(new_size);
	if (!temp)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(temp, ptr, copy_size);
		free(ptr);
	}
	return (temp);
}

int	ft_export(t_minishell *mini, t_token_list *list, char *input, char **value)
{
	t_stuff	stuff;

	stuff.start = list;
	if (stuff.start == list->next || list->next->token_value < 6)
		return (export_alone(mini->env_cpy), 0);
	while (1)
	{
		input = list->next->str;
		if (ft_verif_input_export(input) == 1)
			ft_setenv_alone(input, mini);
		else
		{
			value = ft_split_export(input, '=');
			if (value == NULL)
				return (1);
			value[0] = ft_handle_export(value[0], 0, 0, 0);
			value[1] = ft_handle_export(value[1], 0, 0, 0);
			ft_setenv(value, mini);
			ft_free_split(value);
		}
		list = list->next;
		if (stuff.start == list->next)
			break ;
	}
	return (0);
}
