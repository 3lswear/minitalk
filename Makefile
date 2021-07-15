NAME = minitalk

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = ./includes

HEADER = $(INCLUDES)/minitalk.h

HEADERS = minitalk.h

SRV_SRC = ./src/server/server.c
CLI_SRC = ./src/client/client.c
UTILS_SRC = ./src/utils.c

SRC = $(SRV_SRC) $(CLI_SRC) $(UTILS_SRC)

SRV_OBJ = $(SRV_SRC:.c=.o)
CLI_OBJ = $(CLI_SRC:.c=.o)
UTILS_OBJ = $(UTILS_SRC:.c=.o)

OBJ = $(SRC:.c=.o)

LIBFT_HEADER = ./libft/libft.h
LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

all: $(NAME)

$(NAME): client server

$(UTILS_OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(CLI_OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -o $@

$(SRV_OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(LIBFT):
	$(MAKE) -C ./libft

client: $(CLI_OBJ) $(LIBFT) $(HEADER) $(UTILS_OBJ)
	$(CC) $(CLI_OBJ) $(UTILS_OBJ) $(LIBFT_FLAGS) -o $@

server: $(SRV_OBJ) $(LIBFT) $(HEADER) $(UTILS_OBJ)
	$(CC) $(SRV_OBJ) $(UTILS_OBJ) $(LIBFT_FLAGS) -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) server
	$(RM) client
	$(MAKE) fclean -C ./libft

re:
	$(MAKE) fclean
	$(MAKE) all

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"

