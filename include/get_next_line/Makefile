# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 16:30:07 by dloisel           #+#    #+#              #
#    Updated: 2024/06/17 22:09:17 by dloisel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = get_next_line.c \
      get_next_line_utils.c \

OBJS = get_next_line.o \
      get_next_line_utils.o \

all : $(NAME)

%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	@$(CC) $(FLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
