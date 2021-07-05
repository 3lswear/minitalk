NAME = minitalk

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = ./includes

HEADER = $(INCLUDES)/minitalk.h

HEADERS = minitalk.h

SRV_SRC = $(wildcard ./src/server/*.c)
CLI_SRC = $(wildcard ./src/client/*.c)

SRC = $(SRV_SRC) $(CLI_SRC)

SRV_OBJ = $(SRV_SRC:.c=.o)
CLI_OBJ = $(CLI_SRC:.c=.o)
OBJ = $(SRC:.c=.o)

LIBFT_HEADER = ./libft/libft.h
LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

all: $(NAME)

$(NAME): client server

# $(OBJ): %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(CLI_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(SRV_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(LIBFT):
	$(MAKE) -C ./libft

# $(NAME): $(LIBFT) $(OBJ) 
	# $(CC) $(OBJ) $(LIBFT_FLAGS) -lm -o $(NAME)

client: $(CLI_OBJ) $(LIBFT) 
	$(CC) $(CLI_OBJ) $(LIBFT_FLAGS) -o $@

server: $(SRV_OBJ) $(LIBFT)
	$(CC) $(SRV_OBJ) $(LIBFT_FLAGS) -o $@

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

