NAME		=	philo
#
SOURSE		=	utils.c\
				init_rules.c\
				time_count.c\
				start_simulation.c
# 
CFLAGS		= -Wall -Werror -Wextra -I $(HEADER) -g
HEADER		= philo.h

OBJ = $(SOURSE:%.c=%.o)
CC = gcc
#
.PHONY : all clean fclean re bonus
#
all: $(NAME)
	@say Hello peer. I am phella. Welcome to my project philosophers! &
#
$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(SOURSE) -o $(NAME)
#
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
#
clean :
	@rm -f $(OBJ)
#
fclean : clean
	@rm -f $(NAME)
re     :	fclean all