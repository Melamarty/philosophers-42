SRCS = main.c check_args.c utils.c init_philo.c routine.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread # -fsanitize=address -g

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS) $^ -o $@

%.o : %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONEY : all clean fclean re
