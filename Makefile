CC = cc
CFLAGS = -Wall -Wextra -Werror

VPATH = srcs:srcs/ast_parser:srcs/tokenizer:srcs/tokenizer_bonus:includes

MANDATORY_INC = ast.h tokenizer.h
MANDATORY_SRC =
# tokenizer srcs
				get_operator.c		\
				tokenizer.c 		\
				tokenizer_utils.c	\
# ast_parser srcs

MANDATORY = minishell
BONUS = minishell
NAME = $(MANDATORY) $(BONUS)

OBJ_DIR = obj
LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
CFLAGS += -I $(LIBFT_DIR) -I $(LIBFT_DIR)/get_next_line

FT_PRINTF = libftprintf.a
FT_PRINTF_DIR = libft/ft_printf
FT_PRINTF_FILE = $(FT_PRINTF_DIR)/$(FT_PRINTF)
CFLAGS += -I $(FT_PRINTF_DIR)/includes

LIB = $(LIBFT_FILE) $(FT_PRINTF_FILE)

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

all: $(MANDATORY) $(BONUS)


