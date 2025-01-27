

SRCS            = philosophers.c checks.c utils.c inits.c handlers.c \
					philo_set_get.c philo_start.c

OBJS            = $(SRCS:.c=.o)

CC              = cc

RM              = rm -f

CFLAGS          =  -g -Wall -Wextra -Werror -pthread #-fsanitize=thread

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
