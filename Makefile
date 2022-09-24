SRC = $(wildcard src/*.c)
SRC += $(wildcard src/XML_Parser/*.c)

OBJ = $(SRC:.c=.o)

INCLUDE = -Iinclude

CFLAGS = -Wall -Wextra $(INCLUDE)

NAME = bin/xml_parser

LIB_NAME = bin/libxml_parser.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

debug: CFLAGS += -g
debug: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_NAME)

re: fclean all

lib: $(OBJ)
	ar rc $(LIB_NAME) $(OBJ)
	rm -f $(OBJ)