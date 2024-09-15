/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:27:12 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 11:44:47 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_infile_change(t_minishell *mini)
{
	if (mini->token->token_value == INPUT && \
	mini->token->next->token_value == ARG)
		mini->cmd->infile = open(mini->token->next->str, O_RDONLY);
	else
		mini->cmd->infile = STDIN_FILENO;
	if (mini->cmd->infile == -1)
		return (0);
	if (mini->cmd->infile != STDIN_FILENO)
		dup2(mini->cmd->infile, STDIN_FILENO);
	return (1);
}

int	ft_outfile_change(t_minishell *mini)
{
	if (mini->token->prev->prev->token_value == APPEND)
		mini->cmd->outfile = open(mini->token->prev->str, O_CREAT \
	| O_RDWR | O_APPEND, 0777);
	else if (mini->token->prev->prev->token_value == TRUNC)
		mini->cmd->outfile = open(mini->token->prev->str, O_CREAT \
	| O_RDWR | O_TRUNC, 0777);
	else
		mini->cmd->outfile = STDOUT_FILENO;
	if (mini->cmd->outfile == -1)
		return (0);
	if (mini->cmd->outfile != STDOUT_FILENO)
		dup2(mini->cmd->outfile, STDOUT_FILENO);
	return (1);
}

char	*ft_check_cat1(t_minishell *mini)
{
	char	*temp;

	temp = NULL;
	if (mini->cmd->cmd_param[1])
	{
		temp = mini->cmd->cmd_param[1];
		if (mini->cmd->cmd_param[1][0] == '$')
			temp = ft_getenv(mini->cmd->cmd_param[1], mini);
	}
	return (temp);
}

char	*ft_check_cat2(char **argv, t_minishell *mini)
{
	char	*temp;

	temp = NULL;
	if (argv[1])
	{
		temp = argv[1];
		if (argv[1][0] == '$')
			temp = ft_getenv(argv[1], mini);
	}
	return (temp);
}

void	execute_suite(t_minishell *mini)
{
	char	*path;

	path = findpath(mini->cmd->cmd_param[0], mini->env_cpy, -1);
	if (!path)
	{
		ft_free_split(mini->cmd->cmd_param);
		perror("findpath");
		exit(EXIT_FAILURE);
	}
	else if (execve(path, mini->cmd->cmd_param, mini->env_cpy) == -1)
	{
		perror("Could not execute execve");
		free(path);
		ft_free_split(mini->cmd->cmd_param);
		exit(EXIT_FAILURE);
	}
}
