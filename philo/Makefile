NAME = philo

CC = cc
GFLAGS = -g3 -Wall -Werror -Wextra -Wshadow -Wpedantic

SRCDIR = src/
OBJDIR = obj/

SRCFILES = fork_utils.c frees.c init_philos.c input_check.c main.c philo_locks.c printers.c threading.c utils.c sim.c
SRCOBJ = $(SRCFILES:%.c=$(OBJDIR)%.o)

HEADERS = -I include/philo.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(CC) $(GFLAGS) $(SRCOBJ) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p ${OBJDIR}
	$(CC) -c $(GFLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
