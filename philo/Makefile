GCC		= gcc

CFLAGS	= -g -Wall -Wextra -Werror -pthread

FILES	= main.c utils.c input_check.c routine.c eat.c death.c

NAME	= philo

RM	= rm -f

OBJECTS=$(FILES:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJECTS)
			$(GCC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
			@$(RM) $(OBJECTS)
			
fclean:	clean
			@$(RM) $(NAME)
			
re:		fclean all

.PHONY:		all clean fclean re
