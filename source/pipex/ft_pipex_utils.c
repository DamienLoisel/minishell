/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:41:22 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/06 11:53:17 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_pipex(t_minishell *mini, t_cmd *start)
{
	int	i;

	while (1)
	{
		i = 1;
		while (start->cmd_param[i])
		{
			start->cmd_param[i] = ft_handle_pipex(start->cmd_param[i], 0, 0, 0);
			i++;
		}
		start = start->next;
		if (start == mini->cmd)
			break ;
	}
	return (1);
}

char	*ft_handle_pipex(char *value, int flag_double_quote, \
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
	return (new_value);
}

void	ft_free_pipex(t_minishell *mini, t_cmd *start)
{
	int	i;

	while (1)
	{
		i = 1;
		while (start->cmd_param[i])
		{
			free(start->cmd_param[i]);
			i++;
		}
		start = start->next;
		if (start == mini->cmd)
			break ;
	}
}

int	is_builtins(t_minishell *mini, t_token_list *token, char **cmd)
{
	if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		return (ft_cd(mini));
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		return (ft_env(mini->env_cpy));
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (ft_unset(mini, NULL));
	else if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		return (ft_echo(token, mini));
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		return (ft_export(mini, mini->token, NULL, NULL));
	else if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		return (ft_exit(token, mini), 0);
	return (42);
}

int	exec_builtins(t_minishell *mini, char **cmd)
{
	int				count;
	t_token_list	*start;
	t_cmd			*start_cmd;

	count = 0;
	start = mini->token;
	start_cmd = mini->cmd;
	while (start_cmd->skip_cmd)
	{
		count++;
		start_cmd = start_cmd->next;
	}
	while (count > 0)
	{
		if (start->token_value == CMD)
			count--;
		start = start->next;
	}
	mini->exit_status = is_builtins(mini, start, cmd);
	if (mini->exit_status == 42)
		return (0);
	return (1);
}
