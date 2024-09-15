/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:25:31 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/08 18:57:26 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute(t_minishell *mini, char *temp, char **cmd)
{
	temp = ft_check_cat1(mini);
	if (!ft_strcmp("cat\0", mini->cmd->cmd_param[0]) && temp == NULL)
	{
		free(mini->cmd->cmd_param[1]);
		mini->cmd->cmd_param[1] = NULL;
	}
	if (exec_builtins(mini, cmd))
	{
		ft_free_split(mini->cmd->cmd_param);
		exit(EXIT_SUCCESS);
	}
	execute_suite(mini);
	if (temp)
		free(temp);
	return (ft_free_split(mini->cmd->cmd_param), (void)1);
}

int	ft_exec(t_minishell *mini)
{
	int		fd[2];
	pid_t	pid;

	while (mini->cmd->skip_cmd == 1)
		mini->cmd = mini->cmd->next;
	mini->cmd->skip_cmd = 1;
	if (pipe(fd) == -1)
		return (printf("An error occured with opening the pipe\n"), 0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(mini, NULL, mini->cmd->cmd_param);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (1);
}

int	ft_cmd_count(t_cmd *cmd)
{
	t_cmd	*start;
	int		i;

	start = cmd;
	i = 0;
	while (1)
	{
		i++;
		start = start->next;
		if (start == cmd)
			break ;
	}
	return (i);
}

int	init_first_child(t_minishell *mini, int count)
{
	if (check_heredoc(mini, mini->token))
	{
		mini->cmd->infile = ft_here_doc(mini);
		dup2(mini->cmd->infile, STDIN_FILENO);
	}
	if (!ft_infile_change(mini))
		return (perror("open"), 0);
	while (count > 1)
	{
		if (!ft_exec(mini))
			return (0);
		count--;
	}
	if (!ft_outfile_change(mini))
		return (perror("open"), 0);
	while (mini->cmd->skip_cmd == 1)
		mini->cmd = mini->cmd->next;
	return (execute(mini, NULL, mini->cmd->cmd_param), 1);
}

int	ft_pipex(t_minishell *mini)
{
	int		count;
	int		fd[2];

	ft_check_pipex(mini, mini->cmd);
	count = ft_cmd_count(mini->cmd);
	if (pipe(fd) == -1)
		return (printf("Error with opening the pipe\n"), 0);
	g_pid = fork();
	if (g_pid == -1)
		return (0);
	if (g_pid == 0)
		init_first_child(mini, count);
	else
	{
		waitpid(g_pid, &mini->exit_status, 0);
		close(fd[0]);
		close(fd[1]);
		if (WIFEXITED(mini->exit_status))
			return (ft_free_pipex(mini, mini->cmd), \
			WEXITSTATUS(mini->exit_status));
	}
	ft_free_pipex(mini, mini->cmd);
	return (1);
}
