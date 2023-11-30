SRC =   main.c \
	src/mystring.c \
	src/automate.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wextra

NAME = output

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lconfig 

all:     $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: 	fclean all
