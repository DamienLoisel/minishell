/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:57:09 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 12:02:35 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	g_pid;

char	**ft_env_cpy(char **env)
{
	char	**new_env;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			return (free(new_env), NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	main(int ac, char **av, char **env)
{
	t_minishell			mini;
	char				*input;

	(void)av;
	(void)ac;
	mini.token = NULL;
	mini.cmd = NULL;
	mini.exit_status = 0;
	mini.env_cpy = ft_env_cpy(env);
	ft_signals();
	while (1)
	{
		input = readline(YELLOW"minishell : "RESET);
		if (!input)
			return (ft_free_split(mini.env_cpy), printf("exit\n"), 0);
		add_history(input);
		if (ft_parse(input, &mini))
			ft_launch(&mini);
		free(input);
		ft_free_lst(&mini);
		ft_free_lst_pipex(&mini);
		g_pid = 0;
	}
	return (ft_free_split(mini.env_cpy), 0);
}
