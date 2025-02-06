# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 11:02:10 by ptorrao-          #+#    #+#              #
#    Updated: 2025/02/04 15:37:20 by peferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS            = main.c init.c utils.c philosophers.c free.c \
					routine.c checks.c prints.c

OBJS            = $(SRCS:.c=.o)

CC              = cc

RM              = rm -f

CFLAGS          =  -g -Wall -Wextra -Werror -pthread -fsanitize=thread

NAME            = philo


all:            $(NAME)

$(NAME):        $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)	

clean:
	$(RM) $(OBJS)

fclean:         clean
	$(RM) $(NAME)

re:             fclean $(NAME)

.PHONY:         all clean fclean re 