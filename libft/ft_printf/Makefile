CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes -I..
NAME = libftprintf.a

SRCS = ft_parse.c ft_format.c ft_format_utils.c ft_printf.c
BNS_SRCS = ft_flags_bonus.c ft_flags_options_bonus.c ft_flags_utils1_bonus.c ft_flags_utils2_bonus.c ft_printf_bonus.c

SRCS_NO_PRINTF = ft_parse.c ft_format.c ft_format_utils.c

SRC_DIR = srcs
OBJ_DIR = objs

LIBFT_DIR = ..
LIBFT = $(LIBFT_DIR)/libft.a
TMP_DIR = tmp_libft_objs

# Add all c files to ALL_SRCS 
ALL_SRCS = $(SRCS)

# make bonus will add all bonus c files to ALL_SRCS
ifeq ($(filter bonus,$(MAKECMDGOALS)),bonus)
    ALL_SRCS = $(SRCS_NO_PRINTF) $(BNS_SRCS)
endif

# Path to the all c files 
SRCS_WITH_PATH = $(addprefix $(SRC_DIR)/, $(ALL_SRCS))

# Path to the all object files
OBJS = $(addprefix $(OBJ_DIR)/, $(ALL_SRCS:.c=.o))

ifeq ($(filter bonus, $(MAKECMDGOALS)), bonus)
	ALL_SRCS = $(SRCS_NO_PRINTF) $(BNS_SRCS)
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@mkdir -p $(TMP_DIR)
	@cp $(LIBFT) $(TMP_DIR)
	@cd $(TMP_DIR) && ar x libft.a
	@ar rcs $(NAME) $(OBJS) $(TMP_DIR)/*.o
	@rm -rf $(TMP_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
