CC = cc 
CFLAGS = -Wall -Wextra -Werror -I get_next_line
NAME = libft.a 
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isdigit.c ft_isprint.c ft_isspace.c\
		ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcpy.c ft_strcpy.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtok.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strndup.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

BNS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
		ft_lstsize.c

OBJS = $(SRCS:.c=.o)
BNS_OBJS = $(BNS:.c=.o)
INCLUDES = libft.h

all: $(NAME) 

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BNS_OBJS)
	ar rcs $(NAME) $^
	touch $@

clean:
	rm -f $(OBJS)
	rm -f $(BNS_OBJS)
	rm -f bonus

fclean: clean
	rm -f $(NAME) $(SO_NAME)

re: fclean all

.PHONY: clean fclean re
