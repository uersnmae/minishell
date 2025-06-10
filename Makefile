CC = cc
CFLAGS = -Wall -Wextra -Werror -I srcs/tokenizer -I includes -g
LDLIBS   = -lreadline

VPATH = srcs:srcs/ast:srcs/tokenizer:includes:srcs/exec:srcs/builtins:srcs/signal:srcs/input:srcs/expansion:srcs/utils:srcs/env:srcs/run

AST = ast_node_create.c								\
	  ast_create.c									\
	  ast_parse_and_or.c							\
	ast_parse_pipe.c								\
	ast_parse_cmd.c									\
	ast_parse_redirection.c							\
	ast_print_tree.c								\
	ast_parse_subshell.c							\
	ast_utils.c										\

BUILTINS = builtins.c								\
	builtin_cd.c									\
	builtin_echo.c									\
	builtin_env.c									\
	builtin_exit.c									\
	builtin_exit_utils.c							\
	builtin_export.c								\
	builtin_pwd.c									\
	builtin_unset.c									\
	builtin_utils.c									\

RUN = run_ast.c										\
	  run_cmd_line.c								\

ENV = env_table.c									\
	env_table_utils.c								\
	env_handler.c									\
	env_manager.c									\

EXEC = exec_pipeline.c						\
	   free.c	\
	   build_argv_from_ast.c	\
	   build_redirs_from_ast.c	\
	   exec_heredoc_child.c		\
	   exec_utils.c				\
	   flatten_jobs.c			\
	   flatten_pipeline.c		\
	   spawn_pipeline.c			\
	   spawn_pipeline_utils.c	\
	   exec_subshell.c			\
	   redirect_utils.c			\
	   apply_redirection.c		\


EXPANSION = expansion.c								\
			expansion_utils.c						\
			expand_wildcard_arguments_bonus.c	\
			expand_wildcard_utils_bonus.c			\
			split_on_ifs.c						\

INPUT = get_input.c									\

SIGNAL = signal_handler.c							\

LEXER = tokenizer.c									\
	tokenizer_utils.c								\
	handle_word.c									\
	handle_word_utils.c								\

LEXER_BONUS = handle_word_bonus.c	\
			  handle_word_utils.c	\
			  tokenizer_bonus.c		\
			  tokenizer_utils.c		\

UTILS = str_array_list.c							\
		cleanup.c									\

COMMON = $(INPUT) $(SIGNAL) $(LEXER) $(UTILS)
COMMON_BONUS = $(INPUT) $(SIGNAL) $(LEXER_BONUS) $(UTILS)

MANDATORY_SRC = minishell.c									\
				$(AST) 			\
				$(BUILTINS)									\
				$(EXEC) \
				$(EXPANSION)								\
				$(ENV)										\
				$(RUN)										\
				$(COMMON)

BONUS_SRC = minishell.c													\
				$(AST) 			\
				$(BUILTINS)									\
				$(EXEC) \
				$(EXPANSION)								\
				$(ENV)										\
				$(RUN)										\
				$(COMMON_BONUS)

MANDATORY = minishell
BONUS = minishell_bonus

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

all: $(MANDATORY)

bonus: $(BONUS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MANDATORY): $(MANDATORY_OBJ) $(LIBFT_FILE) $(FT_PRINTF_FILE)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIB) $(LDLIBS) -o $@

$(BONUS): $(BONUS_OBJ) $(LIBFT_FILE) $(FT_PRINTF_FILE)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIB) $(LDLIBS) -o $@

$(LIBFT_FILE):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(FT_PRINTF_FILE):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(MANDATORY) $(BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

re: fclean all

compile:
	@echo "[" > compile_commands.json; \
	SEP=""; \
	for SRC in $$(find srcs -name "*.c"); do \
		echo "$$SEP{" >> compile_commands.json; \
		echo "  \"directory\": \"$$PWD\"," >> compile_commands.json; \
		echo "  \"command\": \"cc -Wall -Wextra -Werror -Isrcs/tokenizer -Iincludes -Ilibft -Isrcs -c $$SRC -o /dev/null\"," >> compile_commands.json; \
		echo "  \"file\": \"$$SRC\"" >> compile_commands.json; \
		echo "}" >> compile_commands.json; \
		SEP=","; \
	done; \
	echo "]" >> compile_commands.json

del_compile:
	rm -f compile_commands.json

.PHONY: clean fclean bonus re compile del_compile
