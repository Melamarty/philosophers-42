SRCS =   main_bonus.c ft_atoi.c init_philo_bonus.c routine_bonus.c \
 		time_bonus.c  create_philos.c check_args.c

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -pthread # -fsanitize=address -g

all : $(NAME)
	make clean

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
