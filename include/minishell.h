/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:53:18 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/06 12:51:27 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6
# define ARG		7

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef struct s_cmd
{
	int				skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token_list
{
	char				*str;
	int					token_value;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}	t_token_list;

typedef struct s_stuff
{
	int				i;
	int				j;
	t_token_list	*start;
}	t_stuff;

//cwd : current_working_directory, 4096 is the max length of a a path.
typedef struct s_minishell
{
	int				exit_status;
	char			**env_cpy;
	t_cmd			*cmd;
	t_token_list	*token;
}	t_minishell;

//utils

/*free.c*/
void	ft_free_split(char **split);
void	ft_free_lst(t_minishell *mini);
void	ft_free_lst_pipex(t_minishell *mini);

/*utils1.c*/
int		ft_is_empty_or_spaces(const char *str);
void	ft_print_export_alone(char *new_env);

/* signal.c */
void	handle_sigint(int sig);
void	ft_signals(void);

/* ft_export.c */
int		ft_setenv(char **value, t_minishell *mini);
int		ft_export(t_minishell *mini, t_token_list *list, \
char *input, char **value);
void	ft_sort_env(char **new_env);
char	**export_alone(char **env);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/* ft_export_utils.c */
char	*ft_copy_export(char *value, int flag_double_quote, \
int flag_single_quote, char *new_value);
char	*ft_handle_export(char *value, int flag_double_quote, \
int flag_single_quote, int i);
int		ft_verif_input_export(char *input);
int		ft_setenv_alone(char *value, t_minishell *mini);

/* ft_echo.c */
int		ft_echo(t_token_list *list, t_minishell *mini);
char	*ft_echo_suite(t_token_list *node, t_minishell *mini);
int		handle_echo_suite(t_token_list *node, int flag_s, \
int i, t_minishell *mini);

/* ft_env.c */
int		ft_env(char **env);

/* ft_exit.c */
void	ft_exit(t_token_list *token, t_minishell *mini);

/* ft_unset.c */
int		ft_unset(t_minishell *mini, char *input);
void	change_env(t_minishell *mini, int i);

/* ft_split_export.c */
char	**ft_split_export(char *s, char c);

/* ft_pipex.c */
int		ft_pipex(t_minishell *mini);
int		init_first_child(t_minishell *mini, int count);
int		ft_cmd_count(t_cmd *cmd);
int		ft_exec(t_minishell *mini);
void	execute(t_minishell *mini, char *temp, char **cmd);

/* ft_pipex_utils.c */
int		ft_check_pipex(t_minishell *mini, t_cmd *start);
char	*ft_handle_pipex(char *value, int flag_double_quote, \
int flag_single_quote, int i);
void	ft_free_pipex(t_minishell *mini, t_cmd *start);

/* ft_pipex_utils2.c */
int		ft_infile_change(t_minishell *mini);
int		ft_outfile_change(t_minishell *mini);
char	*ft_check_cat1(t_minishell *mini);
char	*ft_check_cat2(char **argv, t_minishell *mini);
void	execute_suite(t_minishell *mini);

/* ft_here_doc.c */
int		ft_here_doc(t_minishell *mini);
int		check_heredoc(t_minishell *mini, t_token_list *start);

int		ft_cd(t_minishell *mini);
int		ft_pwd(void);

char	**ft_env_cpy(char **env);
void	ft_sort_env(char **new_env);

//parsing

/* ft_parse.c */
int		ft_parse(char *input, t_minishell *mini);
int		ft_which_builtin(t_minishell *mini);

/* ft_parse_utils.c */
int		ft_lst_init(char *input, t_minishell *mini, int i, int quote_state);
int		ft_change_quote_state(char c, int quote_state);
int		ft_lst_fill(int size, int start, char *input, t_minishell *mini);
int		is_builtins(t_minishell *mini, t_token_list *token, char **cmd);
int		exec_builtins(t_minishell *mini, char **cmd);

/* ft_parse_utils2.c */
int		ft_env_parse(t_minishell *mini);
char	*ft_search_and_replace(t_minishell *mini);
char	*ft_replace_str(t_minishell *mini, char *var_name, int start, int end);
int		ft_is_in_single_quote(char *str, int start, int end, \
int in_double_quote);
char	*ft_getenv(char *var_name, t_minishell *mini);

/* ft_parse_utils3.c */
int		ft_token_init(t_minishell *mini);
int		ft_which_token(t_token_list *token, char **env);
int		ft_is_command(t_token_list *token, char **env);
char	*ft_strcpy_parse(char *src, char *dest, int size, int j);
int		ft_count_words(char const *s, char c);

/* ft_parse_utils4.c*/
int		ft_token_parse(t_minishell *mini);
int		ft_replace_exit_status(t_minishell *mini);

/* ft_parse_utils5.c */
int		ft_awk(t_minishell *mini);

/* ft_parse_pipex.c */
int		ft_parse_pipex(t_minishell *mini, t_token_list *start);

//execution

/* ft_exec.c */
int		ft_launch(t_minishell *mini);

/* ft_find_cmd */
char	*get_path(char *name, char **env);
char	*findpath(char *tofind, char **env, int i);
int		ft_which_command(t_minishell *mini);
int		ft_command_exec(char *path, char **argv, t_minishell *mini, char *temp);
int		ft_launch(t_minishell *mini);

/* ft_which_builtin.c */
int		ft_which_builtin(t_minishell *mini);

extern pid_t	g_pid;
#endif
