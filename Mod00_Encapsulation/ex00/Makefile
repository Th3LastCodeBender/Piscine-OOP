NAME = DivideAndRule

CC = c++
FLAGS = -Wall -Wextra -Werror -g
DEBUG ?= 0
CPPFLAGS = -std=c++98 -DDEBUG=$(DEBUG)

SRCS = main.cpp Account/Account.cpp Bank/Bank.cpp

RUN_ARGS := $(filter-out run val all clean fclean gdb re debug,$(MAKECMDGOALS))

all: $(NAME)

$(NAME): $(SRCS)
		$(CC) $(FLAGS) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	@echo "wassup"

fclean:
	rm -f $(NAME)

re: fclean all

debug: fclean
	$(MAKE) --no-print-directory DEBUG=1 run $(RUN_ARGS)

run: $(NAME)
	clear ; ./$(NAME) $(RUN_ARGS)

val: $(NAME)
	clear ; valgrind ./$(NAME) $(RUN_ARGS)

gdb: $(NAME)
	clear ; gdb --args ./$(NAME) $(RUN_ARGS)

.PHONY: all clean fclean re run val gdb debug

#regola che non fa interpretare come target le parole non riconosciute come comandi make
%:
	@:

.SILENT: