# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 13:33:48 by dloisel           #+#    #+#              #
#    Updated: 2024/09/06 12:51:50 by matle-br         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRAY = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lreadline -lncurses

SRC = source/main.c \
	  source/parsing/ft_parse.c \
	  source/parsing/ft_parse_utils.c \
	  source/parsing/ft_parse_utils2.c \
	  source/parsing/ft_parse_utils3.c \
	  source/builtins/ft_pwd.c \
	  source/builtins/ft_env.c \
	  source/builtins/ft_echo.c \
	  source/builtins/ft_export.c \
	  source/builtins/ft_export_utils.c \
	  source/builtins/ft_unset.c \
	  source/builtins/ft_cd.c \
	  source/execution/ft_find_cmd.c \
	  source/utils/free.c \
	  source/execution/ft_which_builtin.c \
	  source/execution/ft_exec.c \
	  source/utils/utils1.c \
	  source/utils/signal.c \
	  source/utils/ft_split_export.c \
	  source/parsing/ft_parse_pipex.c \
	  source/parsing/ft_parse_utils4.c \
	  source/pipex/ft_pipex.c \
	  source/pipex/ft_pipex_utils.c \
	  source/pipex/ft_here_doc.c \
	  source/pipex/ft_pipex_utils2.c \
	  source/builtins/ft_exit.c \
	  source/parsing/ft_parse_utils5.c

RM = rm -f
OBJ = $(SRC:.c=.o)

LIBFT = ./include/libft/libft.a
GNL = ./include/get_next_line/get_next_line.a
PIPEX = ./include/pipex/pipex.a

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) $(GNL) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)minishell compiled!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)making libft...$(RESET)"
	@make bonus --no-print-directory -C ./include/libft

$(GNL):
	@echo "$(YELLOW)making GNL..."
	@make --no-print-directory -C ./include/get_next_line

$(PIPEX):
	@echo "$(YELLOW)making pipex...$(RESET)"
	@make --no-print-directory -C ./include/pipex

clean:
	@echo "$(RED)make clean...$(RESET)"
	@rm -f $(OBJ)
	@rm -f $(OBJS_BONUS)
	@make clean --no-print-directory -C ./include/libft
	@make clean --no-print-directory -C ./include/get_next_line


fclean: clean
	@echo "$(RED)make fclean..$(RESET)."
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make fclean --no-print-directory -C ./include/libft
	@make fclean --no-print-directory -C ./include/get_next_line

re: fclean all

.PHONY: all clean fclean re bonus






