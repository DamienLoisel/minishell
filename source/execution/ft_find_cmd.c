/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:15:01 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 09:16:33 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Fonction qui récupére et return la taille de la liste chaînée
static int	ft_lst_len(t_token_list *token)
{
	int				i;
	t_token_list	*temp;

	i = 0;
	temp = token;
	while (1)
	{
		i++;
		temp = temp->next;
		if (temp == token)
			break ;
	}
	return (i);
}

char	*get_path(char *name, char **env)
{
	int		i;
	char	*to_compare;

	i = -1;
	while (env[++i])
	{
		to_compare = ft_substr(env[i], 0, ft_strlen(name));
		if (to_compare == NULL)
			return (NULL);
		if (ft_strncmp(to_compare, name, ft_strlen(to_compare)) == 0 \
		&& env[i][ft_strlen(name)] == '=')
		{
			free(to_compare);
			return (env[i]);
		}
		free(to_compare);
	}
	return (NULL);
}

char	*findpath(char *tofind, char **env, int i)
{
	char	**mypaths;
	char	*new_str;
	char	*temp_str;
	char	*path_var;

	if (tofind)
		if (tofind[0] == '/')
			return (ft_strdup(tofind));
	path_var = get_path("PATH", env);
	if (!path_var || tofind[0] == '\0')
		return (NULL);
	mypaths = ft_split(path_var + 5, ':');
	if (!mypaths)
		return (free(path_var), NULL);
	while (mypaths[++i])
	{
		temp_str = ft_strjoin(mypaths[i], "/");
		new_str = ft_strjoin(temp_str, tofind);
		free(temp_str);
		if (access(new_str, F_OK) == 0)
			return (ft_free_split(mypaths), new_str);
		free(new_str);
	}
	return (ft_free_split(mypaths), NULL);
}

int	ft_which_command(t_minishell *mini)
{
	char			*path;
	char			**argv;
	t_token_list	*start;
	int				i;

	if (mini->token == NULL || mini->token->str == NULL)
		return (0);
	i = 0;
	path = findpath(mini->token->str, mini->env_cpy, -1);
	if (path == NULL)
		return (printf("%s: command not found\n", mini->token->str), 0);
	start = mini->token;
	argv = malloc(sizeof(char *) * (ft_lst_len(mini->token) + 1));
	while (1)
	{
		argv[i] = ft_strdup(mini->token->str);
		i++;
		mini->token = mini->token->next;
		if (start == mini->token)
			break ;
	}
	argv[i] = NULL;
	return (ft_command_exec(path, argv, mini, NULL));
}

int	ft_command_exec(char *p, char **a, t_minishell *mini, char *temp)
{
	temp = ft_check_cat2(a, mini);
	g_pid = fork();
	if (g_pid < 0)
		return (ft_free_split(a), free(p), printf("fork failed\n"), 0);
	else if (g_pid == 0)
	{
		if (!ft_strcmp("cat\0", a[0]) && temp == NULL)
		{
			free(a[1]);
			a[1] = NULL;
		}
		if (execve(p, a, mini->env_cpy) == -1)
			return (printf("execve failed\n"), \
			ft_free_split(a), free(p), exit(EXIT_SUCCESS), 0);
	}
	else
	{
		waitpid(g_pid, &mini->exit_status, 0);
		if (WIFEXITED(mini->exit_status))
			return (free(p), ft_free_split(a), WEXITSTATUS(mini->exit_status));
	}
	if (temp && temp != a[1])
		free(temp);
	return (free(p), ft_free_split(a), -1);
}
