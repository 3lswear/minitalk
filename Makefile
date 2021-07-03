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

LIBFT_HEADER = ./ext/libft/libft.h
LIBFT = ./ext/libft/libft.a
LIBFT_FLAGS = -L=ext/libft -lft
LIBFT_SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memcpy_bd.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd. \
	ft_putendl_fd. \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strchr_bd.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c

all: $(NAME)

$(NAME): client server

# $(OBJ): %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(CLI_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(SRV_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

# $(LIBFT):
# 	$(MAKE) -C ./ext/libft

# $(NAME): $(LIBFT) $(OBJ) 
	# $(CC) $(OBJ) $(LIBFT_FLAGS) -lm -o $(NAME)

client: $(CLI_OBJ) 
	$(CC) $(CLI_OBJ) -o $@

server: $(SRV_OBJ) 
	$(CC) $(SRV_OBJ) -o $@

clean:
	$(RM) $(OBJ)
	# $(MAKE) clean -C ./libft

fclean: clean
	$(RM) server
	$(RM) client
	# $(MAKE) fclean -C ./libft

re:
	$(MAKE) fclean
	$(MAKE) all

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"

