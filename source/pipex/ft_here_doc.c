/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:47:52 by matle-br          #+#    #+#             */
/*   Updated: 2024/09/08 18:54:12 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_replace_heredoc(char *str, t_minishell *mini)
{
	char	*var_name;
	int		i;
	int		start;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (str);
	start = i + 1;
	i++;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = malloc(sizeof(char) * (i - start + 1));
	if (var_name == NULL)
		return (NULL);
	var_name = ft_strcpy_parse(str, var_name, (i - start), start);
	if (ft_getenv(var_name, mini) != NULL)
		return (ft_replace_str(mini, var_name, start, i));
	free(var_name);
	return (str);
}

int	check_heredoc(t_minishell *mini, t_token_list *start)
{
	int	heredoc;
	int	limiter;

	heredoc = 0;
	limiter = 0;
	while (1)
	{
		if (start->token_value == HEREDOC && !limiter)
			heredoc = 1;
		if (start->token_value == ARG && heredoc)
			limiter += 1;
		start = start->next;
		if (start == mini->token || (start->token_value != ARG && heredoc))
			break ;
	}
	if (heredoc == 1 && limiter == 1)
		return (1);
	return (0);
}

int	ft_read_heredoc(t_minishell *mini, int fd, char *limiter)
{
	char	*input;

	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			printf("warning: here-document delimited by end-of-file ");
			printf("(wanted '%s')\n", limiter);
			break ;
		}
		if (!ft_strcmp(input, limiter))
			break ;
		input = ft_replace_heredoc(input, mini);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	close(fd);
	return (1);
}

int	ft_count_here_doc(t_token_list *token)
{
	int				count;
	t_token_list	*temp;

	count = 0;
	temp = token;
	while (1)
	{
		if (temp->token_value == HEREDOC)
			count++;
		temp = temp->next;
		if (temp == token)
			break ;
	}
	return (count);
}

int	ft_here_doc(t_minishell *mini)
{
	int				fd;
	int				count;
	t_token_list	*start;

	count = ft_count_here_doc(mini->token);
	start = mini->token;
	while (count > 0)
	{
		while (start->token_value != HEREDOC)
			start = start->next;
		fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd < 0)
			return (-1);
		ft_read_heredoc(mini, fd, start->next->str);
		fd = open(".heredoc.tmp", O_RDONLY);
		if (fd > 0)
			unlink(".heredoc.tmp");
		start = start->next;
		count--;
	}
	return (fd);
}
