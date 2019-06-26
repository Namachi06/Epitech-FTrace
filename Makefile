##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Compilation
##

LIB_PATH	=	./lib/my

SRC_proj	=	src/main.c \
				src/handle_args.c \
				src/ftrace.c \
				src/print_signals.c \
				src/symb_name.c \
				src/symbols_handler.c \
				src/call_handler.c \
				src/print/syscalls/print_syscalls.c \
				src/print/syscalls/print_args_addresses.c \
				src/print/syscalls/print_args_addresses2.c \
				src/print/relcall/print_relcall.c \
				src/print/indcall/print_indcall.c \
				src/errors.c \
				src/free.c \

SRC_test	= 	tests/test.c

OBJ		=	$(SRC_proj:.c=.o)

CFLAGS		+=	-W -Wall -Wextra -g

LDFLAGS	+=	-ldl -lelf

CRITFLAGS		=	-lcriterion -lgcov

MAKE =		@make -s -C

NAME	=	ftrace

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) $(LIB_PATH) re
	@gcc $(OBJ) -o $(NAME) $(CFLAGS) $(LDFLAGS) -I./include -L./lib/my -lmy

tests_run:
	cc -o units $(SRC_proj) $(SRC_test) $(CRITFLAGS) --coverage
	./units

clean:
	rm -f $(OBJ) *.gcno *.gcda

fclean: clean_lib clean
	rm -f $(NAME) units

re: fclean all

clean_lib:
	$(MAKE) $(LIB_PATH) fclean