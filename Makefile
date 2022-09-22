SRC = $(wildcard src/*.c)
SRC += $(wildcard src/XML_Parser/*.c)

OBJ = $(SRC:.c=.o)

INCLUDE = -Iinclude

CFLAGS = -Wall -Wextra $(INCLUDE)

NAME = xml_parser

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

debug: CFLAGS += -g
debug: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean all

re: fclean all