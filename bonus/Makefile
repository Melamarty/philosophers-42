SRCS = main_bonus.c check_args_bonus.c utils_bonus.c init_philo_bonus.c routine_bonus.c \
	#    create_philos_bonus.c

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -pthread # -fsanitize=address -g

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS) $^ -o $@

%.o : %.c philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONEY : all clean fclean re
