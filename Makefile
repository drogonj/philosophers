SRCS		=	main.c				\
				philosophers.c		\
				utils.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	philo

FLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

.c.o:
			gcc $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(FLAGS) $(OBJS) -o $(NAME)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re